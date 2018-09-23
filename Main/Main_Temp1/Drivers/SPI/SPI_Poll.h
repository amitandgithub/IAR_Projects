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


#include "SPI_Base.h"

namespace Peripherals
{
    
class SPI_Poll : public SPI_Base
{
public:
    static const uint32_t SPI_POLL_DELAY = 0xFFUL;
    
    SPI_Poll (SPIx_t spix, GpioOutput* CS, HZ_t hz = 100000UL);
    
    virtual ~SPI_Poll (){HwDeinit();};
    
    virtual       Status_t        HwInit          ();
    
    virtual       Status_t        HwDeinit        (){ return HAL_SPI_DeInit(&m_hspi);}
    
    virtual       Status_t        Tx            (uint8_t* pTxBuf, uint16_t TxLen);
    
    virtual       Status_t        Rx            (uint8_t* pRxBuf, uint16_t RxLen);  
    
    virtual       Status_t        TxRx          (uint8_t* pTxBuf, uint8_t* pRxBuf, uint16_t Len); 
    
private: 
    GpioOutput* m_pCS;
    SPIx_t m_spix;
    uint32_t m_hz;
    SPI_HandleTypeDef m_hspi;
  
};

}
#endif //SPI_h
