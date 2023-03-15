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
void CONTROL_LogicProcess();
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
	CONTROL_LogicProcess();

	DEVPROFILE_ProcessRequests();
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

		default:
			return DIAG_HandleDiagnosticAction(ActionID, pUserError);
			
	}
	return true;
}
//-----------------------------------------------

void CONTROL_LogicProcess()
{
	if(CONTROL_State == DS_InProcess)
	{
		switch(CONTROL_SubState)
		{
			case SS_TopAdapterStateCheck:
				DataTable[REG_TOP_ADPTR_STATE] = LL_GetStateLimitSwitchTopAdapter();

				if (DataTable[REG_TOP_ADPTR_STATE])
					CONTROL_SetDeviceState(DS_InProcess, SS_TopAdapterID);
				else
					CONTROL_SwitchToFault(DF_TOP_ADAPTER_OPENED);

				break;

			case SS_TopAdapterID:
				LOGIC_TopAdapterIdentification();
				CONTROL_SetDeviceState(DS_InProcess, SS_TopAdapterIDCheck);
				break;

			case SS_TopAdapterIDCheck:
				if (DataTable[REG_ID_ADPTR_SET] == DataTable[REG_ID_TOP_ADPTR_FACTUAL])
					CONTROL_SetDeviceState(DS_InProcess, SS_BotAdapterStateCheck);
				else
					CONTROL_SwitchToFault(DF_TOP_ADAPTER_MISMATCHED);
				break;

			case SS_BotAdapterStateCheck:
				DataTable[REG_BOT_ADPTR_STATE] = LL_GetStateLimitSwitchBotAdapter();

				if (DataTable[REG_BOT_ADPTR_STATE])
					CONTROL_SetDeviceState(DS_InProcess, SS_BotAdapterID);
				else
					CONTROL_SwitchToFault(DF_BOT_ADAPTER_OPENED);

			case SS_BotAdapterID:
				LOGIC_BotAdapterIdentification();
				CONTROL_SetDeviceState(DS_InProcess, SS_BotAdapterIDCheck);
				break;

			case SS_BotAdapterIDCheck:
				if (DataTable[REG_ID_ADPTR_SET] == DataTable[REG_ID_BOT_ADPTR_FACTUAL])
					CONTROL_SetDeviceState(DS_InProcess, SS_AdaptersMatchingCheck);
				else
					CONTROL_SwitchToFault(DF_BOT_ADAPTER_MISMATCHED);
				break;

			case SS_AdaptersMatchingCheck:
				if (DataTable[REG_ID_TOP_ADPTR_FACTUAL] == DataTable[REG_ID_BOT_ADPTR_FACTUAL])
					CONTROL_SetDeviceState(DS_InProcess, SS_DUTPresenceCheck);
				else
					CONTROL_SwitchToFault(DF_ADAPTERS_MISMATCHED);
				break;

			default:
				break;
		}
	}

	if(CONTROL_State == DS_SelfTest)
		SELFTEST_Process();
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

