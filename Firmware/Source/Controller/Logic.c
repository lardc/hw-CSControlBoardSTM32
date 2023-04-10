// Includes
#include "Board.h"
#include "Logic.h"
#include "DataTable.h"
#include "LowLevel.h"
#include "Math.h"
#include "Delay.h"
#include "Controller.h"
#include "Constraints.h"

// Variables
//

// Functions prototypes

// Functions
//
void LOGIC_ResetOutputRegisters()
{
	DataTable[REG_FAULT_REASON] = DF_NONE;
	DataTable[REG_DISABLE_REASON] = DF_NONE;
	DataTable[REG_WARNING] = WARNING_NONE;
	DataTable[REG_PROBLEM] = PROBLEM_NONE;
	DataTable[REG_OP_RESULT] = OPRESULT_NONE;
	//
	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
}
//------------------------------------------

//
void LOGIC_AdapterIDMeasure(uint16_t Adapter)
{
	if(Adapter == TOP_ADAPTER)
		DataTable[REG_ID_ADPTR_FACTUAL] = LL_MeasureIDTop();
	else
		DataTable[REG_ID_ADPTR_FACTUAL] = LL_MeasureIDBot();
}
//------------------------------------------

void LOGIC_AdapterIDMatch()
{
	if(DataTable[REG_ID_ADPTR_FACTUAL] <= REG_ADPTR_REF_MIHM)
		DataTable[REG_ID_ADPTR_CHECKED] = MIHM;
	else if(DataTable[REG_ID_ADPTR_FACTUAL] <= REG_ADPTR_REF_MIHV)
		DataTable[REG_ID_ADPTR_CHECKED] = MIHV;
	else if(DataTable[REG_ID_ADPTR_FACTUAL] <= REG_ADPTR_REF_MISM)
		DataTable[REG_ID_ADPTR_CHECKED] = MISM;
	else if(DataTable[REG_ID_ADPTR_FACTUAL] <= REG_ADPTR_REF_MISV)
		DataTable[REG_ID_ADPTR_CHECKED] = MISV;
	else if(DataTable[REG_ID_ADPTR_FACTUAL] <= REG_ADPTR_REF_MIXM)
		DataTable[REG_ID_ADPTR_CHECKED] = MIXM;
	else if(DataTable[REG_ID_ADPTR_FACTUAL] <= REG_ADPTR_REF_MIXV)
		DataTable[REG_ID_ADPTR_CHECKED] = MIXV;
}
//------------------------------------------

void LOGIC_UpdateDiscreteSensors()
{
	DataTable[REF_TL_DUT_PRESENCE] = LL_GetStatePresenceSensorDUT1() ? YES : NO;
	DataTable[REF_TR_DUT_PRESENCE] = LL_GetStatePresenceSensorDUT2() ? YES : NO;
	DataTable[REF_BL_DUT_PRESENCE] = LL_GetStatePresenceSensorDUT3() ? YES : NO;
	DataTable[REF_BR_DUT_PRESENCE] = LL_GetStatePresenceSensorDUT4() ? YES : NO;

	DataTable[REG_SEN_TOP_ADAPTER] = LL_GetStateLimitSwitchTopAdapter() ? YES : NO;
	DataTable[REG_SEN_BOT_ADAPTER] = LL_GetStateLimitSwitchBotAdapter() ? YES : NO;
}
//------------------------------------------
