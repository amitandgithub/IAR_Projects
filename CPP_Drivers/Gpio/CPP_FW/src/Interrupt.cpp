/*
 * Interrupt.cpp
 *
 *  Created on: 12-Oct-2017
 *      Author: Amit Chaudhary
 */

#include "Interrupt.hpp"
#include "core_cm3.h"
#include "stm32f1xx_ll_exti.h"

namespace Peripherals
{
typedef uint8_t u8;
Interrupt::ISR Interrupt::m_NMI_Handler = nullptr;
Interrupt::ISR Interrupt::m_HardFault_Handler = nullptr;
Interrupt::ISR Interrupt::m_MemManage_Handler = nullptr;
Interrupt::ISR Interrupt::m_BusFault_Handler = nullptr;
Interrupt::ISR Interrupt::m_UsageFault_Handler = nullptr;
Interrupt::ISR Interrupt::m_SVC_Handler = nullptr;
Interrupt::ISR Interrupt::m_DebugMon_Handler = nullptr;
Interrupt::ISR Interrupt::m_PendSV_Handler = nullptr;
Interrupt::ISR Interrupt::m_SysTick_Handler = nullptr;
Interrupt::ISR Interrupt::m_WWDG_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_PVD_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_TAMPER_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_RTC_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_FLASH_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_RCC_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI0_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI1_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI2_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI3_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI4_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_DMA1_Channel1_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_DMA1_Channel2_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_DMA1_Channel3_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_DMA1_Channel4_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_DMA1_Channel5_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_DMA1_Channel6_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_DMA1_Channel7_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_ADC1_2_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_USB_HP_CAN1_TX_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_USB_LP_CAN1_RX0_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_CAN1_RX1_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_CAN1_SCE_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI9_5_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_TIM1_BRK_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_TIM1_UP_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_TIM1_TRG_COM_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_TIM1_CC_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_TIM2_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_TIM3_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_TIM4_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_I2C1_EV_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_I2C1_ER_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_I2C2_EV_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_I2C2_ER_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_SPI1_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_SPI2_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_USART1_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_USART2_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_USART3_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI15_10_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_RTCAlarm_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_USBWakeUp_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI5_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI6_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI7_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI8_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI9_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI10_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI11_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI12_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI13_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI14_IRQHandler = nullptr;
Interrupt::ISR Interrupt::m_EXTI15_IRQHandler = nullptr;

//Interrupt::ISR Interrupt::VECTOR_TABLE_RAM[VECTOR_TABLE_SIZE] = {nullptr}; 

Status_t Interrupt::RegisterInterrupt(ISR pISR, IRQn eIRQn, uint8_t Priority, uint8_t SubPriority )
{
	switch(static_cast<short int>(eIRQn))
	{
    case Interrupt::NMI_Handler               :    Interrupt::m_NMI_Handler                 = pISR; break;
	case Interrupt::HardFault_Handler         :    Interrupt::m_HardFault_Handler           = pISR; break;
	case Interrupt::MemManage_Handler         :    Interrupt::m_MemManage_Handler           = pISR; break;
	case Interrupt::BusFault_Handler          :    Interrupt::m_BusFault_Handler            = pISR; break;
	case Interrupt::UsageFault_Handler        :    Interrupt::m_UsageFault_Handler          = pISR; break;
	case Interrupt::SVC_Handler               :    Interrupt::m_SVC_Handler                 = pISR; break;
	case Interrupt::DebugMon_Handler          :    Interrupt::m_DebugMon_Handler            = pISR; break;
	case Interrupt::PendSV_Handler            :    Interrupt::m_PendSV_Handler              = pISR; break;
	case Interrupt::SysTick_Handler           :    Interrupt::m_SysTick_Handler             = pISR; break;
	case Interrupt::WWDG_IRQHandler           :    Interrupt::m_WWDG_IRQHandler             = pISR; break;
	case Interrupt::PVD_IRQHandler            :    Interrupt::m_PVD_IRQHandler              = pISR; break;
	case Interrupt::TAMPER_IRQHandler         :    Interrupt::m_TAMPER_IRQHandler           = pISR; break;
	case Interrupt::RTC_IRQHandler            :    Interrupt::m_RTC_IRQHandler              = pISR; break;
	case Interrupt::FLASH_IRQHandler          :    Interrupt::m_FLASH_IRQHandler            = pISR; break;
	case Interrupt::RCC_IRQHandler            :    Interrupt::m_RCC_IRQHandler              = pISR; break;
	case Interrupt::EXTI0_IRQHandler          :    Interrupt::m_EXTI0_IRQHandler            = pISR; break;
	case Interrupt::EXTI1_IRQHandler          :    Interrupt::m_EXTI1_IRQHandler            = pISR; break;
	case Interrupt::EXTI2_IRQHandler          :    Interrupt::m_EXTI2_IRQHandler            = pISR; break;
	case Interrupt::EXTI3_IRQHandler          :    Interrupt::m_EXTI3_IRQHandler            = pISR; break;
	case Interrupt::EXTI4_IRQHandler          :    Interrupt::m_EXTI4_IRQHandler            = pISR; break;
	case Interrupt::DMA1_Channel1_IRQHandler  :    Interrupt::m_DMA1_Channel1_IRQHandler    = pISR; break;
	case Interrupt::DMA1_Channel2_IRQHandler  :    Interrupt::m_DMA1_Channel2_IRQHandler    = pISR; break;
	case Interrupt::DMA1_Channel3_IRQHandler  :    Interrupt::m_DMA1_Channel4_IRQHandler    = pISR; break;
	case Interrupt::DMA1_Channel4_IRQHandler  :    Interrupt::m_DMA1_Channel5_IRQHandler    = pISR; break;
	case Interrupt::DMA1_Channel5_IRQHandler  :    Interrupt::m_DMA1_Channel6_IRQHandler    = pISR; break;
	case Interrupt::DMA1_Channel6_IRQHandler  :    Interrupt::m_DMA1_Channel7_IRQHandler    = pISR; break;
	case Interrupt::DMA1_Channel7_IRQHandler  :    Interrupt::m_ADC1_2_IRQHandler           = pISR; break;
	case Interrupt::ADC1_2_IRQHandler         :    Interrupt::m_USB_HP_CAN1_TX_IRQHandler   = pISR; break;
	case Interrupt::USB_HP_CAN1_TX_IRQHandler :    Interrupt::m_USB_LP_CAN1_RX0_IRQHandler  = pISR; break;
	case Interrupt::USB_LP_CAN1_RX0_IRQHandler:    Interrupt::m_CAN1_RX1_IRQHandler         = pISR; break;
	case Interrupt::CAN1_RX1_IRQHandler       :    Interrupt::m_CAN1_SCE_IRQHandler         = pISR; break;
	case Interrupt::CAN1_SCE_IRQHandler       :    Interrupt::m_TIM1_BRK_IRQHandler         = pISR; break;
	case Interrupt::EXTI9_5_IRQHandler        :    Interrupt::m_EXTI9_5_IRQHandler          = pISR; break;
	case Interrupt::TIM1_BRK_IRQHandler       :    Interrupt::m_TIM1_UP_IRQHandler          = pISR; break;
	case Interrupt::TIM1_UP_IRQHandler        :    Interrupt::m_TIM1_TRG_COM_IRQHandler     = pISR; break;
	case Interrupt::TIM1_TRG_COM_IRQHandler   :    Interrupt::m_TIM1_CC_IRQHandler          = pISR; break;
	case Interrupt::TIM1_CC_IRQHandler        :    Interrupt::m_TIM2_IRQHandler             = pISR; break;
	case Interrupt::TIM2_IRQHandler           :    Interrupt::m_TIM3_IRQHandler             = pISR; break;
	case Interrupt::TIM3_IRQHandler           :    Interrupt::m_TIM4_IRQHandler             = pISR; break;
	case Interrupt::TIM4_IRQHandler           :    Interrupt::m_I2C1_ER_IRQHandler          = pISR; break;
	case Interrupt::I2C1_EV_IRQHandler        :    Interrupt::m_I2C2_EV_IRQHandler          = pISR; break;
	case Interrupt::I2C1_ER_IRQHandler        :    Interrupt::m_I2C1_ER_IRQHandler          = pISR; break;
	case Interrupt::I2C2_EV_IRQHandler        :    Interrupt::m_I2C2_EV_IRQHandler          = pISR; break;
	case Interrupt::I2C2_ER_IRQHandler        :    Interrupt::m_I2C2_ER_IRQHandler          = pISR; break;
	case Interrupt::SPI1_IRQHandler           :    Interrupt::m_SPI1_IRQHandler             = pISR; break;
	case Interrupt::SPI2_IRQHandler           :    Interrupt::m_SPI2_IRQHandler             = pISR; break;
	case Interrupt::USART1_IRQHandler         :    Interrupt::m_USART1_IRQHandler           = pISR; break;
	case Interrupt::USART2_IRQHandler         :    Interrupt::m_USART2_IRQHandler           = pISR; break;
	case Interrupt::USART3_IRQHandler         :    Interrupt::m_USART3_IRQHandler           = pISR; break;
	case Interrupt::EXTI15_10_IRQHandler      :    Interrupt::m_EXTI15_10_IRQHandler        = pISR; break;
	case Interrupt::RTCAlarm_IRQHandler       :    Interrupt::m_RTCAlarm_IRQHandler         = pISR; break;
	case Interrupt::USBWakeUp_IRQHandler      :    Interrupt::m_USBWakeUp_IRQHandler        = pISR; break;
	case Interrupt::EXTI5_IRQHandler          :    Interrupt::m_EXTI5_IRQHandler            = pISR; break;
	case Interrupt::EXTI6_IRQHandler          :    Interrupt::m_EXTI6_IRQHandler            = pISR; break;
	case Interrupt::EXTI7_IRQHandler          :    Interrupt::m_EXTI7_IRQHandler            = pISR; break;
	case Interrupt::EXTI8_IRQHandler          :    Interrupt::m_EXTI8_IRQHandler            = pISR; break;
	case Interrupt::EXTI9_IRQHandler          :    Interrupt::m_EXTI9_IRQHandler            = pISR; break;
	case Interrupt::EXTI10_IRQHandler         :    Interrupt::m_EXTI10_IRQHandler           = pISR; break;
	case Interrupt::EXTI11_IRQHandler         :    Interrupt::m_EXTI11_IRQHandler           = pISR; break;
	case Interrupt::EXTI12_IRQHandler         :    Interrupt::m_EXTI12_IRQHandler           = pISR; break;
	case Interrupt::EXTI13_IRQHandler         :    Interrupt::m_EXTI13_IRQHandler           = pISR; break;
	case Interrupt::EXTI14_IRQHandler         :    Interrupt::m_EXTI14_IRQHandler           = pISR; break;
	case Interrupt::EXTI15_IRQHandler         :    Interrupt::m_EXTI15_IRQHandler           = pISR; break;

	default : break;
	}

	if(pISR) NVICConfig(eIRQn, Priority, SubPriority);

	return true;

}


Status_t Interrupt::DisableInterrupt(IRQn eIRQn)
{
    Status_t Status = false;

	if( (eIRQn >= EXTI5_IRQHandler ) && (eIRQn <= EXTI9_IRQHandler )  )
    {
        eIRQn = Interrupt::EXTI9_5_IRQHandler;

    }
	else if( (eIRQn >= EXTI10_IRQHandler ) && (eIRQn <= EXTI15_IRQHandler )  )
    {
        eIRQn = Interrupt::EXTI15_10_IRQHandler;

    }
	else
	{
		// nothing to do
	}

    /* Disable the Selected IRQ Channels -------------------------------------*/
    NVIC->ICER[static_cast<u8>(eIRQn) >> 0x05] = (uint32_t)0x01 << (static_cast<u8>(eIRQn) & (u8)0x1F);
    Status = true;

    return  Status;
}

Status_t Interrupt::EnableInterrupt(IRQn eIRQn)
{
    Status_t Status = false;

	if( (eIRQn >= EXTI5_IRQHandler ) && (eIRQn <= EXTI9_IRQHandler )  )
    {
        eIRQn = Interrupt::EXTI9_5_IRQHandler;

    }
	else if( (eIRQn >= EXTI10_IRQHandler ) && (eIRQn <= EXTI15_IRQHandler )  )
    {
        eIRQn = Interrupt::EXTI15_10_IRQHandler;

    }
	else
	{
		// nothing to do
	}



    /* Enable the Selected IRQ Channels --------------------------------------*/
    NVIC->ISER[( static_cast<u8>(eIRQn) >> 0x05)] = (uint32_t)0x01 << (static_cast<u8>(eIRQn) & (u8)0x1F);
    Status = true;

    return  Status;

}
Status_t Interrupt::NVICConfig(IRQn eIRQn, u8 Priority, u8 SubPriority)
{
    Status_t Status = false;

	if( (eIRQn >= EXTI5_IRQHandler ) && (eIRQn <= EXTI9_IRQHandler )  )
    {
        eIRQn = Interrupt::EXTI9_5_IRQHandler;
    }

	else if( (eIRQn >= EXTI10_IRQHandler ) && (eIRQn <= EXTI15_IRQHandler )  )
    {
        eIRQn = Interrupt::EXTI15_10_IRQHandler;
    }
	else
	{
		// nothing to do
	}

    Status = true;

    return Status;
}

/*
Status_t Interrupt::RegisterInterrupt_Vct_Table(ISR pISR, IRQn eIRQn,  uint8_t Priority , uint8_t SubPriority)
{
    VECTOR_TABLE_RAM[eIRQn] = pISR;
    if(pISR) NVICConfig(eIRQn, Priority, SubPriority);
    return 1;
}
*/
} // namespace Peripherals

extern "C"
{

void EXTI9_5_IRQHandler(void)
{

	if((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_5) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_5);
		if(Peripherals::Interrupt::m_EXTI5_IRQHandler)
			Peripherals::Interrupt::m_EXTI5_IRQHandler();
	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_6) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_6);
		if(Peripherals::Interrupt::m_EXTI6_IRQHandler)
			Peripherals::Interrupt::m_EXTI6_IRQHandler();
	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_7) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_7);
		if(Peripherals::Interrupt::m_EXTI7_IRQHandler)
			Peripherals::Interrupt::m_EXTI7_IRQHandler();
	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_8) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_8);
		if(Peripherals::Interrupt::m_EXTI8_IRQHandler)
			Peripherals::Interrupt::m_EXTI8_IRQHandler();
	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_9) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_9);
		if(Peripherals::Interrupt::m_EXTI9_IRQHandler)
			Peripherals::Interrupt::m_EXTI9_IRQHandler();
	}
	else
	{

	}
}

void EXTI15_10_IRQHandler(void)
{

	if((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_10) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_10);
		if(Peripherals::Interrupt::m_EXTI10_IRQHandler)
			Peripherals::Interrupt::m_EXTI10_IRQHandler();
	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_11) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_11);
		if(Peripherals::Interrupt::m_EXTI11_IRQHandler)
			Peripherals::Interrupt::m_EXTI11_IRQHandler();
	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_12) == true)
	{
        SET_BIT(EXTI->PR,LL_EXTI_LINE_12);
		if(Peripherals::Interrupt::m_EXTI12_IRQHandler)
			Peripherals::Interrupt::m_EXTI12_IRQHandler();
	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_13) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_13);
		if(Peripherals::Interrupt::m_EXTI13_IRQHandler)
			Peripherals::Interrupt::m_EXTI13_IRQHandler();
	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_14) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_14);
		if(Peripherals::Interrupt::m_EXTI14_IRQHandler)
			Peripherals::Interrupt::m_EXTI14_IRQHandler();
	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_15) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_15);
		if(Peripherals::Interrupt::m_EXTI15_IRQHandler)
			Peripherals::Interrupt::m_EXTI15_IRQHandler();
	}
	else
	{

	}
}

void EXTI0_IRQHandler(void)
{
	LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_0);
	if(Peripherals::Interrupt::m_EXTI0_IRQHandler)
		Peripherals::Interrupt::m_EXTI0_IRQHandler();
}
void EXTI1_IRQHandler(void)
{
	LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_1);
	if(Peripherals::Interrupt::m_EXTI1_IRQHandler)
		Peripherals::Interrupt::m_EXTI1_IRQHandler();
}
void EXTI2_IRQHandler(void)
{
	LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_2);
	if(Peripherals::Interrupt::m_EXTI2_IRQHandler)
		Peripherals::Interrupt::m_EXTI2_IRQHandler();
}
void EXTI3_IRQHandler(void)
{
	LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_3);
	if(Peripherals::Interrupt::m_EXTI3_IRQHandler)
		Peripherals::Interrupt::m_EXTI3_IRQHandler();
}
void EXTI4_IRQHandler(void)
{
	LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_4);
	if(Peripherals::Interrupt::m_EXTI4_IRQHandler)
		Peripherals::Interrupt::m_EXTI4_IRQHandler();
}
void EXTI5_IRQHandler(void)
{
	LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_5);
	if(Peripherals::Interrupt::m_EXTI5_IRQHandler)
		Peripherals::Interrupt::m_EXTI5_IRQHandler();
}



}//  extern "C"


