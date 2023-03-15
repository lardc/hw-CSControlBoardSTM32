#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

// Include
#include "stdinc.h"
#include "DataTable.h"
#include "Global.h"

//Definitions
//
#define ADPTR_MIHM_MIN				140		// в мВ
#define ADPTR_MIHM_MAX				180		// в мВ
#define ADPTR_MIHV_MIN				280		// в мВ
#define ADPTR_MIHV_MAX				420		// в мВ
#define ADPTR_MISM_MIN				560		// в мВ
#define ADPTR_MISM_MAX				800		// в мВ
#define ADPTR_MISV_MIN				900		// в мВ
#define ADPTR_MISV_MAX				1200	// в мВ
#define ADPTR_MIXM_MIN				1450	// в мВ
#define ADPTR_MIXM_MAX				1900	// в мВ
#define ADPTR_MIXV_MIN				2250	// в мВ
#define ADPTR_MIXV_MAX				2750	// в мВ
//
#define NO							0
#define YES							1
//
#define MIHM						0
#define MIHV						1
#define MISM						2
#define MISV						3
#define MIXM						4
#define MIXV						5
//

// Types
typedef struct __TableItemConstraint
{
	float Min;
	float Max;
	float Default;
} TableItemConstraint;

// Variables
extern const TableItemConstraint Constraint[];

#endif // __CONSTRAINTS_H
