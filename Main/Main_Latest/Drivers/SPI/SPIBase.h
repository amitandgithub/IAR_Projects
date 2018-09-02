/******************
** CLASS: SPIBase
**
** DESCRIPTION:
**  SPI Base class
**
** CREATED: 9/2/2018, by Amit Chaudhary
**
** FILE: SPI_Base.h
**
******************/
#ifndef SPI_Base_h
#define SPI_Base_h

#include "stm32f1xx_hal.h"
#include "Peripheral.hpp"
#include "stm32f1xx_hal_spi.h"


namespace Peripherals
{
    
class SPIBase : public Peripheral
{
public:
    typedef enum 
    {
        SPI1_A4_A5_A6_A7,
        SPI1_A15_B3_B4_B5,
        SPI2_B12_B13_B14_B15
    }SPIx_t;
    
  SPIBase(){;}
  
  virtual ~SPIBase(){;}
  
  virtual       Status_t        HwInit          () = 0;
  
  virtual       Status_t        HwDeinit        () = 0;
  
  virtual       Status_t        Send            (uint8_t* pTxBuf, uint16_t TxLen) = 0;
  
  virtual       Status_t        Read            (uint8_t* pRxBuf, uint16_t RxLen) = 0;  
  
  virtual       Status_t        Xfer            (uint8_t* pTxBuf, uint16_t TxLen, uint8_t* pRxBuf, uint16_t RxLen) = 0; 
  
  
};


}
#endif //SPI_Base_h
