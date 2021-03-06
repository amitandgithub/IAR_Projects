/******************
** CLASS: I2C
**
** DESCRIPTION:
**  I2C class Implementation
**
** CREATED: 8/14/2018, by Amit Chaudhary
**
** FILE: I2C_Drv.cpp
**
******************/
#ifndef I2C_Master_IT_hpp
#define I2C_Master_IT_hpp

#include "I2C_Base.hpp"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"
#include "Interrupt.hpp"


namespace Peripherals
{
    
class I2C_Master_IT  : public I2C_Base, public Interrupt 
{
public:
    static const uint32_t DONE = 0;
    static const uint32_t BUSY = 1;
    
    typedef void (*Callback_t) ();
    
    I2C_Master_IT(I2CPort_t I2CPort, I2CBaudRate_t I2CBaudRate = BAUD_100K);
  
    ~I2C_Master_IT(){HwDeInit();}
  
    Status_t    HwInit          ();
  
    Status_t    HwDeInit        (){return HAL_I2C_DeInit(&m_hi2c);}
    
    Status_t    HwConfig        (void* pConfigStruct);
  
    static      Status_t     Send            (uint16_t DevAddress, uint8_t *pTxBuf, uint16_t Len);
    
    static      Status_t     Send            (uint16_t DevAddress, uint8_t *pTxBuf, uint16_t Len, uint32_t XferOptions);
  
    static      Status_t     Read            (uint16_t DevAddress, uint8_t *pRxBuf, uint16_t Len);
    
    static      Status_t     Read            (uint16_t DevAddress, uint8_t *pRxBuf, uint16_t Len, uint32_t XferOptions);
  
                Status_t     Xfer            (uint16_t DevAddress, uint8_t *pTxBuf, uint16_t TxLen, uint8_t *pRxBuf, uint16_t RxLen);
                
                Status_t     Abort           ();
  
                Status_t     Reset           ();
  
                Status_t     GetState        (){return m_hi2c.State;}
  
                Status_t     GetErrorStatus  (){return m_hi2c.ErrorCode;}
                
                Status_t     Scan            (uint16_t *DevAddress, uint16_t len );
    
 
  
private:
    static void EventISR();    
    static void ErrorISR();
    
   
    I2CPort_t                      m_I2CPort;  
    
public:
     static I2C_HandleTypeDef      m_hi2c;
    static Callback_t              m_RxCallback;
    static Callback_t              m_TxCallback;
    static volatile uint32_t                       m_TxDone;
    static volatile uint32_t                       m_RxDone;
  
};


}
#endif //I2C_Drv_hpp
