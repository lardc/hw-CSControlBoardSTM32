#ifndef __CONTROLLER_H
#define __CONTROLLER_H

// Include
//
#include "stdinc.h"
#include "Global.h"

// Types
//
typedef enum __DeviceState
{
	DS_None					= 0,
	DS_Fault				= 1,
	DS_Disabled 			= 2,
	DS_Ready 				= 3,
	DS_InProcess 			= 4
} DeviceState;

typedef enum __DeviceSubState
{
	SS_None = 0,
	SS_TopAdapterStateCheck	= 1,
	SS_TopAdapterIDCheck	= 2,
	SS_BotAdapterStateCheck	= 3,
	SS_BotAdapterIDCheck	= 4,
	SS_DUTPresenceCheck		= 5,
	SS_DUTPresenceCheck1	= 6
} DeviceSubState;

typedef enum __ClampState
{
	CS_None					= 0,
	CS_ClampPressureCheck 	= 1,
	CS_ClampEngage 			= 2,
	CS_ClampDisengage 		= 3
} ClampState;

// Variables
//
extern volatile Int64U CONTROL_TimeCounter;
extern volatile DeviceState CONTROL_State;
extern volatile DeviceSubState CONTROL_SubState;
extern Int64U CONTROL_LEDTimeout;

// Functions
//
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_DelayMs(uint32_t Delay);
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_SetDeviceState(DeviceState NewState, DeviceSubState NewSubState);

#endif // __CONTROLLER_H
