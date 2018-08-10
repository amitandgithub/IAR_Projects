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
    
__no_init Interrupt::ISR Vectors_RAM[64] @ 0x20000100;

typedef uint8_t u8;


Status_t Interrupt::RegisterInterrupt(ISR pISR, IRQn eIRQn, uint8_t Priority, uint8_t SubPriority )
{
	return  true;
}


Status_t Interrupt::DisableInterrupt(IRQn eIRQn)
{
    Status_t Status = false;
    /* Disable the Selected IRQ Channels -------------------------------------*/
    NVIC->ICER[static_cast<u8>(eIRQn) >> 0x05] = (uint32_t)0x01 << (static_cast<u8>(eIRQn) & (u8)0x1F);
    Status = true;

    return  Status;
}

Status_t Interrupt::EnableInterrupt(IRQn eIRQn)
{
    Status_t Status = false;
    /* Enable the Selected IRQ Channels --------------------------------------*/
    NVIC->ISER[( static_cast<u8>(eIRQn) >> 0x05)] = (uint32_t)0x01 << (static_cast<u8>(eIRQn) & (u8)0x1F);
    Status = true;

    return  Status;

}
Status_t Interrupt::NVICConfig(IRQn eIRQn, u8 Priority, u8 SubPriority)
{
    Status_t Status = false;
    EnableInterrupt(eIRQn);
    return Status;
}


Status_t Interrupt::RegisterInterrupt_Vct_Table(ISR pISR, IRQn eIRQn,  uint8_t Priority , uint8_t SubPriority)
{
    if(pISR != nullptr)
    {
       // NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, PreemptPriority, SubPriority));
        EnableInterrupt(eIRQn);
        HAL_NVIC_SetPriority(static_cast<IRQn_Type>(eIRQn), Priority, SubPriority);
        Vectors_RAM[16 + eIRQn] = pISR;
    }
    
    return true;
}

void Interrupt::Relocate_Vector_Table()
{
    
    uint32_t *Ram_Start  = (uint32_t*)Vectors_RAM;
    uint32_t *ROM_Start = (uint32_t*)0x08000000;
    
    for(uint32_t start = 0; start<= 0x3E; start++)
    {
        Ram_Start[start] = ROM_Start[start];
    }
    
    SCB->VTOR = (uint32_t)Vectors_RAM;// | (0U & (uint32_t)0x1FFFFF80);
}

} // namespace Peripherals

extern "C"
{

void EXTI9_5_IRQHandler(void)
{

	if((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_5) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_5);

	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_6) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_6);

	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_7) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_7);

	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_8) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_8);

	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_9) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_9);

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

	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_11) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_11);

	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_12) == true)
	{
        SET_BIT(EXTI->PR,LL_EXTI_LINE_12);

	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_13) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_13);

	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_14) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_14);

	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_15) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_15);

	}
	else
	{

	}
}

void EXTI0_IRQHandler(void)
{
	LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_0);

}
void EXTI1_IRQHandler(void)
{
	LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_1);

}
void EXTI2_IRQHandler(void)
{
	LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_2);

}
void EXTI3_IRQHandler(void)
{
	LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_3);

}
void EXTI4_IRQHandler(void)
{
	LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_4);

}
void EXTI5_IRQHandler(void)
{
	LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_5);

}



}//  extern "C"


