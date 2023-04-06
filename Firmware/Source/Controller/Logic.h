#ifndef LOGIC_H_
#define LOGIC_H_

// Includes
//

typedef enum __TestType
{
	TT_DUT = 0,
	TT_SelfTest
} TestType;

// Variables
//

// Functions
//
void LOGIC_ResetOutputRegisters();
void LOGIC_AdapterIDMeasure(uint16_t Adapter);
void LOGIC_AdapterIDMatch();
void LOGIC_DUTPresenceCheck();

#endif /* LOGIC_H_ */
