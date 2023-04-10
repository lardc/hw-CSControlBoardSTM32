// Header
#include "Controller.h"
//
// Includes
#include "Board.h"
#include "Delay.h"
#include "DeviceProfile.h"
#include "Interrupts.h"
#include "LowLevel.h"
#include "SysConfig.h"
#include "DebugActions.h"
#include "Diagnostic.h"
#include "Logic.h"
#include "BCCIxParams.h"
#include "Constraints.h"
#include "Measurement.h"
#include "math.h"

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
volatile DeviceSubState CONTROL_SubState = SS_None;
static Boolean CycleActive = false;
static float ActualPressureValue = 0;
ClampState CONTROL_ClampState = CS_None;
//
volatile Int64U CONTROL_TimeCounter = 0;

// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetToDefaultState();
void CONTROL_CSMPrepareLogic();
void CONTROL_ClampLogic();
void CONTROL_HandleLEDLogic();
void CONTROL_SamplePressureValue();
void CONTROL_HandleSafetyOutput();

// Functions
//
void CONTROL_Init()
{
	// Конфигурация сервиса работы Data-table и EPROM
	EPROMServiceConfig EPROMService = {(FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT};
	// Инициализация data table
	DT_Init(EPROMService, false);
	DT_SaveFirmwareInfo(CAN_NID, 0);
	// Инициализация device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	
	// Сброс значений
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaultState();
}
//------------------------------------------

void CONTROL_ResetToDefaultState()
{
	LOGIC_ResetOutputRegisters();
	CONTROL_SetDeviceState(DS_None, SS_None);
}
//------------------------------------------

void CONTROL_Idle()
{
	DEVPROFILE_ProcessRequests();
	
	LOGIC_UpdateDiscreteSensors();
	CONTROL_HandleLEDLogic();
	CONTROL_SamplePressureValue();
	CONTROL_HandleSafetyOutput();
	
	CONTROL_CSMPrepareLogic();
	
	CONTROL_ClampLogic();
	
	CONTROL_UpdateWatchDog();
}
//------------------------------------------

static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError)
{
	*pUserError = ERR_NONE;
	
	switch(ActionID)
	{
		case ACT_ENABLE_POWER:
			if(CONTROL_State == DS_None)
			{
				LOGIC_ResetOutputRegisters();
				CONTROL_SetDeviceState(DS_None, SS_None);
			}
			else if(CONTROL_State != DS_Ready)
				*pUserError = ERR_OPERATION_BLOCKED;
			break;
			
		case ACT_DISABLE_POWER:
			if(CONTROL_State == DS_Ready)
			{
				CONTROL_SetDeviceState(DS_None, SS_None);
			}
			else if(CONTROL_State != DS_None)
				*pUserError = ERR_OPERATION_BLOCKED;
			break;
			
		case ACT_CLR_FAULT:
			if(CONTROL_State == DS_Fault)
			{
				CONTROL_SetDeviceState(DS_None, SS_None);
				DataTable[REG_FAULT_REASON] = DF_NONE;
			}
			break;
			
		case ACT_CLR_WARNING:
			DataTable[REG_WARNING] = WARNING_NONE;
			break;
			
		case ACT_PREPARE_CSM:
			if(CONTROL_State == DS_Ready)
			{
				CONTROL_SetDeviceState(DS_InProcess, SS_TopAdapterStateCheck);
			}
			else if(CONTROL_State == DS_InProcess)
				*pUserError = ERR_OPERATION_BLOCKED;
			else
				*pUserError = ERR_DEVICE_NOT_READY;
			break;
			
		case ACT_CLAMP_START:
			if(CONTROL_State == DS_Ready)
			{
				CONTROL_SetDeviceState(DS_InProcess, SS_None);
				CONTROL_ClampState = CS_ClampPressureCheck;
			}
			else if(CONTROL_State == DS_InProcess)
				*pUserError = ERR_OPERATION_BLOCKED;
			else
				*pUserError = ERR_DEVICE_NOT_READY;
			break;
			
		case ACT_CLAMP_STOP:
			if(CONTROL_State == DS_Ready)
			{
				CONTROL_SetDeviceState(DS_InProcess, SS_None);
				CONTROL_ClampState = CS_ClampDisengage;
			}
			else if(CONTROL_State == DS_InProcess)
				*pUserError = ERR_OPERATION_BLOCKED;
			else
				*pUserError = ERR_DEVICE_NOT_READY;
			break;
			
		default:
			return DIAG_HandleDiagnosticAction(ActionID, pUserError);
			
	}
	return true;
}
//-----------------------------------------------

void CONTROL_CSMPrepareLogic()
{
	if(CONTROL_State == DS_InProcess)
	{
		switch(CONTROL_SubState)
		{
			case SS_TopAdapterStateCheck:
				if(LL_GetStateLimitSwitchTopAdapter())
					CONTROL_SetDeviceState(DS_InProcess, SS_TopAdapterIDCheck);
				else
					CONTROL_SwitchToFault(DF_TOP_ADAPTER_OPENED);
				break;
				
			case SS_TopAdapterIDCheck:
				LOGIC_AdapterIDMeasure(TOP_ADAPTER);
				LOGIC_AdapterIDMatch();
				
				if(DataTable[REG_ID_ADPTR_CHECKED] == DataTable[REG_ID_ADPTR_SET])
					CONTROL_SetDeviceState(DS_InProcess, SS_BotAdapterStateCheck);
				else
					CONTROL_SwitchToFault(DF_TOP_ADAPTER_MISMATCHED);
				break;
				
			case SS_BotAdapterStateCheck:
				if(LL_GetStateLimitSwitchBotAdapter())
					CONTROL_SetDeviceState(DS_InProcess, SS_BotAdapterIDCheck);
				else
					CONTROL_SwitchToFault(DF_BOT_ADAPTER_OPENED);
				break;
				
			case SS_BotAdapterIDCheck:
				LOGIC_AdapterIDMeasure(BOT_ADAPTER);
				LOGIC_AdapterIDMatch();
				
				if(DataTable[REG_ID_ADPTR_CHECKED] == DataTable[REG_ID_ADPTR_SET])
					CONTROL_SetDeviceState(DS_InProcess, SS_DUTPresenceCheck);
				else
					CONTROL_SwitchToFault(DF_BOT_ADAPTER_MISMATCHED);
				break;
				
			case SS_DUTPresenceCheck:
				CONTROL_SetDeviceState(DS_Ready, SS_None);
				break;
				
			default:
				break;
		}
	}
}
//-----------------------------------------------

void CONTROL_ClampLogic()
{
	float MeasuredError = ((float)DataTable[REG_SET_PRESSURE_VALUE] - ActualPressureValue)
			/ DataTable[REG_SET_PRESSURE_VALUE] * 100;
	float AllowedError = (float)DataTable[REG_ALLOWED_ERROR] / 10;
	
	if(CONTROL_State == DS_InProcess)
	{
		switch(CONTROL_ClampState)
		{
			case CS_ClampPressureCheck:
				if((fabsf(MeasuredError)) > AllowedError)
				{
					CONTROL_ClampState = CS_None;
					CONTROL_SwitchToFault(DF_PRESSURE_ERROR_EXCEED);
				}
				else
					CONTROL_ClampState = CS_ClampEngage;
				break;
				
			case CS_ClampEngage:
				LL_SetStatePneumTOP(true);
				LL_SetStatePneumBOT(true);
				LL_SetStatePneumDUT(true);
				CONTROL_SetDeviceState(DS_Ready, SS_None);
				break;
				
			case CS_ClampDisengage:
				LL_SetStatePneumTOP(false);
				LL_SetStatePneumBOT(false);
				LL_SetStatePneumDUT(false);
				CONTROL_SetDeviceState(DS_Ready, SS_None);
				break;
				
			default:
				break;
		}
	}
}
//-----------------------------------------------

void CONTROL_HandleLEDLogic()
{
	if((CONTROL_State == DS_Ready) && (CONTROL_ClampState == CS_ClampEngage))
	{
		LL_SetStateIndCSM(true);
		LL_SetStateIndADPTR(true);
	}
	else
	{
		LL_SetStateIndCSM(false);
		LL_SetStateIndADPTR(false);
	}
}
//-----------------------------------------------

void CONTROL_HandleSafetyOutput()
{
	if((CONTROL_State == DS_Ready) && (CONTROL_ClampState == CS_ClampEngage))
		LL_SetStateSFOutput(true);
}
//-----------------------------------------------

void CONTROL_SamplePressureValue()
{
	ActualPressureValue = MEASURE_GetPressureValue();
	DataTable[REG_PRESSURE_VALUE] = ActualPressureValue;
}
//------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_SetDeviceState(DS_Fault, SS_None);
	DataTable[REG_FAULT_REASON] = Reason;
}
//------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState, DeviceSubState NewSubState)
{
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;
	
	CONTROL_SubState = NewSubState;
	DataTable[REG_SUB_STATE] = NewSubState;
}
//------------------------------------------

void CONTROL_UpdateWatchDog()
{
	if(BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//------------------------------------------

