/******************
** CLASS: BtnInt
**
** DESCRIPTION:
**  Implements the basic button functionality with Interrupt method
**
** CREATED: 22/2/2019, by Amit Chaudhary
**
** FILE: BtnInt.h
**
******************/
#ifndef BtnInt_h
#define BtnInt_h

#include "GpioInput.h"
#define BTN_DEBOUNCE_REQUIRED
namespace BSP
{
    
using namespace HAL;   

class BtnInt
{
public:
    
    typedef enum
	{
        BTN_LOW,
        BTN_HIGH,
        BTN_IDLE,
        BTN_DEBOUNCE       
	}BtnState_t;
    
    using Pin_t = HAL::Gpio::Pin_t;
    using Status_t = uint32_t;
    
    typedef enum
    {
        BTN_PULL_UP,
        BTN_PULL_DOWN
    }Pull_t;
    
    BtnInt(Pin_t Pin, Pull_t Pull = BTN_PULL_DOWN, uint8_t Debounce = 3U, HALCallback_t L2HCallback = nullptr, HALCallback_t H2LCallback = nullptr );
    ~BtnInt(){};
    Status_t HwInit(void *pInitStruct = nullptr);
	void RunStateMachine();
	BtnState_t Read();
    bool getState();
    uint32_t _getMillis();
    void RegisterHandler(HALCallback_t L2HCallback, HALCallback_t H2LCallback);
private:
//static void    
private:
     HAL::GpioInput         _BtnPin;
     BtnState_t             _previousState;
     BtnState_t             _currentState;
     uint8_t                _debounce;
     uint16_t               _startMillis;
     HALCallback_t          _L2HCallback;
     HALCallback_t          _H2LCallback;
};

inline void BtnInt::RegisterHandler(HALCallback_t L2HCallback, HALCallback_t H2LCallback)
{
    _L2HCallback = L2HCallback;
    _H2LCallback = H2LCallback;    
}

inline BtnInt::BtnState_t BtnInt::Read()
{
    return ( _BtnPin.Read()? BTN_HIGH: BTN_LOW);
}

inline uint32_t BtnInt::_getMillis()
{
    return HAL_GetTick();
}

inline bool BtnInt::getState()
{
    return _previousState? true:false;
}

}



#endif //BtnInt_h
