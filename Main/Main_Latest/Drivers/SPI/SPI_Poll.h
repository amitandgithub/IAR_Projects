/******************
** CLASS: SPI 
**
** DESCRIPTION:
**  SPI implementation in polling mode
**
** CREATED: 9/2/2018, by Amit Chaudhary
**
** FILE: SPI.h
**
******************/
#ifndef SPI_h
#define SPI_h


#include "SPIBase.h"

namespace Peripherals
{
    
class SPI_Poll : public SPIBase
{
public:
    static const uint32_t SPI_POLL_DELAY = 0xFFUL;
    
    SPI_Poll (SPIx_t spix = SPI1_A4_A5_A6_A7, uint32_t hz = 100000UL);
    
    virtual ~SPI_Poll (){HwDeinit();};
    
    virtual       Status_t        HwInit          ();
    
    virtual       Status_t        HwDeinit        (){ return HAL_SPI_DeInit(&m_hspi);}
    
    virtual       Status_t        Send            (uint8_t* pTxBuf, uint16_t TxLen, GpioOutput* CS = nullptr);
    
    virtual       Status_t        Read            (uint8_t* pRxBuf, uint16_t RxLen, GpioOutput* CS = nullptr);  
    
    virtual       Status_t        Xfer            (uint8_t* pTxBuf, uint8_t* pRxBuf, uint16_t Len, GpioOutput* CS); 
    
private: 
    GpioOutput* m_pDefault_CS;
    SPIx_t m_spix;
    uint32_t m_hz;
    SPI_HandleTypeDef m_hspi;
  
};

}
#endif //SPI_h
