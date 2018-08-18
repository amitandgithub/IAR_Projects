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
#ifndef I2C_Drv_hpp
#define I2C_Drv_hpp

#include "Peripheral.hpp"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"

//#define HAL_I2C_MODULE_ENABLED

namespace Peripherals
{
    
class I2C_Master  : public Peripheral
{
public:
    
    typedef enum
    {
		I2C1_SCL_B6_SDA_B7      = 0,
		I2C1_SCL_B8_SDA_B9      = 1,
		I2C2_SCL_B11_SDA_B12    = 2,       
    }I2CPort_t;
    
    typedef enum
    {
		BAUD_100K      = 0,
		BAUD_400K      = 1,
		BAUD_1M        = 2,       
    }I2CBaudRate_t;
    
    typedef struct
    {
       uint8_t      Addrs;
       uint8_t*     pBuf;
       uint32_t     Len;       
    }I2CPkt_t;
    
    typedef struct
    {
       uint8_t      Addrs;
       uint8_t*     pTxBuf;
       uint32_t     TxLen;  
       uint8_t*     pRxBuf;
       uint32_t     RxLen;
    }I2CTransaction_t;
    
  I2C_Master(I2CPort_t I2CPort, I2CBaudRate_t I2CBaudRate = BAUD_100K);
  
  ~I2C_Master(){HwDeInit();}
  
  virtual      Status_t     HwInit          ();
  
  virtual      Status_t     HwDeInit        (){return HAL_I2C_DeInit(&m_hi2c);}
  
  virtual      Status_t     HwConfig        (void* pConfigStruct){return 1;}
  
  Status_t     Send            (uint16_t Addrs, uint8_t *pTxBuf, uint16_t Len);
  
  Status_t     Send            (I2CPkt_t* pPkt);
  
  Status_t     Read            (uint16_t Addrs, uint8_t *pRxBuf, uint16_t Len);
  
  Status_t     Read            (I2CPkt_t* pPkt);
  
  Status_t     Xfer            (uint16_t Addrs, uint8_t *pTxBuf, uint16_t TxLen,
                                               uint8_t *pRxBuf, uint16_t RxLen);
  Status_t     Abort           ();
  
  Status_t     Reset           ();
  
  Status_t     GetState        ();
  
  Status_t     GetErrorStatus  ();
  
  Status_t     Scan(uint16_t *DevAddress, uint16_t len );
  
  Status_t    IsDeviceReady(uint16_t DevAddress, uint32_t Trials, uint32_t Timeout){return HAL_I2C_IsDeviceReady(&m_hi2c, DevAddress, Trials, Timeout);}
  
private:
    I2C_HandleTypeDef       m_hi2c;
    I2CPort_t               m_I2CPort;   
    
    void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c);
    ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT);
  
};


}
#endif //I2C_Drv_hpp
