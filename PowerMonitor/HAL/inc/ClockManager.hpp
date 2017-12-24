/*
 * ClockManager.hpp
 *
 *  Created on: 14-Oct-2017
 *      Author: Amit Chaudhary
 */

#ifndef APP_INC_CLOCKMANAGER_HPP_
#define APP_INC_CLOCKMANAGER_HPP_

#include "stm32f10x.h"
//#include"stm32f10x_rcc.h"


namespace Bsp
{

class ClockManager
{
public:
	typedef enum
	{
		APB2Periph_AFIO,
		DUMMY1,
		APB2Periph_GPIOA,
		APB2Periph_GPIOB,
		APB2Periph_GPIOC,
		APB2Periph_GPIOD,
		APB2Periph_GPIOE,
		APB2Periph_GPIOF,
		APB2Periph_GPIOG,
		APB2Periph_ADC1,
		APB2Periph_ADC2,
		APB2Periph_TIM1,
		APB2Periph_SPI1,
		APB2Periph_TIM8 ,
		APB2Periph_USART1,
		APB2Periph_ADC3,
		APB2Periph_TIM15,
		APB2Periph_TIM16,
		APB2Periph_TIM17,
		APB2Periph_TIM9,
		APB2Periph_TIM10,
		APB2Periph_TIM11,
		APB1Periph_TIM2,
		APB1Periph_TIM3,
		APB1Periph_TIM4,
		APB1Periph_TIM5,
		APB1Periph_TIM6,
		APB1Periph_TIM7,
		APB1Periph_TIM12,
		APB1Periph_TIM13,
		APB1Periph_TIM14,
		DUMMY2,
		DUMMY3,
		APB1Periph_WWDG,
		DUMMY4,
		DUMMY5,
		APB1Periph_SPI2,
		APB1Periph_SPI3,
		DUMMY6,
		APB1Periph_USART2,
		APB1Periph_USART3,
		APB1Periph_UART4,
		APB1Periph_UART5,
		APB1Periph_I2C1,
		APB1Periph_I2C2,
		APB1Periph_USB,
		DUMMY7,
		APB1Periph_CAN1,
		APB1Periph_CAN2,
		APB1Periph_BKP,
		APB1Periph_PWR,
		APB1Periph_DAC,
		APB1Periph_CEC,
		AHBPeriph_DMA1,
		AHBPeriph_DMA2,
		AHBPeriph_SRAM,
		DUMMY8,
		AHBPeriph_FLITF,
		DUMMY9,
		AHBPeriph_CRC
	}Peripheral_t;
	void PeripheralClockEnable(Peripheral_t RCC_Periph);
	void PeripheralClockDisble(Peripheral_t RCC_Periph);
	static ClockManager* GetInstance();
private:
	static ClockManager* m_pClockManager;
};

}//namespace bsp
#endif /* APP_INC_CLOCKMANAGER_HPP_ */
