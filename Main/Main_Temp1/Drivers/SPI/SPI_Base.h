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
#include "GpioOutput.hpp"

namespace Peripherals
{
    
class SPI_Base : public Peripheral
{
public:
    typedef enum 
    {
        SPI_TX_COMPLETE         = 0x01,
        SPI_RX_COMPLETE         = 0x02,
        SPI_TXRX_COMPLETE       = 0x04,
        SPI_TX_HALF_COMPLETE    = 0x08,
        SPI_RX_HALF_COMPLETE    = 0x10,
        SPI_TXRX_HALF_COMPLETE  = 0x20,
    }SPI_Completetion_Status_t;
    
    typedef enum 
    {
        SPI1_A4_A5_A6_A7,
        SPI1_A15_B3_B4_B5,
        SPI2_B12_B13_B14_B15
    }SPIx_t;
    
        typedef uint32_t HZ_t;
    
    typedef struct
    {
        uint32_t            Event       :14;
        uint32_t            TimeUnits   :2;
        uint16_t            TimeValue   :16;        
    }TxnStatus_t;
    
    typedef struct
    {
        uint8_t*        TxBuf;
        uint8_t*        RxBuf;
        uint16_t        TxLen;
        uint16_t        RxLen;
        HZ_t            hz;
        GpioOutput*     pCS;
        TxnStatus_t     TxnStatus; 
    }Transaction_t;
    
    typedef void (*Callback_t) ();
     
    static const uint32_t SPI_POLL_DELAY = 0xFFUL;
    
    SPI_Base(){;}
    
    virtual ~SPI_Base(){;}
    
    virtual       Status_t        HwInit            () = 0;
    
    virtual       Status_t        HwDeinit          () = 0;
    
    virtual       Status_t        Tx                (uint8_t* pTxBuf, uint16_t TxLen) = 0;
    
    virtual       Status_t        Rx                (uint8_t* pRxBuf, uint16_t RxLen) = 0;  
    
    virtual       Status_t        TxRx              (uint8_t* pTxBuf, uint8_t* pRxBuf, uint16_t Len) = 0;
    
    static       Status_t        Post               (Transaction_t aTransaction){return 1;};
    
    static       Status_t        SPI_Init           (SPIx_t SPIx, HZ_t HZ, SPI_HandleTypeDef* phSPI);
    
    static        void           SPI1__IRQHandler   ();
    
    static        void           SPI2__IRQHandler   ();
    
    static        void           DMA_Ch2_IRQHandler (); 
    
    static        void           DMA_Ch3_IRQHandler (); 
    
    static        void           DMA_Ch4_IRQHandler (); 
    
    static        void           DMA_Ch5_IRQHandler (); 
    
  
public:

    static SPI_HandleTypeDef m_hspi_1;
    static SPI_HandleTypeDef m_hspi_2;
    
    static DMA_HandleTypeDef* m_phdma_spi1_rx;
    static DMA_HandleTypeDef* m_phdma_spi1_tx;
    static DMA_HandleTypeDef* m_phdma_spi2_rx;
    static DMA_HandleTypeDef* m_phdma_spi2_tx; 
    
    static DMA_HandleTypeDef m_hdma_spi1_rx;
    static DMA_HandleTypeDef m_hdma_spi1_tx;
    static DMA_HandleTypeDef m_hdma_spi2_rx;
    static DMA_HandleTypeDef m_hdma_spi2_tx;
    static SPI_HandleTypeDef* m_phspi_1;
    static SPI_HandleTypeDef* m_phspi_2;
    
    static Peripherals::GpioOutput* m_pChipSelect_SPI1;
    static Peripherals::GpioOutput* m_pChipSelect_SPI2;

    static Callback_t                   SPI1_TxDoneCallback;
    static Callback_t                   SPI1_RxDoneCallback;
    static Callback_t                   SPI1_TxRxDoneCallback;
    static Callback_t                   SPI1_TxHalfDoneCallback;
    static Callback_t                   SPI1_RxHalfDoneCallback;
    static Callback_t                   SPI1_TxRxHalfDoneCallback;  
    
    static Callback_t                   SPI2_TxDoneCallback;
    static Callback_t                   SPI2_RxDoneCallback;
    static Callback_t                   SPI2_TxRxDoneCallback;
    static Callback_t                   SPI2_TxHalfDoneCallback;
    static Callback_t                   SPI2_RxHalfDoneCallback;
    static Callback_t                   SPI2_TxRxHalfDoneCallback;
};


}
#endif //SPI_Base_h
