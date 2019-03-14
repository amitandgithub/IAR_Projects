/*
 * GpioInput.cpp
 *
 *  Created on: 08-Oct-2017
 *      Author: Amit Chaudhary
 */


#include "GpioInput.h"

namespace HAL
{

Interrupt::ISR GpioInput::_GPIO_ISRs[16];

GpioInput::CallbackFunction         GpioInput::m_callback;

GpioInput::GpioInput(Pin_t  Pin, GpioInput_Params_t Params,Intr_Event_Edge_t Edge, ISR_t aISR) : Gpio(Pin), _params(Params), _Intr_Event_Edge(Edge), _pISR(aISR)
{

}

GpioInput::GpioInput(Pin_t  Pin, GpioInput_Params_t Params,Intr_Event_Edge_t Edge, CallbackFunction cb) : Gpio(Pin), _params(Params), _Intr_Event_Edge(Edge)
{
    m_callback = cb;
}
//0x88  Code, but when compiled with High Optimization 
//constexpr Interrupt::IRQn GpioInput::MapPin2ExtLine(uint32_t  Pin)
//{
//    
//	const Interrupt::IRQn ExtLine =
//        (Pin == 0) ? Interrupt::EXTI0_IRQHandler :
//        (Pin == 1) ? Interrupt::EXTI1_IRQHandler :
//        (Pin == 2) ? Interrupt::EXTI2_IRQHandler :
//        (Pin == 3) ? Interrupt::EXTI3_IRQHandler :
//        (Pin == 4) ? Interrupt::EXTI4_IRQHandler :
//        (Pin == 5) ? Interrupt::EXTI9_5_IRQHandler :
//        (Pin == 6) ? Interrupt::EXTI9_5_IRQHandler :
//        (Pin == 7) ? Interrupt::EXTI9_5_IRQHandler :
//        (Pin == 8) ? Interrupt::EXTI9_5_IRQHandler :
//        (Pin == 9) ? Interrupt::EXTI9_5_IRQHandler :
//        (Pin == 10)? Interrupt::EXTI15_10_IRQHandler :
//        (Pin == 11)? Interrupt::EXTI15_10_IRQHandler :
//        (Pin == 12)? Interrupt::EXTI15_10_IRQHandler :
//        (Pin == 13)? Interrupt::EXTI15_10_IRQHandler :
//        (Pin == 14)? Interrupt::EXTI15_10_IRQHandler :
//        (Pin == 15)? Interrupt::EXTI15_10_IRQHandler : Interrupt::EXTI0_IRQHandler;
//
//	return ExtLine;
//}


// 0x20  Code
constexpr Interrupt::IRQn GpioInput::MapPin2ExtLine(uint32_t  Pin)
{
    const Interrupt::IRQn IRQns[16] = 
    {   Interrupt::EXTI0_IRQHandler,
        Interrupt::EXTI1_IRQHandler,
        Interrupt::EXTI2_IRQHandler,
        Interrupt::EXTI3_IRQHandler,
        Interrupt::EXTI4_IRQHandler,
        Interrupt::EXTI9_5_IRQHandler,
        Interrupt::EXTI9_5_IRQHandler,
        Interrupt::EXTI9_5_IRQHandler,
        Interrupt::EXTI9_5_IRQHandler,
        Interrupt::EXTI9_5_IRQHandler,
        Interrupt::EXTI15_10_IRQHandler,
        Interrupt::EXTI15_10_IRQHandler,
        Interrupt::EXTI15_10_IRQHandler,
        Interrupt::EXTI15_10_IRQHandler,
        Interrupt::EXTI15_10_IRQHandler,
        Interrupt::EXTI15_10_IRQHandler
    };

	return IRQns[Pin % PINS_PER_PORT];
}

// 0x46  Code, but when compiled with High Optimization 
// its eliminated by compiler completly 
//constexpr Interrupt::IRQn GpioInput::MapPin2ExtLine(uint32_t  Pin)
//{
//    switch(Pin)
//    {
//    case 0: return Interrupt::EXTI0_IRQHandler;
//    case 1: return Interrupt::EXTI1_IRQHandler;
//    case 2: return Interrupt::EXTI2_IRQHandler;
//    case 3: return Interrupt::EXTI3_IRQHandler;
//    case 4: return Interrupt::EXTI4_IRQHandler;
//    case 5:
//    case 6: 
//    case 7: 
//    case 8: 
//    case 9: return Interrupt::EXTI9_5_IRQHandler;
//    case 10: 
//    case 11: 
//    case 12: 
//    case 13: 
//    case 14: 
//    case 15: return Interrupt::EXTI15_10_IRQHandler;
//    default: break;
//    }
//    return Interrupt::EXTI0_IRQHandler;
//}


GpioInput::GpioStatus_t GpioInput::HwInit(void *pInitStruct)
{
    ErrorStatus status;
    GpioStatus_t Status;
    LL_GPIO_InitTypeDef GPIO_InitTypeDef; 
    
    if(pInitStruct == nullptr)
    {
        pInitStruct = &GPIO_InitTypeDef;
        Status = get_GPIO_InitTypeDef((LL_GPIO_InitTypeDef*)pInitStruct);       
    }
  
    ClockEnable();    
    
    if((_pISR != nullptr) || (m_callback))
    {
        ExtLineInit();
        
        // Configure the Interrupt if ISR is supplied with the constructor
        ConfigureInterrupt(POSITION_VAL(_pin)); // if _pin = 0x80, then POSITION_VAL(_pin) is 7
    }
    status = LL_GPIO_Init(_GPIOx, (LL_GPIO_InitTypeDef*)pInitStruct);
    
    return (status == SUCCESS) && (Status == GPIO_SUCCESS) ? GPIO_SUCCESS: GPIO_ERROR;
     
}

GpioInput::GpioStatus_t GpioInput::get_GPIO_InitTypeDef(LL_GPIO_InitTypeDef* pLL_GPIO_Init)
{
    if(pLL_GPIO_Init == nullptr)
        return GPIO_ERROR_INVALID_PARAMS; 
    
    
    pLL_GPIO_Init->Pin              = get_LL_pin(_pin); // Init Done 
    pLL_GPIO_Init->Speed            = LL_GPIO_MODE_OUTPUT_2MHz;
    pLL_GPIO_Init->Mode             = LL_GPIO_MODE_INPUT; 
    
    switch(_params)
    {
    case INPUT_FLOATING:    pLL_GPIO_Init->Pull = 0;
                            break;
    case INPUT_PULL_UP:     pLL_GPIO_Init->Pull = LL_GPIO_PULL_UP;
                            break;
    case INPUT_PULL_DOWN:   pLL_GPIO_Init->Pull = LL_GPIO_PULL_DOWN;
                            break;                                  
    case ANALOG:            pLL_GPIO_Init->Mode =  LL_GPIO_MODE_ANALOG;
                            break;
    default:                return GPIO_ERROR;  
                            break;
    }
    
    return GPIO_SUCCESS;     
                     
}



GpioInput::GpioStatus_t GpioInput::ConfigureInterrupt(const uint32_t Pin)
{
    Interrupt::IRQn L_IRQn;
    //constexpr uint32_t Pin = Pin;//POSITION_VAL(_pin);// MapPin2PinSource();

     if((_pISR != nullptr) || (m_callback))
    {
        L_IRQn = MapPin2ExtLine(Pin);
        
        if( L_IRQn == Interrupt::EXTI9_5_IRQHandler)
        {
            if((Pin > 4) && (Pin < 10) )
            {
                _GPIO_ISRs[Pin] = _pISR;
                Interrupt::RegisterInterrupt_Vct_Table(GpioInput::EXTI5_9_IRQHandler, L_IRQn); 
            }
        }
        else if( L_IRQn == Interrupt::EXTI15_10_IRQHandler)
        {
             if((Pin > 9) && (Pin < 16) )
             {
                _GPIO_ISRs[Pin] = _pISR;
                Interrupt::RegisterInterrupt_Vct_Table(GpioInput::EXTI15_10_IRQHandler, L_IRQn); 
             }
        }
        else 
        {
             Interrupt::ISR L_ISR = nullptr;
             _GPIO_ISRs[Pin%16] = _pISR;
             
             switch(Pin)
             {
             case 0 : L_ISR = EXTI0_IRQHandler; break;
             case 1 : L_ISR = EXTI1_IRQHandler; break;
             case 2 : L_ISR = EXTI2_IRQHandler; break;
             case 3 : L_ISR = EXTI3_IRQHandler; break;
             case 4 : L_ISR = EXTI4_IRQHandler; break;
             default: ;
             }
             
             Interrupt::RegisterInterrupt_Vct_Table(L_ISR, L_IRQn); 
        }
        //Enable_Interrupt
        Interrupt::EnableInterrupt(L_IRQn);

        return GPIO_SUCCESS;
    }

    return GPIO_ERROR;
}

GpioInput::GpioStatus_t GpioInput::ExtLineInit()
{
	LL_EXTI_InitTypeDef EXTI_InitStruct;
    
    if((_Intr_Event_Edge == IT_ON_RISING) || (_Intr_Event_Edge == EVT_ON_RISING))
    {
        EXTI_InitStruct.Trigger = EXTI_RISING;
    }
    else if((_Intr_Event_Edge == IT_ON_FALLING) || (_Intr_Event_Edge == EVT_ON_FALLING))
    {
         EXTI_InitStruct.Trigger = EXTI_FALLING;
    }
    else
    {
        EXTI_InitStruct.Trigger = EXTI_RISING_FALLING;
    }    
    
    EXTI_InitStruct.Line_0_31 = _pin;
    EXTI_InitStruct.Mode = _Intr_Event_Edge;    
    EXTI_InitStruct.LineCommand = (FunctionalState)ENABLE;
    LL_EXTI_Init(&EXTI_InitStruct);
    return GPIO_SUCCESS;
}
void GpioInput::EXTI5_9_IRQHandler()
{
	if((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_5) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_5);
        _GPIO_ISRs[5]();
	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_6) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_6);
        _GPIO_ISRs[6]();
	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_7) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_7);
        _GPIO_ISRs[7]();

	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_8) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_8);
        //_GPIO_ISRs[8]();
         if (m_callback)
             m_callback(0);

	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_9) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_9);
        _GPIO_ISRs[9]();
        
       
	}
}

void GpioInput::EXTI15_10_IRQHandler()
{

	if((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_10) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_10);
        _GPIO_ISRs[10]();

	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_11) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_11);
        _GPIO_ISRs[11]();

	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_12) == true)
	{
        SET_BIT(EXTI->PR,LL_EXTI_LINE_12);
        _GPIO_ISRs[12]();

	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_13) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_13);
        _GPIO_ISRs[13]();

	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_14) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_14);
        _GPIO_ISRs[14]();

	}
	else if ((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_15) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_15);
        if (_GPIO_ISRs[15])
        _GPIO_ISRs[15]();

	}
}

void GpioInput::EXTI0_IRQHandler()
{
	if((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_0) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_0);
        _GPIO_ISRs[0]();
	}

}
void GpioInput::EXTI1_IRQHandler()
{
	if((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_1) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_1);
        _GPIO_ISRs[1]();
	}

}
void GpioInput::EXTI2_IRQHandler()
{
	if((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_2) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_2);
        _GPIO_ISRs[2]();
	}

}
void GpioInput::EXTI3_IRQHandler()
{
	if((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_3) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_3);
        _GPIO_ISRs[3]();

	}

}
void GpioInput::EXTI4_IRQHandler()
{
	if((bool)LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_4) == true)
	{
		SET_BIT(EXTI->PR,LL_EXTI_LINE_4);
        _GPIO_ISRs[4]();

	}

}

}



