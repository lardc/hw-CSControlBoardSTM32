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

#define PRESSURE_OFFSET_MIN			0.001
#define PRESSURE_OFFSET_MAX			10
#define PRESSURE_OFFSET_DEF			0

#define PRESSURE_K_MIN				0.001
#define PRESSURE_K_MAX				10
#define PRESSURE_K_DEF				1

#define PRESSURE_P2_MIN				0.001
#define PRESSURE_P2_MAX				10
#define PRESSURE_P2_DEF				0

#define PRESSURE_P1_MIN				0.001
#define PRESSURE_P1_MAX				10
#define PRESSURE_P1_DEF				1

#define PRESSURE_P0_MIN				0.001
#define PRESSURE_P0_MAX				10
#define PRESSURE_P0_DEF				0

#define SET_PRESSURE_VALUE_MIN		4		// в Бар
#define SET_PRESSURE_VALUE_MAX		6		// в Бар
#define SET_PRESSURE_VALUE_DEF		5		// в Бар

//
#define NO							0
#define YES							1
//
#define TOP_ADAPTER					0
#define BOT_ADAPTER					1

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
