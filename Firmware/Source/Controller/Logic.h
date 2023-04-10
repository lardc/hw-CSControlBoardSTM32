#ifndef LOGIC_H_
#define LOGIC_H_

// Types
typedef enum __DUTType
{
	DT_None = 0,
	DT_MIHM,
	DT_MIHV,
	DT_MISM,
	DT_MISV,
	DT_MIXM,
	DT_MIXV
} DUTType;

// Functions
//
void LOGIC_ResetOutputRegisters();
DUTType LOGIC_AdapterIDMatch(float IDVoltage);
void LOGIC_UpdateDiscreteSensors();

#endif /* LOGIC_H_ */
