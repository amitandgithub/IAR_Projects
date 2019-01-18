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
#include "stm32f1xx.h"

namespace HAL
{
  
class GpioOutput : public Gpio
{
public:
    
    typedef struct
    {
        Port_t  _GPIOx;
        uint8_t _pin;  
        Mode_t _mode;
    }Params_t;
    
constexpr GpioOutput(Pin_t  Pin, GpioMode_t mode = GPIO_MODE_OPEN_DRAIN, GpioSpeed_t speed = GPIO_SPEED_HIGH);

~GpioOutput(){};

  Status_t HwInit(void *pInitStruct = nullptr);
  
  HAL_Status_t HwDeinit();
  
  void High();
  
  void Low();
  
  void Toggle();
  
private:
    GpioMode_t _mode;
    GpioSpeed_t _speed;  
};




constexpr GpioOutput::GpioOutput(Pin_t  Pin, GpioMode_t mode, GpioSpeed_t speed) : Gpio(Pin),_mode(mode),_speed(speed)
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
    //LL_GPIO_TogglePin(_GPIOx, LL_GPIO_PIN_13);
}


}

#endif //GpioOutput_h
