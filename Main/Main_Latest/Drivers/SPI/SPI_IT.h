/******************
** CLASS: SPI 
**
** DESCRIPTION:
**  SPI implementation in Interrupt mode
**
** CREATED: 9/2/2018, by Amit Chaudhary
**
** FILE: SPI.h
**
******************/
#ifndef SPI_IT_h
#define SPI_IT_h


#include "SPI_Base.h"
#include "Interrupt.hpp"

namespace Peripherals
{
    
class SPI_IT : public SPI_Base, public Interrupt 
{
public:

    
    SPI_IT (SPIx_t spix = SPI1_A4_A5_A6_A7, uint32_t hz = 100000UL);
    
    virtual ~SPI_IT (){HwDeinit();};
    
    virtual       Status_t        HwInit          ();
    
    virtual       Status_t        HwDeinit        (){ return HAL_SPI_DeInit(&m_hspi);}
    
    virtual       Status_t        Tx              (uint8_t* pTxBuf, uint16_t TxLen, GpioOutput* CS = nullptr);
    
    virtual       Status_t        Rx              (uint8_t* pRxBuf, uint16_t RxLen, GpioOutput* CS = nullptr);  
    
    virtual       Status_t        TxRx            (uint8_t* pTxBuf, uint8_t* pRxBuf, uint16_t Len, GpioOutput* CS);  
    
                  Status_t       Post             (Transaction_t aTransaction);
                  
private:
    static        void           IRQHandler       ();
private: 
    GpioOutput* m_pDefault_CS;
    SPIx_t m_spix;
    uint32_t m_hz;
    static SPI_HandleTypeDef m_hspi;
  
};

}
#endif //SPI_IT_h
