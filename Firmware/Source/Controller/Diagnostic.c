// Header
#include "Diagnostic.h"

// Includes
#include "DataTable.h"
#include "LowLevel.h"
#include "Controller.h"
#include "DebugActions.h"

// Functions
bool DIAG_HandleDiagnosticAction(uint16_t ActionID, uint16_t *pUserError)
{
	switch (ActionID)
	{
	case ACT_DBG_DIG_OUT:
		DBACT_ToggleDigitalOutput();
		break;

	case ACT_DBG_SF_OUT:
		DBACT_ToggleSFOutput();
		break;

	case ACT_DBG_LS_DUT:
		DBACT_GetStateLimitSwitchDUT();
		break;

	case ACT_DBG_LS_ADPTR:
		DBACT_GetStateLimitSwitchAdapter();
		break;

	case ACT_DBG_MEASURE_ID_TOP:
		DBACT_MeasureIDDividerTop();
		break;

	case ACT_DBG_MEASURE_ID_BOT:
		DBACT_MeasureIDDividerBot();
		break;

	case ACT_DBG_MEASURE_PRESSURE:
		DBACT_MeasurePressure();
		break;

		default:
			return false;
	}

	return true;
}
//-------------------------------------
