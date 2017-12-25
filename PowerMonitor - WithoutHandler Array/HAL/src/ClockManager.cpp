/*
 * ClockManager.cpp
 *
 *  Created on: 14-Oct-2017
 *      Author: Amit Chaudhary
 */

#include "ClockManager.hpp"

namespace Bsp
{
ClockManager* ClockManager::m_pClockManager = nullptr;


ClockManager* ClockManager::GetInstance()
{
	if(m_pClockManager==nullptr)
	{
		static ClockManager ClockManager_Instance;
		m_pClockManager = &ClockManager_Instance;
	}
	return m_pClockManager;

}


/**
  * @brief  Enables or disables the High Speed APB (APB2) peripheral clock.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_APB2Periph_AFIO, RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB,
  *          RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD, RCC_APB2Periph_GPIOE,
  *          RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG, RCC_APB2Periph_ADC1,
  *          RCC_APB2Periph_ADC2, RCC_APB2Periph_TIM1, RCC_APB2Periph_SPI1,
  *          RCC_APB2Periph_TIM8, RCC_APB2Periph_USART1, RCC_APB2Periph_ADC3,
  *          RCC_APB2Periph_TIM15, RCC_APB2Periph_TIM16, RCC_APB2Periph_TIM17,
  *          RCC_APB2Periph_TIM9, RCC_APB2Periph_TIM10, RCC_APB2Periph_TIM11
  * @retval None
  */



void ClockManager::PeripheralClockEnable(Peripheral_t RCC_Periph)
{
	Peripheral_t BitAdjusted;

	if(RCC_Periph>= APB2Periph_AFIO && RCC_Periph<= APB2Periph_TIM11 )
	{
		RCC_APB2PeriphClockCmd( 1U<<RCC_Periph, ENABLE);
	}
	else if (RCC_Periph>= APB1Periph_TIM2 && RCC_Periph<= APB1Periph_CEC )
	{
		BitAdjusted = static_cast<Peripheral_t>(RCC_Periph - APB1Periph_TIM2);
		RCC_APB1PeriphClockCmd( 1U<<BitAdjusted, ENABLE);
	}
	else if (RCC_Periph>= AHBPeriph_DMA1 && RCC_Periph<= AHBPeriph_CRC )
	{
		BitAdjusted = static_cast<Peripheral_t>(RCC_Periph - AHBPeriph_DMA1);
		RCC_AHBPeriphClockCmd( 1U<<RCC_Periph, ENABLE);
	}
	else
	{
		// Nothing to do
	}

}

void ClockManager::PeripheralClockDisble(Peripheral_t RCC_Periph)
{
	Peripheral_t BitAdjusted;

	if(RCC_Periph>= APB2Periph_AFIO && RCC_Periph<= APB2Periph_TIM11 )
	{
		RCC_APB2PeriphClockCmd( 1U<<RCC_Periph, DISABLE);
	}
	else if (RCC_Periph>= APB1Periph_TIM2 && RCC_Periph<= APB1Periph_CEC )
	{
		BitAdjusted = static_cast<Peripheral_t>(RCC_Periph - APB1Periph_TIM2);
		RCC_APB1PeriphClockCmd( 1U<<BitAdjusted, DISABLE);
	}
	else if (RCC_Periph>= AHBPeriph_DMA1 && RCC_Periph<= AHBPeriph_CRC )
	{
		BitAdjusted = static_cast<Peripheral_t>(RCC_Periph - AHBPeriph_DMA1);
		RCC_AHBPeriphClockCmd( 1U<<RCC_Periph, DISABLE);
	}
	else
	{
		// Nothing to do
	}

}

}// namespace Bsp
