/*
 * GpioInput.cpp
 *
 *  Created on: 08-Oct-2017
 *      Author: Amit Chaudhary
 */


#include "GpioInput.hpp"

namespace Peripherals
{



GpioInput::GpioInput(PORT_t Port, PIN_t Pin, PULL_t PULL , ISR_t aISR , EXTIMode_t EXTIMode, EXTIIntrOnEdge_t EXTIIntrOnEdge)
{
	m_Port          = Port;
	m_Pin           = Pin;
    m_Pull          = PULL;
	m_pISR          = aISR;
    m_ExtIntrMode   = EXTIMode;
    m_eEdge         = EXTIIntrOnEdge;    
}


/*
Bsp::PeripheralBase::IRQn GpioInput::MapPin2ExtLine()
{
	const Bsp::PeripheralBase::IRQn ExtLine =
        (GpioInput::m_Pin == GPIO_PIN_0) ? Bsp::PeripheralBase::EXTI0_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_1) ? Bsp::PeripheralBase::EXTI1_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_2) ? Bsp::PeripheralBase::EXTI2_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_3) ? Bsp::PeripheralBase::EXTI3_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_4) ? Bsp::PeripheralBase::EXTI4_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_5) ? Bsp::PeripheralBase::EXTI5_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_6) ? Bsp::PeripheralBase::EXTI6_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_7) ? Bsp::PeripheralBase::EXTI7_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_8) ? Bsp::PeripheralBase::EXTI8_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_9) ? Bsp::PeripheralBase::EXTI9_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_10)? Bsp::PeripheralBase::EXTI10_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_11)? Bsp::PeripheralBase::EXTI11_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_12)? Bsp::PeripheralBase::EXTI12_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_13)? Bsp::PeripheralBase::EXTI13_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_14)? Bsp::PeripheralBase::EXTI14_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_15)? Bsp::PeripheralBase::EXTI15_IRQHandler : Bsp::PeripheralBase::EXTI0_IRQHandler;

	return ExtLine;
}
*/
uint8_t GpioInput::MapPin2PinSource()
{
	const uint8_t PinSource =
         (GpioInput::m_Pin == GPIO_PIN_0) ? 0  :
         (GpioInput::m_Pin == GPIO_PIN_1) ? 1  :
         (GpioInput::m_Pin == GPIO_PIN_2) ? 2  :
         (GpioInput::m_Pin == GPIO_PIN_3) ? 3  :
         (GpioInput::m_Pin == GPIO_PIN_4) ? 4  :
         (GpioInput::m_Pin == GPIO_PIN_5) ? 5  :
         (GpioInput::m_Pin == GPIO_PIN_6) ? 6  :
         (GpioInput::m_Pin == GPIO_PIN_7) ? 7  :
         (GpioInput::m_Pin == GPIO_PIN_8) ? 8  :
         (GpioInput::m_Pin == GPIO_PIN_9) ? 9  :
         (GpioInput::m_Pin == GPIO_PIN_10)? 10 :
         (GpioInput::m_Pin == GPIO_PIN_11)? 11 :
         (GpioInput::m_Pin == GPIO_PIN_12)? 12 :
         (GpioInput::m_Pin == GPIO_PIN_13)? 13 :
         (GpioInput::m_Pin == GPIO_PIN_14)? 14 :
         (GpioInput::m_Pin == GPIO_PIN_15)? 15 : 0;

	return PinSource;
}

Status_t GpioInput::HwInit()
{
        uint32_t Gpio_Mode = 0;
        GPIO_InitTypeDef GPIO_InitStructure;
        const Peripheral_t  APB_Peripheral =
                                           (m_Port==GPIOA)? APB2Periph_GPIOA :
                                           (m_Port==GPIOB)? APB2Periph_GPIOB :
                                           (m_Port==GPIOC)? APB2Periph_GPIOC :
                                           (m_Port==GPIOD)?APB2Periph_GPIOD :
                                           (m_Port==GPIOE)? APB2Periph_GPIOE : APB2Periph_GPIOA;

     // Enable the GPIO hardware Clocks
     __HAL_RCC_AFIO_CLK_ENABLE();
     
     if(APB_Peripheral == APB2Periph_GPIOA )
         __HAL_RCC_GPIOA_CLK_ENABLE();
     else if(APB_Peripheral == APB2Periph_GPIOB )
         __HAL_RCC_GPIOB_CLK_ENABLE();
     else if(APB_Peripheral == APB2Periph_GPIOC )
         __HAL_RCC_GPIOC_CLK_ENABLE();
     else if(APB_Peripheral == APB2Periph_GPIOD )
         __HAL_RCC_GPIOD_CLK_ENABLE();
     else if(APB_Peripheral == APB2Periph_GPIOE )
         __HAL_RCC_GPIOE_CLK_ENABLE();
     else {;}       // Error    


       
       if(m_ExtIntrMode == EXT_MODE_INTERRUPT)
       {
           Gpio_Mode = GPIO | GPIO_IT;
       }
       else if(m_ExtIntrMode == EXT_MODE_EVENT) 
       {
            Gpio_Mode = EXT_I | GPIO_EVT;
       }
       else if(m_ExtIntrMode == EXT_MODE_INTERRUPT_EVENT) 
       {
           Gpio_Mode = GPIO | GPIO_IT | EXT_I | GPIO_EVT;
       }
       else
       {
           // Error
       }
       GPIO_InitStructure.Pin    = m_Pin;
       GPIO_InitStructure.Speed  = HIGH;
       GPIO_InitStructure.Mode   = Gpio_Mode;
       GPIO_InitStructure.Pull   = m_Pull;
       HAL_GPIO_Init( m_Port, &GPIO_InitStructure );

      
       
       if(m_pISR != nullptr)
       {
            if(m_ExtIntrMode != EXT_MODE_NONE)
            {
                ExtLineInit();
            }
            
           // Configure the Interrupt if ISR is supplied with the constructor
           //ConfigureInterrupt();
       }
       return true;
}
/*
Status_t GpioInput::ConfigureInterrupt()
{
    Status_t Status = false;

    Bsp::PeripheralBase::IRQn L_IRQn;

    if(m_pISR != nullptr)
    {
        L_IRQn = MapPin2ExtLine();
        //Register Interrupt
        RegisterInterrupt(m_pISR, L_IRQn, 0);

        // Configure External Gpio Line for Interrupt
        ExtLineInterruptConfig();

        //Enable_Interrupt
        HwEnableInterrupt(L_IRQn);

        Status = true;
    }

    return Status;
}
*/
Status_t GpioInput::ExtLineInit()
{
	LL_EXTI_InitTypeDef EXTI_InitStruct;
        
       EXTI_InitStruct.Line_0_31 = m_Pin;
       EXTI_InitStruct.Mode = m_ExtIntrMode;
       EXTI_InitStruct.Trigger = m_eEdge;
       EXTI_InitStruct.LineCommand = ENABLE;
       LL_EXTI_Init(&EXTI_InitStruct);

       return true;
}
/*
InterruptManager::IRQn GpioInput::MapPin2IRQn()
{
	const InterruptManager::IRQn ExtLine =
			(GpioInput::m_Pin == GPIO_PIN_0) ? InterruptManager::EXTI0_IRQHandler :
            (GpioInput::m_Pin == GPIO_PIN_1) ? InterruptManager::EXTI1_IRQHandler :
            (GpioInput::m_Pin == GPIO_PIN_2) ? InterruptManager::EXTI2_IRQHandler :
            (GpioInput::m_Pin == GPIO_PIN_3) ? InterruptManager::EXTI3_IRQHandler :
            (GpioInput::m_Pin == GPIO_PIN_4) ? InterruptManager::EXTI4_IRQHandler :
            (GpioInput::m_Pin == GPIO_PIN_5) ? InterruptManager::EXTI9_5_IRQHandler :
			(GpioInput::m_Pin == GPIO_PIN_6) ? InterruptManager::EXTI9_5_IRQHandler :
            (GpioInput::m_Pin == GPIO_PIN_7) ? InterruptManager::EXTI9_5_IRQHandler :
            (GpioInput::m_Pin == GPIO_PIN_8) ? InterruptManager::EXTI9_5_IRQHandler :
            (GpioInput::m_Pin == GPIO_PIN_9) ? InterruptManager::EXTI9_5_IRQHandler :
            (GpioInput::m_Pin == GPIO_PIN_10)? InterruptManager::EXTI15_10_IRQHandler :
            (GpioInput::m_Pin == GPIO_PIN_11)? InterruptManager::EXTI15_10_IRQHandler :
			(GpioInput::m_Pin == GPIO_PIN_12)? InterruptManager::EXTI15_10_IRQHandler :
            (GpioInput::m_Pin == GPIO_PIN_13)? InterruptManager::EXTI15_10_IRQHandler :
            (GpioInput::m_Pin == GPIO_PIN_14)? InterruptManager::EXTI15_10_IRQHandler :
            (GpioInput::m_Pin == GPIO_PIN_15)? InterruptManager::EXTI15_10_IRQHandler : InterruptManager::EXTI0_IRQHandler;

	return ExtLine;
}
*/

}



