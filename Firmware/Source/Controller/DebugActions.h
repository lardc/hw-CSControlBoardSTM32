#ifndef __DEBUGACTIONS_H
#define __DEBUGACTIONS_H

// Include
//
#include "ZwBase.h"

// Functions
//
void DBACT_ToggleIndCSM();
void DBACT_ToggleIndADPTR();
void DBACT_TogglePneumTOP();
void DBACT_TogglePneumBOT();
void DBACT_TogglePneumDUT();
void DBACT_ToggleSFOutput();
void DBACT_GetStatePresenceSensorDUT1();
void DBACT_GetStatePresenceSensorDUT2();
void DBACT_GetStatePresenceSensorDUT3();
void DBACT_GetStatePresenceSensorDUT4();
void DBACT_GetStateLimitSwitchTOP();
void DBACT_GetStateLimitSwitchBOT();
void DBACT_MeasureIDDividerTop();
void DBACT_MeasureIDDividerBot();
void DBACT_MeasurePressure();

#endif //__DEBUGACTIONS_H
