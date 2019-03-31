/******************
** CLASS: BtnPoll
**
** DESCRIPTION:
**  Implements the basic button functionality with polling method
**
** CREATED: 1/31/2019, by Amit Chaudhary
**
** FILE: BtnPoll.h
**
******************/
#ifndef BtnPoll_h
#define BtnPoll_h

#include "GpioInput.h"
#define BTN_DEBOUNCE_REQUIRED
namespace BSP
{
    
using namespace HAL;   

class BtnPoll
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
    typedef void(*BtnHandler_t)();
    using Status_t = uint32_t;
    
    typedef enum
    {
        BTN_PULL_UP,
        BTN_PULL_DOWN
    }Pull_t;
    
    BtnPoll(Pin_t Pin, Pull_t Pull = BTN_PULL_DOWN, uint8_t Debounce = 3U, BtnHandler_t LowHandler = nullptr, BtnHandler_t HighHandler = nullptr );
    ~BtnPoll(){};
    Status_t HwInit(void *pInitStruct = nullptr);
	void RunStateMachine();
	BtnState_t Read();
    bool getState();
	void RegisterHandler(BtnHandler_t LowHandler, BtnHandler_t HighHandler);
    uint32_t _getMillis();
private:
     HAL::GpioInput         _BtnPin;
     BtnState_t             _previousState;
     BtnState_t             _currentState;
     uint8_t                _debounce;
     uint16_t               _startMillis;
     BtnHandler_t           _lowHandler;
     BtnHandler_t           _highHandler;  
};


inline void BtnPoll::RegisterHandler(BtnHandler_t LowHandler, BtnHandler_t HighHandler)
{
    _lowHandler = LowHandler;
    _highHandler = HighHandler;    
}

inline BtnPoll::BtnState_t BtnPoll::Read()
{
    return ( _BtnPin.Read()? BTN_HIGH: BTN_LOW);
}

inline uint32_t BtnPoll::_getMillis()
{
    return HAL_GetTick();
}

inline bool BtnPoll::getState()
{
    return _previousState? true:false;
}

}



#endif //BtnPoll_h
