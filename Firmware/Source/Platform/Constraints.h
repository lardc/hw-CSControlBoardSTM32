#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

// Include
#include "stdinc.h"
#include "DataTable.h"
#include "Global.h"

//Definitions
//
#define ADPTR_MIHM_REF_MIN			140		// в мВ
#define ADPTR_MIHM_REF_MAX			180		// в мВ
#define ADPTR_MIHM_REF_DEF			160		// в мВ

#define ADPTR_MIHV_REF_MIN			280		// в мВ
#define ADPTR_MIHV_REF_MAX			420		// в мВ
#define ADPTR_MIHV_REF_DEF			340		// в мВ

#define ADPTR_MISM_REF_MIN			560		// в мВ
#define ADPTR_MISM_REF_MAX			800		// в мВ
#define ADPTR_MISM_REF_DEF			680		// в мВ

#define ADPTR_MISV_REF_MIN			900		// в мВ
#define ADPTR_MISV_REF_MAX			1200	// в мВ
#define ADPTR_MISV_REF_DEF			1000	// в мВ

#define ADPTR_MIXM_REF_MIN			1450	// в мВ
#define ADPTR_MIXM_REF_MAX			1900	// в мВ
#define ADPTR_MIXM_REF_DEF			1670	// в мВ

#define ADPTR_MIXV_REF_MIN			2250	// в мВ
#define ADPTR_MIXV_REF_MAX			2750	// в мВ
#define ADPTR_MIXV_REF_DEF			2500	// в мВ
//
#define NO							0
#define YES							1
//
#define TOP_ADAPTER					0
#define BOT_ADAPTER					1
//
#define NOT_INSTALLED				0
#define INSTALLED					1

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
