/*
 * Interrupt.hpp
 *
 *  Created on: 12-Oct-2017
 *      Author: Amit Chaudhary
 */

#ifndef APP_INC_INTERRUPTMANAGER_HPP_
#define APP_INC_INTERRUPTMANAGER_HPP_
#include "stm32f1xx_hal.h"
#include "Peripheral.hpp"

namespace Peripherals
{


class Interrupt
{
public:
    
	typedef void(*ISR)(void);
	typedef enum {DISABLE = 0, ENABLE = !DISABLE}InterruptState;
	typedef enum
	{
        NMI_Handler = -9,
	    HardFault_Handler,
	    MemManage_Handler,
	    BusFault_Handler,
	    UsageFault_Handler,
	    SVC_Handler,
	    DebugMon_Handler,
	    PendSV_Handler,
	    SysTick_Handler,
            WWDG_IRQHandler,
            PVD_IRQHandler,
            TAMPER_IRQHandler,
            RTC_IRQHandler,
            FLASH_IRQHandler,
            RCC_IRQHandler,
            EXTI0_IRQHandler,
            EXTI1_IRQHandler,
            EXTI2_IRQHandler,
            EXTI3_IRQHandler,
            EXTI4_IRQHandler,
            DMA1_Channel1_IRQHandler,
            DMA1_Channel2_IRQHandler,
            DMA1_Channel3_IRQHandler,
            DMA1_Channel4_IRQHandler,
            DMA1_Channel5_IRQHandler,
            DMA1_Channel6_IRQHandler,
            DMA1_Channel7_IRQHandler,
            ADC1_2_IRQHandler,
            USB_HP_CAN1_TX_IRQHandler,
            USB_LP_CAN1_RX0_IRQHandler,
            CAN1_RX1_IRQHandler,
            CAN1_SCE_IRQHandler,
            EXTI9_5_IRQHandler,
            TIM1_BRK_IRQHandler,
            TIM1_UP_IRQHandler,
            TIM1_TRG_COM_IRQHandler,
            TIM1_CC_IRQHandler,
            TIM2_IRQHandler,
            TIM3_IRQHandler,
            TIM4_IRQHandler,
            I2C1_EV_IRQHandler,
            I2C1_ER_IRQHandler,
            I2C2_EV_IRQHandler,
            I2C2_ER_IRQHandler,
            SPI1_IRQHandler,
            SPI2_IRQHandler,
            USART1_IRQHandler,
            USART2_IRQHandler,
            USART3_IRQHandler,
            EXTI15_10_IRQHandler,
            RTCAlarm_IRQHandler,
            USBWakeUp_IRQHandler,
            EXTI5_IRQHandler,
            EXTI6_IRQHandler,
            EXTI7_IRQHandler,
            EXTI8_IRQHandler,
            EXTI9_IRQHandler,
            EXTI10_IRQHandler,
            EXTI11_IRQHandler,
            EXTI12_IRQHandler,
            EXTI13_IRQHandler,
            EXTI14_IRQHandler,
            EXTI15_IRQHandler
	}IRQn;

	static ISR m_NMI_Handler;
	static ISR m_HardFault_Handler;
	static ISR m_MemManage_Handler;
	static ISR m_BusFault_Handler;
	static ISR m_UsageFault_Handler;
	static ISR m_SVC_Handler;
	static ISR m_DebugMon_Handler;
	static ISR m_PendSV_Handler;
	static ISR m_SysTick_Handler;
	static ISR m_WWDG_IRQHandler;
	static ISR m_PVD_IRQHandler;
	static ISR m_TAMPER_IRQHandler;
	static ISR m_RTC_IRQHandler;
	static ISR m_FLASH_IRQHandler;
	static ISR m_RCC_IRQHandler;
	static ISR m_EXTI0_IRQHandler;
	static ISR m_EXTI1_IRQHandler;
	static ISR m_EXTI2_IRQHandler;
	static ISR m_EXTI3_IRQHandler;
	static ISR m_EXTI4_IRQHandler;
	static ISR m_EXTI5_IRQHandler;
	static ISR m_EXTI6_IRQHandler;
	static ISR m_EXTI7_IRQHandler;
	static ISR m_EXTI8_IRQHandler;
	static ISR m_EXTI9_IRQHandler;
	static ISR m_EXTI10_IRQHandler;
	static ISR m_EXTI11_IRQHandler;
	static ISR m_EXTI12_IRQHandler;
	static ISR m_EXTI13_IRQHandler;
	static ISR m_EXTI14_IRQHandler;
	static ISR m_EXTI15_IRQHandler;
	static ISR m_DMA1_Channel1_IRQHandler;
	static ISR m_DMA1_Channel2_IRQHandler;
	static ISR m_DMA1_Channel3_IRQHandler;
	static ISR m_DMA1_Channel4_IRQHandler;
	static ISR m_DMA1_Channel5_IRQHandler;
	static ISR m_DMA1_Channel6_IRQHandler;
	static ISR m_DMA1_Channel7_IRQHandler;
	static ISR m_ADC1_2_IRQHandler;
	static ISR m_USB_HP_CAN1_TX_IRQHandler;
	static ISR m_USB_LP_CAN1_RX0_IRQHandler;
	static ISR m_CAN1_RX1_IRQHandler;
	static ISR m_CAN1_SCE_IRQHandler;
	static ISR m_EXTI9_5_IRQHandler;
	static ISR m_TIM1_BRK_IRQHandler;
	static ISR m_TIM1_UP_IRQHandler;
	static ISR m_TIM1_TRG_COM_IRQHandler;
	static ISR m_TIM1_CC_IRQHandler;
	static ISR m_TIM2_IRQHandler;
	static ISR m_TIM3_IRQHandler;
	static ISR m_TIM4_IRQHandler;
	static ISR m_I2C1_EV_IRQHandler;
	static ISR m_I2C1_ER_IRQHandler;
	static ISR m_I2C2_EV_IRQHandler;
	static ISR m_I2C2_ER_IRQHandler;
	static ISR m_SPI1_IRQHandler;
	static ISR m_SPI2_IRQHandler;
	static ISR m_USART1_IRQHandler;
	static ISR m_USART2_IRQHandler;
	static ISR m_USART3_IRQHandler;
	static ISR m_EXTI15_10_IRQHandler;
	static ISR m_RTCAlarm_IRQHandler;
	static ISR m_USBWakeUp_IRQHandler;
    
    //static const uint32_t VECTOR_TABLE_SIZE = EXTI15_IRQHandler+9;
   // static ISR VECTOR_TABLE_RAM[VECTOR_TABLE_SIZE]; 
    
    static void Relocate_Vector_Table();
    Interrupt(){};
    
    ~Interrupt(){};
    
	static Status_t RegisterInterrupt(ISR pISR, IRQn eIRQn,  uint8_t Priority = 15, uint8_t SubPriority = 0 );
    
    static Status_t RegisterInterrupt_Vct_Table(ISR pISR, IRQn eIRQn,  uint8_t Priority = 15, uint8_t SubPriority = 0 );
    
	static Status_t EnableInterrupt(IRQn eIRQn);//{NVIC_EnableIRQ( eIRQn);}
    
	static Status_t DisableInterrupt(IRQn eIRQn);
    
	static Status_t NVICConfig(IRQn eIRQn, uint8_t Priority, uint8_t SubPriority);
    
    static Status_t GetInterruptStatus(IRQn eIRQn);
    
    static Status_t SetInterruptPriority(IRQn eIRQn,uint8_t Priority, uint8_t SubPriority);
    
    static Status_t GetInterruptPriority(IRQn eIRQn,uint8_t* pPriority, uint8_t* pSubPriority);
    
     static  ISR Vectors_RAM[64];

};






























}
#endif /* APP_INC_INTERRUPTMANAGER_HPP_ */
