#ifndef LOGIC_H_
#define LOGIC_H_

// Types
typedef enum __TestType
{
	TT_DUT = 0,
	TT_SelfTest
} TestType;

// Functions
//
void LOGIC_ResetOutputRegisters();
void LOGIC_AdapterIDMeasure(uint16_t Adapter);
void LOGIC_AdapterIDMatch();
void LOGIC_UpdateDiscreteSensors();

#endif /* LOGIC_H_ */
