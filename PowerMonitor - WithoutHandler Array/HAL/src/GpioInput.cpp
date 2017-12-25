/*
 * GpioInput.cpp
 *
 *  Created on: 08-Oct-2017
 *      Author: Amit Chaudhary
 */


#include "GpioInput.hpp"
#include "misc.h"
#include "stm32f10x_exti.h"
#include "InterruptManager.hpp"

namespace Bsp
{

GpioInput::GpioInput(PORT Port, u16 Pin)
{
	m_Port = Port;
	m_Pin = Pin;
	m_pISR = nullptr;
	m_eEdge = EXTI_Trigger_Falling;
	m_eEXTIMode = EXTI_Mode_Interrupt;
	m_pInterruptManager = GetInterruptManager();
	m_pClockManager = GetClockManager();
}

GpioInput::GpioInput(PORT Port, u16 Pin, InterruptManager::ISR aISR,
		             IntOnWhichEdge eIntOnWhichEdge )
{
	m_Port = Port;
	m_Pin = Pin;
	m_pISR = aISR;
	m_eEdge = eIntOnWhichEdge;
	m_eEXTIMode = EXTI_Mode_Interrupt;
	m_pInterruptManager = GetInterruptManager();
	m_pClockManager = GetClockManager();
}

GpioInput::GpioInput(PORT Port, u16 Pin, InterruptManager::ISR aISR,
		             IntOnWhichEdge eIntOnWhichEdge, EXTIMode eEXTIMode )
{
	m_Port = Port;
	m_Pin = Pin;
	m_pISR = aISR;
	m_eEdge = eIntOnWhichEdge;
	m_eEXTIMode = eEXTIMode;
	m_pInterruptManager = GetInterruptManager();
	m_pClockManager = GetClockManager();
}

InterruptManager::IRQn GpioInput::MapPin2ExtLine()
{
	const InterruptManager::IRQn ExtLine =
			(GpioInput::m_Pin == GPIO_Pin_0) ? InterruptManager::EXTI0_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_1) ? InterruptManager::EXTI1_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_2) ? InterruptManager::EXTI2_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_3) ? InterruptManager::EXTI3_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_4) ? InterruptManager::EXTI4_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_5) ? InterruptManager::EXTI5_IRQHandler :
			(GpioInput::m_Pin == GPIO_Pin_6) ? InterruptManager::EXTI6_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_7) ? InterruptManager::EXTI7_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_8) ? InterruptManager::EXTI8_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_9) ? InterruptManager::EXTI9_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_10)? InterruptManager::EXTI10_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_11)? InterruptManager::EXTI11_IRQHandler :
			(GpioInput::m_Pin == GPIO_Pin_12)? InterruptManager::EXTI12_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_13)? InterruptManager::EXTI13_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_14)? InterruptManager::EXTI14_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_15)? InterruptManager::EXTI15_IRQHandler : InterruptManager::EXTI0_IRQHandler;

	return ExtLine;
}

u8 GpioInput::MapPin2PinSource()
{
	const u8 PinSource = (GpioInput::m_Pin == GPIO_Pin_0) ? 0  :
					     (GpioInput::m_Pin == GPIO_Pin_1) ? 1  :
						 (GpioInput::m_Pin == GPIO_Pin_2) ? 2  :
						 (GpioInput::m_Pin == GPIO_Pin_3) ? 3  :
						 (GpioInput::m_Pin == GPIO_Pin_4) ? 4  :
						 (GpioInput::m_Pin == GPIO_Pin_5) ? 5  :
						 (GpioInput::m_Pin == GPIO_Pin_6) ? 6  :
			             (GpioInput::m_Pin == GPIO_Pin_7) ? 7  :
			             (GpioInput::m_Pin == GPIO_Pin_8) ? 8  :
			             (GpioInput::m_Pin == GPIO_Pin_9) ? 9  :
			             (GpioInput::m_Pin == GPIO_Pin_10)? 10 :
			             (GpioInput::m_Pin == GPIO_Pin_11)? 11 :
						 (GpioInput::m_Pin == GPIO_Pin_12)? 12 :
			             (GpioInput::m_Pin == GPIO_Pin_13)? 13 :
			             (GpioInput::m_Pin == GPIO_Pin_14)? 14 :
			             (GpioInput::m_Pin == GPIO_Pin_15)? 15 : 0;

	return PinSource;
}

bool GpioInput::HwInit()
{
	const ClockManager::Peripheral_t  Peripheral =
			             (m_Port==GPIOA)? ClockManager::APB2Periph_GPIOA :
				         (m_Port==GPIOB)? ClockManager::APB2Periph_GPIOB :
				         (m_Port==GPIOC)? ClockManager::APB2Periph_GPIOC :
				         (m_Port==GPIOD)? ClockManager::APB2Periph_GPIOD :
				         (m_Port==GPIOE)? ClockManager::APB2Periph_GPIOE :
				         (m_Port==GPIOF)? ClockManager::APB2Periph_GPIOF : ClockManager::APB2Periph_GPIOG;

	GPIO_InitTypeDef GPIO_InitStructure;


	m_pClockManager->PeripheralClockEnable(Peripheral);
	m_pClockManager->PeripheralClockEnable(ClockManager::APB2Periph_AFIO);


	//m_pClockManager->PeripheralClockEnable(ClockManager::APB2Periph_GPIOB);
	//m_pClockManager->PeripheralClockEnable(ClockManager::APB2Periph_GPIOC);


	GPIO_InitStructure.GPIO_Pin = m_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init( m_Port, &GPIO_InitStructure );

	ConfigureInterrupt();

	return true;
}

bool GpioInput::ConfigureInterrupt()
{
	InterruptManager::IRQn L_IRQn;

	if(m_pISR != nullptr)
	{
		L_IRQn = MapPin2ExtLine();
		//Register Interrupt
		m_pInterruptManager->RegisterInterrupt(L_IRQn, m_pISR);

		// Configure External Gpio Line for Interrupt
		ExtLineInterruptConfig();

		//Enable_Interrupt
		//m_pInterruptManager->Enable_Interrupt(L_IRQn);
		EnableInterrupt();

		return true;
	}
	else
	{
		return false;
	}
}

bool GpioInput::DeConfigureInterrupt()
{
	//m_pInterruptManager->Disable_Interrupt(MapPin2ExtLine());
	DisableInterrupt();
	return true;
}

bool GpioInput::ExtLineInterruptConfig()
{
	EXTI_InitTypeDef EXTI_InitStruct;

	const u8  GpioPort = (m_Port==GPIOA)? 0 :
				         (m_Port==GPIOB)? 1 :
				         (m_Port==GPIOC)? 2 :
				         (m_Port==GPIOD)? 3 :
				         (m_Port==GPIOE)? 4 :
				         (m_Port==GPIOF)? 5 :
			             6;

		GPIO_EXTILineConfig( GpioPort,MapPin2PinSource() );

		EXTI_InitStruct.EXTI_Line = m_Pin;
		EXTI_InitStruct.EXTI_Mode = static_cast<EXTIMode_TypeDef>(m_eEXTIMode);
		EXTI_InitStruct.EXTI_Trigger = static_cast<EXTITrigger_TypeDef>(m_eEdge);
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStruct);

	return true;
}
/*
InterruptManager::IRQn GpioInput::MapPin2IRQn()
{
	const InterruptManager::IRQn ExtLine =
			(GpioInput::m_Pin == GPIO_Pin_0) ? InterruptManager::EXTI0_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_1) ? InterruptManager::EXTI1_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_2) ? InterruptManager::EXTI2_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_3) ? InterruptManager::EXTI3_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_4) ? InterruptManager::EXTI4_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_5) ? InterruptManager::EXTI9_5_IRQHandler :
			(GpioInput::m_Pin == GPIO_Pin_6) ? InterruptManager::EXTI9_5_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_7) ? InterruptManager::EXTI9_5_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_8) ? InterruptManager::EXTI9_5_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_9) ? InterruptManager::EXTI9_5_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_10)? InterruptManager::EXTI15_10_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_11)? InterruptManager::EXTI15_10_IRQHandler :
			(GpioInput::m_Pin == GPIO_Pin_12)? InterruptManager::EXTI15_10_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_13)? InterruptManager::EXTI15_10_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_14)? InterruptManager::EXTI15_10_IRQHandler :
            (GpioInput::m_Pin == GPIO_Pin_15)? InterruptManager::EXTI15_10_IRQHandler : InterruptManager::EXTI0_IRQHandler;

	return ExtLine;
}
*/

}



