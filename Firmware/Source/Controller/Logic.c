// Includes
#include "Board.h"
#include "Logic.h"
#include "DataTable.h"
#include "LowLevel.h"
#include "Math.h"
#include "Delay.h"
#include "Controller.h"
#include "Constraints.h"

// Functions prototypes
bool LOGIC_IDVoltageInRane(float IDVoltage, Int16U ReferenceReg);

// Functions
//
DUTType LOGIC_AdapterIDMatch(float IDVoltage)
{
	if(LOGIC_IDVoltageInRane(IDVoltage, REG_ADPTR_REF_MIHM))
		return DT_MIHM;
	else if(LOGIC_IDVoltageInRane(IDVoltage, REG_ADPTR_REF_MIHV))
		return DT_MIHV;
	else if(LOGIC_IDVoltageInRane(IDVoltage, REG_ADPTR_REF_MISM))
		return DT_MISM;
	else if(LOGIC_IDVoltageInRane(IDVoltage, REG_ADPTR_REF_MISV))
		return DT_MISV;
	else if(LOGIC_IDVoltageInRane(IDVoltage, REG_ADPTR_REF_MIXM))
		return DT_MIXM;
	else if(LOGIC_IDVoltageInRane(IDVoltage, REG_ADPTR_REF_MIXV))
		return DT_MIXV;
	else
		return DT_None;
}
//------------------------------------------

bool LOGIC_IDVoltageInRane(float IDVoltage, Int16U ReferenceReg)
{
	return (fabsf(IDVoltage - DataTable[ReferenceReg]) / DataTable[ReferenceReg]) < VOLTAGE_ID_MAX_ERR;
}
//------------------------------------------

void LOGIC_UpdateSensors()
{
	DataTable[REF_TL_DUT_PRESENCE] = LL_GetStatePresenceSensorDUT1() ? YES : NO;
	DataTable[REF_TR_DUT_PRESENCE] = LL_GetStatePresenceSensorDUT2() ? YES : NO;
	DataTable[REF_BL_DUT_PRESENCE] = LL_GetStatePresenceSensorDUT3() ? YES : NO;
	DataTable[REF_BR_DUT_PRESENCE] = LL_GetStatePresenceSensorDUT4() ? YES : NO;

	DataTable[REG_SEN_TOP_ADAPTER] = LL_GetStateLimitSwitchTopAdapter() ? YES : NO;
	DataTable[REG_SEN_BOT_ADAPTER] = LL_GetStateLimitSwitchBotAdapter() ? YES : NO;

	DataTable[REG_ID_TOP_ADAPTER] = LOGIC_AdapterIDMatch(LL_MeasureIDTop());
	DataTable[REG_ID_BOT_ADAPTER] = LOGIC_AdapterIDMatch(LL_MeasureIDBot());
}
//------------------------------------------
