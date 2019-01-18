/******************
** CLASS: GpioOutput
**
** DESCRIPTION:
**  GpioOutput class functionality
**
** CREATED: 1/17/2019, by Amit Chaudhary
**
** FILE: GpioOutput.h
**
******************/
#ifndef GpioOutput_h
#define GpioOutput_h

#include "Gpio.h"


namespace HAL
{
  
class GpioOutput : public Gpio
{
public:
    
    
    //constexpr GpioOutput(Pin_t  Pin, GpioMode_t mode = GPIO_MODE_OPEN_DRAIN, GpioSpeed_t speed = GPIO_SPEED_HIGH);
    
    constexpr GpioOutput(Pin_t  Pin, GpioOutput_Params_t Params = Gpio::PUSH_PULL);
    
    ~GpioOutput(){};
    
    Status_t HwInit(void *pInitStruct = nullptr);
    
    HAL_Status_t HwDeinit();
    
    void High();
    
    void Low();
    
    void Toggle();
    
private:
    GpioOutput_Params_t _params;
};




//constexpr GpioOutput::GpioOutput(Pin_t  Pin, GpioMode_t mode, GpioSpeed_t speed) : Gpio(Pin),_mode(mode),_speed(speed)
//{
//
//}

constexpr GpioOutput::GpioOutput(Pin_t  Pin, GpioOutput_Params_t Params) : Gpio(Pin),_params(Gpio::PUSH_PULL)
{

}

inline void GpioOutput::High()
{
    _GPIOx->BSRR |= (1U<<_pin);
}

inline void GpioOutput::Low()
{
    _GPIOx->BRR &= ~(1U<<_pin);
}

inline void GpioOutput::Toggle()
{
    _GPIOx->ODR ^= (1U<<_pin);
}


}

#endif //GpioOutput_h
