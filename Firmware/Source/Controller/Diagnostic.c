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
	switch(ActionID)
	{
		case ACT_DBG_IND_CSM:
			DBACT_ToggleIndCSM();
			break;
			
		case ACT_DBG_IND_ADPTR:
			DBACT_ToggleIndADPTR();
			break;
			
		case ACT_DBG_PNEUM_TOP:
			DBACT_TogglePneumTOP();
			break;
			
		case ACT_DBG_PNEUM_BOT:
			DBACT_TogglePneumBOT();
			break;
			
		case ACT_DBG_PNEUM_DUT:
			DBACT_TogglePneumDUT();
			break;
			
		case ACT_DBG_SF_OUT:
			DBACT_ToggleSFOutput();
			break;
			
		case ACT_DBG_PRESENCE_DUT1:
			DBACT_GetStatePresenceSensorDUT1();
			break;
			
		case ACT_DBG_PRESENCE_DUT2:
			DBACT_GetStatePresenceSensorDUT2();
			break;
			
		case ACT_DBG_PRESENCE_DUT3:
			DBACT_GetStatePresenceSensorDUT3();
			break;
			
		case ACT_DBG_PRESENCE_DUT4:
			DBACT_GetStatePresenceSensorDUT4();
			break;
			
		case ACT_DBG_STATE_LS_TOP:
			DBACT_GetStateLimitSwitchTOP();
			break;
			
		case ACT_DBG_STATE_LS_BOT:
			DBACT_GetStateLimitSwitchBOT();
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
