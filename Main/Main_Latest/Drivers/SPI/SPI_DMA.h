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
#ifndef SPI_DMA_h
#define SPI_DMA_h


#include "SPI_Base.h"
#include "Interrupt.hpp"
#include "GpioOutput.hpp"

namespace Peripherals
{
    
class SPI_DMA : public SPI_Base, public Interrupt 
{
public:
     
    static const uint32_t SPI_POLL_DELAY = 0xFFUL;
    
    SPI_DMA (SPIx_t spix = SPI1_A4_A5_A6_A7, uint32_t hz = 100000UL);
    
    virtual ~SPI_DMA (){HwDeinit();};
    
    virtual       Status_t        HwInit          ();
    
    virtual       Status_t        HwDeinit        (){ return HAL_SPI_DeInit(&m_hspi_1);}
    
    virtual       Status_t        Tx              (uint8_t* pTxBuf, uint16_t TxLen, GpioOutput* CS = nullptr);
    
    virtual       Status_t        Rx              (uint8_t* pRxBuf, uint16_t RxLen, GpioOutput* CS = nullptr);  
    
    virtual       Status_t        TxRx            (uint8_t* pTxBuf, uint8_t* pRxBuf, uint16_t Len, GpioOutput* CS);  
    
                  Status_t        Post            (Transaction_t aTransaction);
                  
//    static Peripherals::GpioOutput CS_PB12(Peripherals::GpioOutput::PORT_t Port, Peripherals::GpioOutput::PIN_t Pin);
//    static Peripherals::GpioOutput CS_PA4(Peripherals::GpioOutput::PORT_t Port, Peripherals::GpioOutput::PIN_t Pin);
//    static Peripherals::GpioOutput CS_PA15(Peripherals::GpioOutput::PORT_t Port, Peripherals::GpioOutput::PIN_t Pin);
    
private:
    static        void           SPI1__IRQHandler         ();
    static        void           SPI2__IRQHandler         ();
    static        void           DMA_Ch2_IRQHandler       (); 
    static        void           DMA_Ch3_IRQHandler       (); 
    static        void           DMA_Ch4_IRQHandler       (); 
    static        void           DMA_Ch5_IRQHandler       (); 
    static        void           TxCompleteCallback       ();
private: 

    SPIx_t m_spix;
    uint32_t m_hz;
    static DMA_HandleTypeDef hdma_spi1_rx;
    static DMA_HandleTypeDef hdma_spi1_tx;
    static DMA_HandleTypeDef hdma_spi2_rx;
    static DMA_HandleTypeDef hdma_spi2_tx;  
};

}
#endif //SPI_DMA_h
