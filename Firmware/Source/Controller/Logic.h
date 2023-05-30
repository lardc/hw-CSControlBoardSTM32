#ifndef LOGIC_H_
#define LOGIC_H_

// Types
typedef enum __DUTType
{
	DT_None = 0,
	DT_MIHM = 1,
	DT_MIHV	= 2,
	DT_MISM	= 3,
	DT_MISV	= 4,
	DT_MIXM	= 5,
	DT_MIXV	= 6
} DUTType;

// Functions
//
DUTType LOGIC_AdapterIDMatch(float IDVoltage);
void LOGIC_UpdateSensors();

#endif /* LOGIC_H_ */
