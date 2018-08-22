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
#ifndef I2C_Slave_hpp
#define I2C_Slave_hpp

#include "I2C_Base.hpp"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"
#include "Interrupt.hpp"


namespace Peripherals
{
    
class I2C_Slave  : public I2C_Base, public Interrupt 
{
public:
    
    typedef void (*Callback_t) ();
    
    I2C_Slave(I2CPort_t I2CPort, I2CBaudRate_t I2CBaudRate = BAUD_100K);
  
    ~I2C_Slave(){HwDeInit();}
  
    Status_t     HwInit          ();
  
    Status_t     HwDeInit        (){return HAL_I2C_DeInit(&m_hi2c);}
  
    Status_t     HwConfig        (void* pConfigStruct){return 1;}
  
    static      Status_t     Send            (uint8_t *pTxBuf, uint16_t Len);
    
    static      Status_t     Send            (uint8_t *pTxBuf, uint16_t Len, uint32_t XferOptions);
  
    static      Status_t     Read            (uint8_t *pRxBuf, uint16_t Len);
    
    static      Status_t     Read            (uint8_t *pRxBuf, uint16_t Len, uint32_t XferOptions);
  
                Status_t     Xfer            (uint8_t *pTxBuf, uint16_t TxLen,
                                               uint8_t *pRxBuf, uint16_t RxLen);
                Status_t     Abort           ();
  
                Status_t     Reset           ();
  
                Status_t     GetState        (){return m_hi2c.State;}
  
                Status_t     GetErrorStatus  ();
    
    
 
  
private:
    static void I2C_EV_ISR();    
    static void I2C_ER_ISR();
    
    static I2C_HandleTypeDef       m_hi2c;
    I2CPort_t                      m_I2CPort;  
    
public:
    static Callback_t              m_RxCallback;
    static Callback_t              m_TxCallback;
  
};


}
#endif //I2C_Drv_hpp
