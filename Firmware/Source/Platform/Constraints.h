#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

// Include
#include "stdinc.h"
#include "DataTable.h"
#include "Global.h"

//Definitions
//
#define ADPTR_MCDA_REF_MIN			1		// в мВ
#define ADPTR_MCDA_REF_MAX			3000	// в мВ
#define ADPTR_MCDA_REF_DEF			2345	// в мВ

#define ADPTR_MIAA_REF_MIN			1		// в мВ
#define ADPTR_MIAA_REF_MAX			3000	// в мВ
#define ADPTR_MIAA_REF_DEF			1990	// в мВ

#define ADPTR_MIDA_REF_MIN			1		// в мВ
#define ADPTR_MIDA_REF_MAX			3000	// в мВ
#define ADPTR_MIDA_REF_DEF			2685	// в мВ

#define ADPTR_MIFA_REF_MIN			1		// в мВ
#define ADPTR_MIFA_REF_MAX			3000	// в мВ
#define ADPTR_MIFA_REF_DEF			1		// в мВ

#define ADPTR_MIHA_REF_MIN			1		// в мВ
#define ADPTR_MIHA_REF_MAX			3000	// в мВ
#define ADPTR_MIHA_REF_DEF			1100	// в мВ

#define ADPTR_MIHM_REF_MIN			1		// в мВ
#define ADPTR_MIHM_REF_MAX			3000	// в мВ
#define ADPTR_MIHM_REF_DEF			85		// в мВ

#define ADPTR_MIHV_REF_MIN			1		// в мВ
#define ADPTR_MIHV_REF_MAX			3000	// в мВ
#define ADPTR_MIHV_REF_DEF			162		// в мВ

#define ADPTR_MISM_REF_MIN			1		// в мВ
#define ADPTR_MISM_REF_MAX			3000	// в мВ
#define ADPTR_MISM_REF_DEF			305		// в мВ

#define ADPTR_MISM2_REF_MIN			1		// в мВ
#define ADPTR_MISM2_REF_MAX			3000	// в мВ
#define ADPTR_MISM2_REF_DEF			585		// в мВ

#define ADPTR_MISV_REF_MIN			1		// в мВ
#define ADPTR_MISV_REF_MAX			3000	// в мВ
#define ADPTR_MISV_REF_DEF			466		// в мВ

#define ADPTR_MIXM_REF_MIN			1		// в мВ
#define ADPTR_MIXM_REF_MAX			3000	// в мВ
#define ADPTR_MIXM_REF_DEF			830		// в мВ

#define ADPTR_MIXV_REF_MIN			1		// в мВ
#define ADPTR_MIXV_REF_MAX			3000	// в мВ
#define ADPTR_MIXV_REF_DEF			1445	// в мВ

#define PRESSURE_OFFSET_MIN			0.001
#define PRESSURE_OFFSET_MAX			4095
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
