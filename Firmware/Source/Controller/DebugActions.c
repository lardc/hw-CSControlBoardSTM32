// Header
#include "DebugActions.h"

// Include
//
#include "LowLevel.h"
#include "Board.h"
#include "Delay.h"
#include "Controller.h"
#include "DataTable.h"

// Functions
// Send pulse to "CSM Block" indicator
void DBACT_ToggleIndCSM()
{
	LL_SetStateIndCSM(true);
	DELAY_MS(1000);
	LL_SetStateIndCSM(false);
}
//-----------------------

// Send pulse to "Adapter Block" indicator
void DBACT_ToggleIndADPTR()
{
	LL_SetStateIndADPTR(true);
	DELAY_MS(1000);
	LL_SetStateIndADPTR(false);
}
//-----------------------

// Send pulse to Top adapter blocking pneumatic cylinder
void DBACT_TogglePneumTOP()
{
	LL_SetStatePneumTOP(true);
	DELAY_MS(1000);
	LL_SetStatePneumTOP(false);
}
//-----------------------

// Send pulse to Bottom adapter blocking pneumatic cylinder
void DBACT_TogglePneumBOT()
{
	LL_SetStatePneumBOT(true);
	DELAY_MS(1000);
	LL_SetStatePneumBOT(false);
}
//-----------------------

// Send pulse to DUT blocking pneumatic cylinder
void DBACT_TogglePneumDUT()
{
	LL_SetStatePneumDUT(true);
	DELAY_MS(1000);
	LL_SetStatePneumDUT(false);
}
//-----------------------

// Send pulse to Safety Subsystem Output
void DBACT_ToggleSFOutput()
{
	LL_SetStateSFOutput(true);
	DELAY_MS(1000);
	LL_SetStateSFOutput(false);
}
//-----------------------

// Get state of presence sensor of DUT1
void DBACT_GetStatePresenceSensorDUT1()
{
	DataTable[REG_RSLT] = LL_GetStatePresenceSensorDUT1();
}
//-----------------------

// Get state of presence sensor of DUT2
void DBACT_GetStatePresenceSensorDUT2()
{
	DataTable[REG_RSLT] = LL_GetStatePresenceSensorDUT2();
}
//-----------------------

// Get state of presence sensor of DUT3
void DBACT_GetStatePresenceSensorDUT3()
{
	DataTable[REG_RSLT] = LL_GetStatePresenceSensorDUT3();
}
//-----------------------

// Get state of presence sensor of DUT4
void DBACT_GetStatePresenceSensorDUT4()
{
	DataTable[REG_RSLT] = LL_GetStatePresenceSensorDUT4();
}
//-----------------------

// Get state of limit switch at the top adapter
void DBACT_GetStateLimitSwitchTOP()
{
	DataTable[REG_RSLT] = LL_GetStateLimitSwitchTopAdapter();
}
//-----------------------

// Get state of limit switch at the bottom adapter
void DBACT_GetStateLimitSwitchBOT()
{
	DataTable[REG_RSLT] = LL_GetStateLimitSwitchBotAdapter();
}
//-----------------------

// Measure voltage at the resistor divider on the top side of the adapter
void DBACT_MeasureIDDividerTop()
{
	float MeasurementResult;

	MeasurementResult = LL_MeasureIDTop();
	DataTable[REG_RSLT] = MeasurementResult;
}
//-----------------------

// Measure voltage at the resistor divider on the bottom side of the adapter
void DBACT_MeasureIDDividerBot()
{
	float MeasurementResult;

	MeasurementResult = LL_MeasureIDBot();
	DataTable[REG_RSLT] = MeasurementResult;
}
//-----------------------

// Measure voltage from the pressure sensor
void DBACT_MeasurePressure()
{
	float MeasurementResult;

	MeasurementResult = LL_MeasurePressure();
	DataTable[REG_RSLT] = MeasurementResult;
}
//-----------------------
