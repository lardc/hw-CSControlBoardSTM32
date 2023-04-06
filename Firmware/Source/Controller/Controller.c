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
#include "SelfTest.h"
#include "Constraints.h"

// Definitions
//


// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
volatile DeviceSubState CONTROL_SubState = SS_None;
static Boolean CycleActive = false;
//
volatile Int64U CONTROL_TimeCounter = 0;
//

// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetToDefaultState();
void CONTROL_CSMPrepareLogic();
void CONTROL_SaveTestResult();

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

	CONTROL_CSMPrepareLogic();

	CONTROL_UpdateWatchDog();
}
//------------------------------------------

static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError)
{
	*pUserError = ERR_NONE;
	
	switch (ActionID)
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

			break;

		case ACT_CLR_FAULT:
			if (CONTROL_State == DS_Fault)
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
			else
				if (CONTROL_State == DS_InProcess)
					*pUserError = ERR_OPERATION_BLOCKED;
				else
					*pUserError = ERR_DEVICE_NOT_READY;

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
				if (LL_GetStateLimitSwitchTopAdapter())
					CONTROL_SetDeviceState(DS_InProcess, SS_TopAdapterIDCheck);
				else
					CONTROL_SwitchToFault(DF_TOP_ADAPTER_OPENED);
				break;

			case SS_TopAdapterIDCheck:
				LOGIC_AdapterIDMeasure(TOP_ADAPTER);
				LOGIC_AdapterIDMatch();

				if (DataTable[REG_ID_ADPTR_CHECKED] == DataTable[REG_ID_ADPTR_SET])
					CONTROL_SetDeviceState(DS_InProcess, SS_BotAdapterStateCheck);
				else
					CONTROL_SwitchToFault(DF_TOP_ADAPTER_MISMATCHED);
				break;

			case SS_BotAdapterStateCheck:
				if (LL_GetStateLimitSwitchBotAdapter())
					CONTROL_SetDeviceState(DS_InProcess, SS_BotAdapterIDCheck);
				else
					CONTROL_SwitchToFault(DF_BOT_ADAPTER_OPENED);
				break;

			case SS_BotAdapterIDCheck:
				LOGIC_AdapterIDMeasure(BOT_ADAPTER);
				LOGIC_AdapterIDMatch();

				if (DataTable[REG_ID_ADPTR_CHECKED] == DataTable[REG_ID_ADPTR_SET])
					CONTROL_SetDeviceState(DS_InProcess, SS_DUTPresenceCheck);
				else
					CONTROL_SwitchToFault(DF_BOT_ADAPTER_MISMATCHED);
				break;

			case SS_DUTPresenceCheck:
				LOGIC_DUTPresenceCheck();
				CONTROL_SetDeviceState(DS_Ready, SS_None);
				break;

			default:
				break;
		}
	}
}
//-----------------------------------------------

void CONTROL_SaveTestResult()
{
	DataTable[REG_OP_RESULT] = OPRESULT_OK;
}
//-----------------------------------------------

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

	CONTROL_SetDeviceSubState(NewSubState);
}
//------------------------------------------

void CONTROL_SetDeviceSubState(DeviceSubState NewSubState)
{
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

