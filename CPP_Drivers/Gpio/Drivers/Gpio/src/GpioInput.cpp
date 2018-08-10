/*
 * GpioInput.cpp
 *
 *  Created on: 08-Oct-2017
 *      Author: Amit Chaudhary
 */


#include "GpioInput.hpp"

namespace Peripherals
{



GpioInput::GpioInput(PORT_t Port, PIN_t Pin, ISR_t aISR, Intr_Event_Edge_t Intr_Event_Edge, PULL_t PULL)
{
	m_Port              = Port;
	m_Pin               = Pin;
    m_Pull              = PULL;
	m_pISR              = aISR;
    m_Intr_Event_Edge   = Intr_Event_Edge; 
}



Interrupt::IRQn GpioInput::MapPin2ExtLine()
{
	const Interrupt::IRQn ExtLine =
        (GpioInput::m_Pin == GPIO_PIN_0) ? Interrupt::EXTI0_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_1) ? Interrupt::EXTI1_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_2) ? Interrupt::EXTI2_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_3) ? Interrupt::EXTI3_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_4) ? Interrupt::EXTI4_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_5) ? Interrupt::EXTI9_5_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_6) ? Interrupt::EXTI9_5_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_7) ? Interrupt::EXTI9_5_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_8) ? Interrupt::EXTI9_5_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_9) ? Interrupt::EXTI9_5_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_10)? Interrupt::EXTI15_10_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_11)? Interrupt::EXTI15_10_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_12)? Interrupt::EXTI15_10_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_13)? Interrupt::EXTI15_10_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_14)? Interrupt::EXTI15_10_IRQHandler :
        (GpioInput::m_Pin == GPIO_PIN_15)? Interrupt::EXTI15_10_IRQHandler : Interrupt::EXTI0_IRQHandler;

	return ExtLine;
}

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
        GPIO_InitTypeDef GPIO_InitStructure;
        const Peripheral_t  APB_Peripheral =
                                           (m_Port==GPIOA)? APB2Periph_GPIOA :
                                           (m_Port==GPIOB)? APB2Periph_GPIOB :
                                           (m_Port==GPIOC)? APB2Periph_GPIOC :
                                           (m_Port==GPIOD)?APB2Periph_GPIOD :
                                           (m_Port==GPIOE)? APB2Periph_GPIOE : APB2Periph_GPIOA;

     // Enable the GPIO hardware Clocks
     //__HAL_RCC_AFIO_CLK_ENABLE();
     
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


      
    
       if(m_pISR == nullptr)
       {
           GPIO_InitStructure.Mode   = INPUT;
       }
       else
       {
          GPIO_InitStructure.Mode   = m_Intr_Event_Edge;
       }
       GPIO_InitStructure.Pin    = m_Pin;
       GPIO_InitStructure.Speed  = MEDIUM;       
       GPIO_InitStructure.Pull   = m_Pull;
       HAL_GPIO_Init( m_Port, &GPIO_InitStructure );

      
       
       if(m_pISR != nullptr)
       {
           //ExtLineInit();

           // Configure the Interrupt if ISR is supplied with the constructor
           ConfigureInterrupt();
       }
       return true;
}

Status_t GpioInput::ConfigureInterrupt()
{
    Status_t Status = false;

    Interrupt::IRQn L_IRQn;

    if(m_pISR != nullptr)
    {
        L_IRQn = MapPin2ExtLine();
        //Register Interrupt
        //Interrupt::RegisterInterrupt(m_pISR, L_IRQn); 
        Interrupt::RegisterInterrupt_Vct_Table(m_pISR, L_IRQn); 
        //Enable_Interrupt
        Interrupt::EnableInterrupt(L_IRQn);

        Status = true;
    }

    return Status;
}

Status_t GpioInput::ExtLineInit()
{
	LL_EXTI_InitTypeDef EXTI_InitStruct;
        
       EXTI_InitStruct.Line_0_31 = m_Pin;
       EXTI_InitStruct.Mode = m_Intr_Event_Edge;
       EXTI_InitStruct.Trigger = EXTI_FALLING;
       EXTI_InitStruct.LineCommand = (FunctionalState)ENABLE;
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



