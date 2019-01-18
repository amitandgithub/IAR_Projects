/******************
** FILE: GpioOutput.cpp
**
** DESCRIPTION:
**  GpioOutput class Implementation
**
** CREATED: 1/17/2019, by Amit Chaudhary
******************/

#include "GpioOutput.h"

namespace HAL
{
    

GpioOutput::Status_t GpioOutput::HwInit(void *pInitStruct)
{
    ErrorStatus status;
    
    LL_GPIO_InitTypeDef GPIO_InitTypeDef; 
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitTypeDef.Pin = get_LL_pin();
    GPIO_InitTypeDef.Pull = 0;
    
    if( _mode == GPIO_MODE_OPEN_DRAIN )
    {
         GPIO_InitTypeDef.Mode = LL_GPIO_MODE_OUTPUT;
         GPIO_InitTypeDef.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    }
    else if(_mode == GPIO_MODE_PUSH_PULL)
    {
        GPIO_InitTypeDef.Mode = LL_GPIO_MODE_OUTPUT;
        GPIO_InitTypeDef.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    }
    
    if(_speed == GPIO_SPEED_LOW)
    {
        GPIO_InitTypeDef.Speed = LL_GPIO_SPEED_FREQ_LOW;
    }
    else if(_speed == GPIO_SPEED_MEDIUM)
     {
         GPIO_InitTypeDef.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
    }
    else
    {
        GPIO_InitTypeDef.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    }
    
  GPIO_InitStruct.Pin        = LL_GPIO_PIN_13;
  GPIO_InitStruct.Mode       = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull       = 0;
  
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
    
    status = LL_GPIO_Init(_GPIOx, &GPIO_InitStruct);
    
    return status == SUCCESS ? HAL_STATUS_SUCCESS: HAL_STATUS_ERROR;
}
    
    
    
}