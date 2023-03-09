#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "Board.h"
#include "stdinc.h"


// Functions
//
void LL_ToggleBoardLED();
void LL_SetStateDigitalOutput(bool State);
void LL_SetStateSFOutput(bool State);
bool LL_GetStateLimitSwitchDUT();
bool LL_GetStateLimitSwitchAdapter();
float LL_MeasureIDTop();
float LL_MeasureIDBot();
float LL_MeasurePressure();

#endif //__LOWLEVEL_H
