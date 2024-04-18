#ifndef LOGIC_H_
#define LOGIC_H_

// Types
typedef enum __DUTType
{
	DT_None = 0,
	DT_MCDA,
	DT_MIAA,
	DT_MIDA,
	DT_MIFA,
	DT_MIHA,
	DT_MIHM,
	DT_MIHV,
	DT_MISM,
	DT_MISM2,
	DT_MISV,
	DT_MIXM,
	DT_MIXV,
} DUTType;

// Functions
//
DUTType LOGIC_AdapterIDMatch(float IDVoltage);
void LOGIC_UpdateSensors();

#endif /* LOGIC_H_ */
