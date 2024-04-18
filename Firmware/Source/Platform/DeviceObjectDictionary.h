﻿#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// Команды
#define ACT_ENABLE_POWER				1	// Включение блока
#define ACT_DISABLE_POWER				2	// Выключение блока
#define ACT_CLR_FAULT					3	// Очистка всех fault
#define ACT_CLR_WARNING					4	// Очистка всех warning
#define ACT_CLEAR_HALT					5	// Очистка состояния halt
//
#define ACT_DBG_IND_CSM					20	// Проверка работы индикатора блокировки зажимного устройства
#define ACT_DBG_IND_ADPTR				21	// Проверка работы индикатора блокировки верхнего и нижнего адаптеров
#define ACT_DBG_PNEUM_TOP				22	// Проверка работы управления пневмоцилиндром для блокировки верхнего адаптера
#define ACT_DBG_PNEUM_BOT				23	// Проверка работы управления пневмоцилиндром для блокировки нижнего адаптера
#define ACT_DBG_PNEUM_DUT				24	// Проверка работы управления пневмоцилиндром для блокировки измеряемых устройств
#define ACT_DBG_SF_OUT					25	// Проверка работы выхода системы безопасности
// 26 - 31
#define ACT_DBG_MEASURE_ID_TOP			32	// Проверка работы системы идентификации верхнего адаптера
#define ACT_DBG_MEASURE_ID_BOT			33	// Проверка работы системы идентификации нижнего адаптера
#define ACT_DBG_MEASURE_PRESSURE		34	// Опрос датчика давления

#define ACT_HOMING						100 // Стартовое позиционирование
#define ACT_CLAMP						102	// Фиксация зажимного устройства
#define ACT_RELEASE						104	// Отсоединение зажимного устройства
#define ACT_CHECK_ADPTS_STATUS 			111 // Проверка статуса адаптеров

#define ACT_SAVE_TO_ROM					200	// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM			201	// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT			202	// Сброс DataTable в состояние по умолчанию

#define ACT_BOOT_LOADER_REQUEST			320	// Перезапуск процессора с целью перепрограммирования
// -----------------------------

// Регистры
// Сохраняемые регистры
#define REG_ADPTR_REF_MIHM				0	// Регистр для хранения эталонного значения напряжения (в мВ) адаптера MIHM
#define REG_ADPTR_REF_MIHV				1	// Регистр для хранения эталонного значения напряжения (в мВ) адаптера MIHV
#define REG_ADPTR_REF_MISM				2	// Регистр для хранения эталонного значения напряжения (в мВ) адаптера MISM
#define REG_ADPTR_REF_MISV				3	// Регистр для хранения эталонного значения напряжения (в мВ) адаптера MISV
#define REG_ADPTR_REF_MIXM				4	// Регистр для хранения эталонного значения напряжения (в мВ) адаптера MIXM
#define REG_ADPTR_REF_MIXV				5	// Регистр для хранения эталонного значения напряжения (в мВ) адаптера MIXV
//
#define REG_PRESSURE_OFFSET				6	// Смещение оцифрованного напряжения датчика давления 1 (в тиках)
#define	REG_PRESSURE_K					7	// Коэффициент пересчёта напряжения АЦП (в мВ) в давление (в Бар)
#define REG_PRESSURE_P2					8	// Калибровочный коэффициент P2 измерения давления
#define REG_PRESSURE_P1					9	// Калибровочный коэффициент P1 измерения давления
#define REG_PRESSURE_P0					10	// Калибровочный коэффициент P0 измерения давления
//
#define REG_SET_PRESSURE_VALUE			11	// Допустимый диапазон значения давления (в Бар)
// Несохраняемые регистры чтения-записи
#define REG_FORCE						70  // Усилие зажатия (Совместимость)
#define REG_ID_ADPTR_SET				71	// Регистр для хранения значения идентификатора верхнего/нижнего адаптеров, установленного верхним уровнем (MCU):
											// (1 - MIHM, 2 - MIHV, 3 - MISM, 4 - MISV, 5 - MIXM, 6 - MIXV)
#define REG_TEMP_SET 					72	// Выставление температуры (Совместимость)
//
#define REG_DEV_STATE					96	// Регистр состояния
#define REG_FAULT_REASON				97	// Регистр Fault
#define REG_DISABLE_REASON				98	// Регистр Disable
#define REG_WARNING						99	// Регистр Warning
#define REG_PROBLEM						100	// Регистр Problem
#define REG_OP_RESULT					103	// Регистр результата операции
#define REG_SELF_TEST_OP_RESULT			104 // Регистр результата самотестирования
#define REG_SUB_STATE					105	// Регистр вспомогательного состояния
//
#define REG_TL_DUT_PRESENCE				113	// Регистр присутствия прибора в 1 позиции (верхний левый)
#define REG_TR_DUT_PRESENCE				114	// Регистр присутствия прибора в 2 позиции (верхний правый)
#define REG_BL_DUT_PRESENCE				115 // Регистр присутствия прибора в 3 позиции (нижний левый)
#define REG_BR_DUT_PRESENCE				116 // Регистр присутствия прибора в 4 позиции (нижний правый)
#define REG_TOP_ADPT_MISMATCHED 		117	// Регистр соответствия верхнего адаптера
#define REG_BOT_ADPT_MISMATCHED 		118 // Регистр соответствия нижнего адаптера
#define REG_PRESSURE_VALUE				119 // Регистр текущего значения датчика давления
#define REG_SEN_TOP_ADAPTER				120 // Регистр состояния верхнего адаптера (открыт/закрыт)
#define REG_SEN_BOT_ADAPTER				121 // Регистр состояния верхнего адаптера (открыт/закрыт)
//
#define REG_DBG							150	// Отладочный регистр
#define REG_RSLT						151	// Отладочный регистр для хранения результатов измерений датчиков

// Регистры только чтение
// -----------------------------
#define REG_FWINFO_SLAVE_NID			256	// Device CAN slave node ID
#define REG_FWINFO_MASTER_NID			257	// Device CAN master node ID (if presented)
// 258 - 259
#define REG_FWINFO_STR_LEN				260	// Length of the information string record
#define REG_FWINFO_STR_BEGIN			261	// Begining of the information string record


// Operation results
#define OPRESULT_NONE					0	// No information or not finished
#define OPRESULT_OK						1	// Operation was successful
#define OPRESULT_FAIL					2	// Operation failed

//  Fault and disable codes
#define DF_NONE							0
#define DF_PRESSURE_ERROR_EXCEED		1	// Превышение значения допустимой погрешности

// Problem
#define PROBLEM_NONE					0
#define PROBLEM_TOP_ADAPTER_OPENED		1	// Верхний адаптер не задвинут до конца
#define PROBLEM_BOT_ADAPTER_OPENED		2	// Нижний адаптер не задвинут до конца
#define PROBLEM_TOP_ADAPTER_MISMATCHED	3	// Установленный верхний адаптер не совпадает с заданым адаптером для проведения измерений
#define PROBLEM_BOT_ADAPTER_MISMATCHED	4	// Установленный нижний адаптер не совпадает с заданым адаптером для проведения измерений

//  Warning
#define WARNING_NONE					0

//  User Errors
#define ERR_NONE						0
#define ERR_CONFIGURATION_LOCKED		1	//  Устройство защищено от записи
#define ERR_OPERATION_BLOCKED			2	//  Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY			3	//  Устройство не готово для смены состояния
#define ERR_WRONG_PWD					4	//  Неправильный ключ

// Endpoints

#endif //  __DEV_OBJ_DIC_H
