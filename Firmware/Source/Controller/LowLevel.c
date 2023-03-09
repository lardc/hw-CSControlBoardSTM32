// Header
#include "LowLevel.h"
// Include
#include "Board.h"
#include "Delay.h"
#include "Global.h"
#include "DataTable.h"

// Functions
//
void LL_ToggleBoardLED()
{
	GPIO_Toggle(GPIO_LED);
}
//-----------------------------

void LL_SetStateDigitalOutput(bool State)
{
	if (DataTable[REG_DBG] == 1)
		GPIO_SetState(GPIO_IND_1, State);
	else if (DataTable[REG_DBG] == 2)
		GPIO_SetState(GPIO_IND_2, State);
	else if (DataTable[REG_DBG] == 3)
		GPIO_SetState(GPIO_PNEUM_1, State);
	else if (DataTable[REG_DBG] == 4)
		GPIO_SetState(GPIO_PNEUM_1, State);
	else if (DataTable[REG_DBG] == 5)
		GPIO_SetState(GPIO_PNEUM_1, State);
	else if (DataTable[REG_DBG] == 0)
	{
		GPIO_SetState(GPIO_IND_1, false);
		GPIO_SetState(GPIO_IND_2, false);
		GPIO_SetState(GPIO_PNEUM_1, false);
		GPIO_SetState(GPIO_PNEUM_2, false);
		GPIO_SetState(GPIO_PNEUM_3, false);
	}
}
//-----------------------------

void LL_SetStateSFOutput(bool State)
{
	GPIO_SetState(GPIO_SF_OUT, State);
}
//-----------------------------

bool LL_GetStateLimitSwitchDUT()
{
	bool MeasuredResult;

	if (DataTable[REG_DBG] == 1)
		MeasuredResult = GPIO_GetState(GPIO_DUT_1);
	if (DataTable[REG_DBG] == 2)
		MeasuredResult = GPIO_GetState(GPIO_DUT_2);
	if (DataTable[REG_DBG] == 3)
		MeasuredResult = GPIO_GetState(GPIO_DUT_3);
	if (DataTable[REG_DBG] == 4)
		MeasuredResult = GPIO_GetState(GPIO_DUT_4);

	return MeasuredResult;
}
//-----------------------------

bool LL_GetStateLimitSwitchAdapter()
{
	bool MeasuredResult;

	if (DataTable[REG_DBG] == 1)
		MeasuredResult = GPIO_GetState(GPIO_ADPTR_TOP);
	if (DataTable[REG_DBG] == 2)
		MeasuredResult = GPIO_GetState(GPIO_ADPTR_BOT);

	return MeasuredResult;
}
//-----------------------------

float LL_MeasureIDTop()
{
	float MeasuredVoltageIDTop;

	// Measure test-point and convert value to voltage
	MeasuredVoltageIDTop = (float)ADC_Measure(ADC1, ADC_ID_TOP_CHANNEL) * ADC_REF_VOLTAGE / ADC_RESOLUTION;

	return MeasuredVoltageIDTop;
}
//-----------------------------

float LL_MeasureIDBot()
{
	float MeasuredVoltageIDBot;

	// Measure test-point and convert value to voltage
	MeasuredVoltageIDBot = (float)ADC_Measure(ADC1, ADC_ID_BOT_CHANNEL) * ADC_REF_VOLTAGE / ADC_RESOLUTION;

	return MeasuredVoltageIDBot;
}
//-----------------------------

float LL_MeasurePressure()
{
	float MeasuredVoltagePressure;

	// Measure test-point and convert value to voltage
	MeasuredVoltagePressure = (float)ADC_Measure(ADC1, ADC_ID_PRESSURE_CHANNEL) * ADC_REF_VOLTAGE / ADC_RESOLUTION;

	return MeasuredVoltagePressure;
}
//-----------------------------
