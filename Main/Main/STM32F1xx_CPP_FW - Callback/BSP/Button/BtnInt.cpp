/******************
** FILE: BtnInt.cpp
**
** DESCRIPTION:
**  BtnInt class implementation using Interrupts
**
** CREATED: 22/2/2019, by Amit Chaudhary
******************/
#include "BtnInt.h"


namespace BSP
{
    
    
BtnInt::BtnInt(Pin_t Pin, Pull_t Pull, uint8_t Debounce,  HALCallback_t L2HCallback, HALCallback_t H2LCallback) :
        _BtnPin(Pin,(Pull==BTN_PULL_UP?HAL::GpioInput::INPUT_PULL_UP:HAL::GpioInput::INPUT_PULL_DOWN),HAL::GpioInput::IT_ON_RISING_FALLING,BtnISR ),
        _debounce(Debounce),
        _previousState(BTN_IDLE),
        _currentState(BTN_IDLE),
        _startMillis(0U),
        _L2HCallback(L2HCallback),
        _H2LCallback(H2LCallback)
{
    
    
}
BtnInt::Status_t BtnInt::HwInit(void *pInitStruct)
{
    (void)pInitStruct;
    _previousState = Read();
    return _BtnPin.HwInit(); 
}

void BtnInt::BtnISR()
{

}
void BtnInt::RunStateMachine()
{      
//    switch(_currentState)
//    {
//        
//    case BTN_IDLE:
//        
//        if(Read() == _previousState)
//            return;
//        
//        if(_debounce != 0)
//        {
//            _currentState = BTN_DEBOUNCE; 
//            _startMillis  = _getMillis();
//        }
//        else
//        {
//            _currentState = Read();            
//        }
//        break;
//        
//    case BTN_DEBOUNCE:
//        
//        if(_getMillis() - (uint32_t)_startMillis >= _debounce)
//        {
//            if (Read() != _previousState)
//            {
//                _currentState = Read();  
//            }
//            else
//            {
//                _currentState = BTN_IDLE;    
//            }            
//        }
//        break;
//        
//    case BTN_LOW: 
//        _currentState = BTN_IDLE;
//        _previousState = BTN_LOW;
//        if(_H2LCallback) _H2LCallback();
//        break;
//        
//    case BTN_HIGH:
//        _currentState = BTN_IDLE;
//        _previousState = BTN_HIGH;
//        if(_L2HCallback) _L2HCallback();        
//        break;         
//        
//    default: break;
//    }
//    
}

}
