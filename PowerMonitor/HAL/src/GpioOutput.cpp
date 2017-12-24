/*
 * GpioOutput.cpp
 *
 *  Created on: 07-Oct-2017
 *      Author: Amit Chaudhary
 */


#include "GpioOutput.hpp"

namespace Bsp
{
GpioOutput::GpioOutput(PORT Port, u16 Pin)
{
	m_Port = Port;
	m_Pin  = Pin;
	m_Mode = GPIO_Mode_Out_PP;

	m_pClockManager = GetClockManager();
}
GpioOutput::GpioOutput(PORT Port, u16 Pin, MODE aMODE)
{
	m_Port = Port;
	m_Pin  = Pin;
	m_Mode = aMODE;

	m_pClockManager = GetClockManager();
}
bool GpioOutput::HwInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	const ClockManager::Peripheral_t  Peripheral =
			             (m_Port==GPIOA)? ClockManager::APB2Periph_GPIOA :
				         (m_Port==GPIOB)? ClockManager::APB2Periph_GPIOB :
				         (m_Port==GPIOC)? ClockManager::APB2Periph_GPIOC :
				         (m_Port==GPIOD)? ClockManager::APB2Periph_GPIOD :
				         (m_Port==GPIOE)? ClockManager::APB2Periph_GPIOE :
				         (m_Port==GPIOF)? ClockManager::APB2Periph_GPIOF : ClockManager::APB2Periph_GPIOG;

	m_pClockManager->PeripheralClockEnable(Peripheral);
	m_pClockManager->PeripheralClockEnable(ClockManager::APB2Periph_AFIO);

	GPIO_InitStructure.GPIO_Pin = m_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = m_Mode;
	GPIO_Init( m_Port, &GPIO_InitStructure );

	// Initially Set the GPIO to Low
	GPIO_WriteBit(m_Port, m_Pin,(BitAction)GpioOutput::LOW);
	return true;
}

void GpioOutput::ToggleOutput()
{
	if ( GpioOutput::LOW == m_eGpioOutputState )
	{
		GPIO_WriteBit(m_Port, m_Pin,(BitAction)GpioOutput::LOW);
		m_eGpioOutputState = GpioOutput::HIGH;
	}
	else
	{
		GPIO_WriteBit(m_Port, m_Pin,(BitAction)GpioOutput::HIGH);
		m_eGpioOutputState = GpioOutput::LOW;
	}

}





}

