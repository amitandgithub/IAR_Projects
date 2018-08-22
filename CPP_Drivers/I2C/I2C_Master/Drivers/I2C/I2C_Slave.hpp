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

namespace Peripherals
{
    
class I2C_Slave  : public I2C_Base
{
public:
    
    I2C_Slave(I2CPort_t I2CPort, I2CBaudRate_t I2CBaudRate = BAUD_100K);
  
    ~I2C_Slave(){HwDeInit();}
  
    Status_t     HwInit          ();
  
    Status_t     HwDeInit        (){return HAL_I2C_DeInit(&m_hi2c);}
  
    Status_t     HwConfig        (void* pConfigStruct){return 1;}
  
    Status_t     Send            (uint8_t *pTxBuf, uint16_t Len);
  
    Status_t     Read            (uint8_t *pRxBuf, uint16_t Len);
  
    Status_t     Xfer            (uint8_t *pTxBuf, uint16_t TxLen,
                                               uint8_t *pRxBuf, uint16_t RxLen);
    Status_t     Abort           ();
  
    Status_t     Reset           ();
  
    Status_t     GetState        ();
  
    Status_t     GetErrorStatus  ();
  
private:
    I2C_HandleTypeDef       m_hi2c;
    I2CPort_t               m_I2CPort;   
  
};


}
#endif //I2C_Drv_hpp
