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
void LOGIC_TopAdapterIdentification()
{
	DataTable[REG_ID_TOP_ADPTR_FACTUAL] = LL_MeasureIDTop();

	if (DataTable[REG_ID_TOP_ADPTR_FACTUAL] == REG_ADPTR_MIHM)
		DataTable[REG_ID_TOP_ADPTR] = MIHM;
	else if (DataTable[REG_ID_TOP_ADPTR_FACTUAL] == REG_ADPTR_MIHV)
		DataTable[REG_ID_TOP_ADPTR] = MIHV;
	else if (DataTable[REG_ID_TOP_ADPTR_FACTUAL] == REG_ADPTR_MISM)
		DataTable[REG_ID_TOP_ADPTR] = MISM;
	else if (DataTable[REG_ID_TOP_ADPTR_FACTUAL] == REG_ADPTR_MISV)
		DataTable[REG_ID_TOP_ADPTR] = MISV;
	else if (DataTable[REG_ID_TOP_ADPTR_FACTUAL] == REG_ADPTR_MIXM)
		DataTable[REG_ID_TOP_ADPTR] = MIXM;
	else if (DataTable[REG_ID_TOP_ADPTR_FACTUAL] == REG_ADPTR_MIXV)
		DataTable[REG_ID_TOP_ADPTR] = MIXV;
}
//------------------------------------------

void LOGIC_BotAdapterIdentification()
{
	DataTable[REG_ID_BOT_ADPTR_FACTUAL] = LL_MeasureIDBot();

	if (DataTable[REG_ID_BOT_ADPTR_FACTUAL] == REG_ADPTR_MIHM)
		DataTable[REG_ID_BOT_ADPTR] = MIHM;
	else if (DataTable[REG_ID_BOT_ADPTR_FACTUAL] == REG_ADPTR_MIHV)
		DataTable[REG_ID_BOT_ADPTR] = MIHV;
	else if (DataTable[REG_ID_BOT_ADPTR_FACTUAL] == REG_ADPTR_MISM)
		DataTable[REG_ID_BOT_ADPTR] = MISM;
	else if (DataTable[REG_ID_BOT_ADPTR_FACTUAL] == REG_ADPTR_MISV)
		DataTable[REG_ID_BOT_ADPTR] = MISV;
	else if (DataTable[REG_ID_BOT_ADPTR_FACTUAL] == REG_ADPTR_MIXM)
		DataTable[REG_ID_BOT_ADPTR] = MIXM;
	else if (DataTable[REG_ID_BOT_ADPTR_FACTUAL] == REG_ADPTR_MIXV)
		DataTable[REG_ID_BOT_ADPTR] = MIXV;
}
//------------------------------------------
