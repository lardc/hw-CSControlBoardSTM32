#include "InitConfig.h"
#include "Board.h"
#include "SysConfig.h"
#include "BCCIxParams.h"

// Functions
//
Boolean INITCFG_ConfigSystemClock()
{
	return RCC_PLL_HSE_Config(QUARTZ_FREQUENCY, PREDIV_4, PLL_14);
}
//------------------------------------------------

void INITCFG_ConfigIO()
{
	// Включение тактирования портов
	RCC_GPIO_Clk_EN(PORTA);
	RCC_GPIO_Clk_EN(PORTB);
	RCC_GPIO_Clk_EN(PORTC);
	
	// Выходы
	GPIO_InitPushPullOutput(GPIO_LED);
	GPIO_InitPushPullOutput(GPIO_IND_1);
	GPIO_InitPushPullOutput(GPIO_IND_2);
	GPIO_InitPushPullOutput(GPIO_PNEUM_1);
	GPIO_InitPushPullOutput(GPIO_PNEUM_2);
	GPIO_InitPushPullOutput(GPIO_PNEUM_3);
	GPIO_InitPushPullOutput(GPIO_SF_OUT);

	// Входы
	GPIO_InitInput(GPIO_DUT_1, NoPull);
	GPIO_InitInput(GPIO_DUT_2, NoPull);
	GPIO_InitInput(GPIO_DUT_3, NoPull);
	GPIO_InitInput(GPIO_DUT_4, NoPull);
	GPIO_InitInput(GPIO_ADPTR_TOP, NoPull);
	GPIO_InitInput(GPIO_ADPTR_BOT, NoPull);

	// Начальная установка состояний выводов
	GPIO_SetState(GPIO_LED, false);
	GPIO_SetState(GPIO_IND_1, false);
	GPIO_SetState(GPIO_IND_2, true);
	GPIO_SetState(GPIO_PNEUM_1, true);
	GPIO_SetState(GPIO_PNEUM_2, true);
	GPIO_SetState(GPIO_PNEUM_3, false);
	GPIO_SetState(GPIO_SF_OUT, false);

	// Альтернативные функции
	GPIO_InitAltFunction(GPIO_ALT_UART1_RX, AltFn_7);
	GPIO_InitAltFunction(GPIO_ALT_UART1_TX, AltFn_7);
	GPIO_InitAltFunction(GPIO_ALT_CAN1_RX, AltFn_9);
	GPIO_InitAltFunction(GPIO_ALT_CAN1_TX, AltFn_9);
}

//------------------------------------------------

void INITCFG_ConfigUART()
{
	USART_Init(USART1, SYSCLK, USART_BAUDRATE);
	USART_Recieve_Interupt(USART1, 0, true);
}
//------------------------------------------------

void INITCFG_ConfigTimer7()
{
	TIM_Clock_En(TIM_7);
	TIM_Config(TIM7, SYSCLK, TIMER7_uS);
	TIM_Interupt(TIM7, 2, true);
	TIM_Start(TIM7);
}
//------------------------------------------------

void INITCFG_ConfigWatchDog()
{
	IWDG_Config();
	IWDG_ConfigureSlowUpdate();
}
//------------------------------------------------

void INITCFG_ConfigADC()
{
	RCC_ADC_Clk_EN(ADC_12_ClkEN);

	// ADC1
	ADC_Calibration(ADC1);
	ADC_SoftTrigConfig(ADC1);
	ADC_Enable(ADC1);
}
//-----------------------------------------------
