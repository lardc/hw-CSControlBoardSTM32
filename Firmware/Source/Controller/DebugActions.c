// Header
#include "DebugActions.h"

// Include
//
#include "LowLevel.h"
#include "Board.h"
#include "Delay.h"
#include "Controller.h"
#include "DataTable.h"

// Variables

// Functions

// Send pulse to chosen digital output. Choosing output is available via [REG_DBG] register:	[REG_DBG] = 1 --> GPIO_IND_1,
// 																								[REG_DBG] = 2 --> GPIO_IND_2,
// 																								[REG_DBG] = 3 --> GPIO_PNEUM_1,
// 																								[REG_DBG] = 4 --> GPIO_PNEUM_2,
// 																								[REG_DBG] = 5 --> GPIO_PNEUM_3.
void DBACT_ToggleDigitalOutput()
{
	LL_SetStateDigitalOutput(true);
	DELAY_MS(1000);
	LL_SetStateDigitalOutput(false);
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

// Get state of chosen DUT. Choosing DUT is  available via [REG_DBG] register:	[REG_DBG] = 1 --> GPIO_DUT_1,
// 																				[REG_DBG] = 2 --> GPIO_DUT_2,
// 																				[REG_DBG] = 3 --> GPIO_DUT_3,
// 																				[REG_DBG] = 4 --> GPIO_DUT_4.
void DBACT_GetStateLimitSwitchDUT()
{
	bool MeasurementResult;

	MeasurementResult = LL_GetStateLimitSwitchDUT();
	DataTable[REG_RSLT] = MeasurementResult;
}
//-----------------------

// Get state of chosen side of Adapter. Choosing side is  available via [REG_DBG] register:	[REG_DBG] = 1 --> GPIO_ADPTR_TOP,
// 																							[REG_DBG] = 2 --> GPIO_ADPTR_BOT.
void DBACT_GetStateLimitSwitchAdapter()
{
	bool MeasurementResult;

	MeasurementResult = LL_GetStateLimitSwitchAdapter();
	DataTable[REG_RSLT] = MeasurementResult;
}
//-----------------------

// Measure the voltage at the resistor divider on the top side of the adapter
void DBACT_MeasureIDDividerTop()
{
	float MeasurementResult;

	MeasurementResult = LL_MeasureIDTop();
	DataTable[REG_RSLT] = MeasurementResult;
}
//-----------------------

// Measure the voltage at the resistor divider on the bottom side of the adapter
void DBACT_MeasureIDDividerBot()
{
	float MeasurementResult;

	MeasurementResult = LL_MeasureIDBot();
	DataTable[REG_RSLT] = MeasurementResult;
}
//-----------------------

// Measure the voltage from the pressure sensor
void DBACT_MeasurePressure()
{
	float MeasurementResult;

	MeasurementResult = LL_MeasurePressure();
	DataTable[REG_RSLT] = MeasurementResult;
}
//-----------------------
