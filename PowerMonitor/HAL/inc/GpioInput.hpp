/*
 * GpioInput.hpp
 *
 *  Created on: 08-Oct-2017
 *      Author: Amit Chaudhary
 */

#ifndef APP_INC_GPIOINPUT_HPP_
#define APP_INC_GPIOINPUT_HPP_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "Gpio.hpp"
#include "InterruptManager.hpp"
#include "ClockManager.hpp"

namespace Bsp
{

class GpioInput: public Gpio
{
public:

	typedef enum
	{
	    EXTI_Trigger_Rising = 0x08,
	    EXTI_Trigger_Falling = 0x0C,
	    EXTI_Trigger_Rising_Falling = 0x10
	}IntOnWhichEdge;

	typedef enum
	{
	  EXTI_Mode_Interrupt = 0x00,
	  EXTI_Mode_Event = 0x04
	}EXTIMode;

	GpioInput(PORT Port, u16 Pin);

	GpioInput(PORT Port, u16 Pin, InterruptManager::ISR aISR,IntOnWhichEdge eIntOnWhichEdge, EXTIMode eEXTIMode );

	GpioInput(PORT Port, u16 Pin, InterruptManager::ISR aISR,IntOnWhichEdge eIntOnWhichEdge );

	virtual ~GpioInput(){};

	virtual bool HwInit();

	inline u8 IsInputHigh() const { return GPIO_ReadInputDataBit(m_Port,m_Pin); }

	inline bool ReadInput() const { return GPIO_ReadInputDataBit(m_Port,m_Pin); }

	bool ConfigureInterrupt();

	bool DeConfigureInterrupt();

	void EnableInterrupt(){m_pInterruptManager->Enable_Interrupt(MapPin2ExtLine());}

	void DisableInterrupt(){m_pInterruptManager->Disable_Interrupt(MapPin2ExtLine());}

private:

	InterruptManager::IRQn MapPin2ExtLine();

	u8 MapPin2PinSource();

	bool ExtLineInterruptConfig();

private:

	PORT  m_Port;
	u16   m_Pin;

	IntOnWhichEdge        m_eEdge;
	EXTIMode              m_eEXTIMode;
	PortManager*          m_pPortManager;
	ClockManager*         m_pClockManager;
	InterruptManager*     m_pInterruptManager;
	InterruptManager::ISR m_pISR;
};

}// namespace Bsp




#endif /* APP_INC_GPIOINPUT_HPP_ */
