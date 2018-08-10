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
        NMI_Handler = -14,
	    HardFault_Handler = -13,
	    MemManage_Handler = -12,
	    BusFault_Handler = -11,
	    UsageFault_Handler = -10,
        _Rsvd1 = -9,                         
		_Rsvd2 = -8,                        
		_Rsvd3 = -7,                       
		_Rsvd4 = -6, 
	    SVC_Handler = -5,
	    DebugMon_Handler = -4,
        _Rsvd5 = -3,
	    PendSV_Handler = -2,
	    SysTick_Handler = -1,
            WWDG_IRQHandler = 0,
            PVD_IRQHandler = 1,
            TAMPER_IRQHandler = 2,
            RTC_IRQHandler = 3,
            FLASH_IRQHandler = 4,
            RCC_IRQHandler = 5,
            EXTI0_IRQHandler = 6,
            EXTI1_IRQHandler = 7,
            EXTI2_IRQHandler = 8,
            EXTI3_IRQHandler = 9,
            EXTI4_IRQHandler = 10,
            DMA1_Channel1_IRQHandler = 11,
            DMA1_Channel2_IRQHandler = 12,
            DMA1_Channel3_IRQHandler = 13,
            DMA1_Channel4_IRQHandler = 14,
            DMA1_Channel5_IRQHandler = 15,
            DMA1_Channel6_IRQHandler = 16,
            DMA1_Channel7_IRQHandler = 17,
            ADC1_2_IRQHandler = 18,
            USB_HP_CAN1_TX_IRQHandler = 19,
            USB_LP_CAN1_RX0_IRQHandler = 20,
            CAN1_RX1_IRQHandler = 21,
            CAN1_SCE_IRQHandler = 22,
            EXTI9_5_IRQHandler = 23,
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
    
     //static  ISR Vectors_RAM[64];

};






























}
#endif /* APP_INC_INTERRUPTMANAGER_HPP_ */
