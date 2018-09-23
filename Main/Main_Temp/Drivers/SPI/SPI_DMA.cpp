/******************
** FILE: SPI_DMA.cpp
**
** DESCRIPTION:
**  SPI implementation in Interrupt mode
**
** CREATED: 9/2/2018, by Amit Chaudhary
******************/

#include "SPI_DMA.h"

namespace Peripherals
{


DMA_HandleTypeDef* SPI_DMA::m_phdma_spi1_rx;
DMA_HandleTypeDef* SPI_DMA::m_phdma_spi1_tx;
DMA_HandleTypeDef* SPI_DMA::m_phdma_spi2_rx;
DMA_HandleTypeDef* SPI_DMA::m_phdma_spi2_tx;
SPI_HandleTypeDef* SPI_DMA::m_phspi_1;
SPI_HandleTypeDef* SPI_DMA::m_phspi_2;


SPI_DMA::SPI_DMA (SPIx_t spix, GpioOutput* pCS, uint32_t hz, 
                  SPI_HandleTypeDef* phspi_x,
                  DMA_HandleTypeDef* phdma_spix_rx,
                  DMA_HandleTypeDef* phdma_spix_tx)
                  : m_hz(hz),
                    m_spix(spix)

{
    
    
     if((m_spix == SPI1_A4_A5_A6_A7) || (m_spix == SPI1_A15_B3_B4_B5) )
     {
        m_pChipSelect_SPI1 = pCS;
        
        m_phspi_1 = phspi_x;
        m_phdma_spi1_rx = phdma_spix_rx;
        m_phdma_spi1_tx = phdma_spix_tx;
        
        if( (m_phspi_1 == nullptr) || (m_phdma_spi1_rx == nullptr) || (m_phdma_spi1_tx == nullptr) || (m_pChipSelect_SPI1 == nullptr)  )
        {
            while(1); // Fatal Error
        }
        
     }
     else if(m_spix == SPI2_B12_B13_B14_B15)
     {
        m_pChipSelect_SPI2 = pCS;
        m_phspi_2 = phspi_x;
        m_phdma_spi2_rx = phdma_spix_rx;
        m_phdma_spi2_tx = phdma_spix_tx;
        
        if( (m_phspi_2 == nullptr) || (m_phdma_spi2_rx == nullptr) || (m_phdma_spi2_tx == nullptr) || (m_pChipSelect_SPI2 == nullptr) )
        {
            while(1); // Fatal Error
        }
     }
     else
     {
         while(1); // Fatal error
     }
}


Status_t SPI_DMA::HwInit ()
{
    GPIO_InitTypeDef GPIO_InitStruct;  
        
    /* SPI1 parameter configuration*/
    if(m_spix == SPI1_A4_A5_A6_A7)
    {   
        m_pChipSelect_SPI1->HwInit(); 
       
        m_phspi_1->Instance = SPI1;
        
        __HAL_RCC_GPIOA_CLK_ENABLE();
        
        /* Peripheral clock enable */
        __HAL_RCC_SPI1_CLK_ENABLE();
        
        /* DMA controller clock enable */
        __HAL_RCC_DMA1_CLK_ENABLE();
        
        /**SPI1 GPIO Configuration    
        PA4     ------> SPI1_NSS
        PA5     ------> SPI1_SCK
        PA6     ------> SPI1_MISO
        PA7     ------> SPI1_MOSI 
        */
        GPIO_InitStruct.Pin     = GPIO_PIN_5|GPIO_PIN_7;
        GPIO_InitStruct.Mode    = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
        GPIO_InitStruct.Pin     = GPIO_PIN_6;
        GPIO_InitStruct.Mode    = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull    = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
        /* SPI1 DMA Init */
        /* SPI1_RX Init */
        m_phdma_spi1_rx->Instance                           = DMA1_Channel2;
        m_phdma_spi1_rx->Init.Direction                     = DMA_PERIPH_TO_MEMORY;
        m_phdma_spi1_rx->Init.PeriphInc                     = DMA_PINC_DISABLE;
        m_phdma_spi1_rx->Init.MemInc                        = DMA_MINC_ENABLE;
        m_phdma_spi1_rx->Init.PeriphDataAlignment           = DMA_PDATAALIGN_BYTE;
        m_phdma_spi1_rx->Init.MemDataAlignment              = DMA_MDATAALIGN_BYTE;
        m_phdma_spi1_rx->Init.Mode                          = DMA_NORMAL;
        m_phdma_spi1_rx->Init.Priority                      = DMA_PRIORITY_LOW;
        if (HAL_DMA_Init(m_phdma_spi1_rx) != HAL_OK)
        {
            //_Error_Handler(__FILE__, __LINE__);
             return HAL_ERROR;
        }
        
        __HAL_LINKDMA(m_phspi_1,hdmarx,*m_phdma_spi1_rx);
        
        /* SPI1_TX Init */
        m_phdma_spi1_tx->Instance                           = DMA1_Channel3;
        m_phdma_spi1_tx->Init.Direction                     = DMA_MEMORY_TO_PERIPH;
        m_phdma_spi1_tx->Init.PeriphInc                     = DMA_PINC_DISABLE;
        m_phdma_spi1_tx->Init.MemInc                        = DMA_MINC_ENABLE;
        m_phdma_spi1_tx->Init.PeriphDataAlignment           = DMA_PDATAALIGN_BYTE;
        m_phdma_spi1_tx->Init.MemDataAlignment              = DMA_MDATAALIGN_BYTE;
        m_phdma_spi1_tx->Init.Mode                          = DMA_NORMAL;
        m_phdma_spi1_tx->Init.Priority                      = DMA_PRIORITY_LOW;
        if (HAL_DMA_Init(m_phdma_spi1_tx) != HAL_OK)
        {
           // _Error_Handler(__FILE__, __LINE__);
            return HAL_ERROR;
        }
        
        __HAL_LINKDMA(m_phspi_1,hdmatx,*m_phdma_spi1_tx);
        
        m_phspi_1->Init.Mode                = SPI_MODE_MASTER;
        m_phspi_1->Init.Direction           = SPI_DIRECTION_2LINES;
        m_phspi_1->Init.DataSize            = SPI_DATASIZE_8BIT;
        m_phspi_1->Init.CLKPolarity         = SPI_POLARITY_LOW;
        m_phspi_1->Init.CLKPhase            = SPI_PHASE_1EDGE;
        m_phspi_1->Init.NSS                 = SPI_NSS_HARD_OUTPUT;
        m_phspi_1->Init.BaudRatePrescaler   = SPI_BAUDRATEPRESCALER_256;//SPI_BAUDRATEPRESCALER_2;
        m_phspi_1->Init.FirstBit            = SPI_FIRSTBIT_MSB;
        m_phspi_1->Init.TIMode              = SPI_TIMODE_DISABLE;
        m_phspi_1->Init.CRCCalculation      = SPI_CRCCALCULATION_DISABLE;
        m_phspi_1->Init.CRCPolynomial       = 10;
        
        if (HAL_SPI_Init(m_phspi_1) != HAL_OK)
        {
            return HAL_ERROR;
        }    
        
        Peripherals::Interrupt::RegisterInterrupt_Vct_Table(SPI1__IRQHandler,static_cast<Peripherals::Interrupt::IRQn>(SPI1_IRQHandler));
        Peripherals::Interrupt::RegisterInterrupt_Vct_Table(DMA_Ch2_IRQHandler,static_cast<Peripherals::Interrupt::IRQn>(DMA1_Channel2_IRQn),0,0);
        Peripherals::Interrupt::RegisterInterrupt_Vct_Table(DMA_Ch3_IRQHandler,static_cast<Peripherals::Interrupt::IRQn>(DMA1_Channel3_IRQn),0,0);
        
    }
    else if(m_spix == SPI1_A15_B3_B4_B5)
    {
        m_pChipSelect_SPI1->HwInit(); 
        
        m_phspi_1->Instance = SPI1;
        
        /* Peripheral clock enable */
        __HAL_RCC_SPI2_CLK_ENABLE();
        
        /* DMA controller clock enable */
        __HAL_RCC_DMA1_CLK_ENABLE(); 
        
        /**SPI2 GPIO Configuration    
        PA15     ------> SPI1_NSS
        PB3     ------> SPI1_SCK
        PB4     ------> SPI1_MISO
        PB5     ------> SPI1_MOSI 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_5;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        
        GPIO_InitStruct.Pin = GPIO_PIN_4;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        
        /* SPI1 DMA Init */
        /* SPI1_RX Init */
        m_phdma_spi1_rx->Instance                           = DMA1_Channel2;
        m_phdma_spi1_rx->Init.Direction                     = DMA_PERIPH_TO_MEMORY;
        m_phdma_spi1_rx->Init.PeriphInc                     = DMA_PINC_DISABLE;
        m_phdma_spi1_rx->Init.MemInc                        = DMA_MINC_ENABLE;
        m_phdma_spi1_rx->Init.PeriphDataAlignment           = DMA_PDATAALIGN_BYTE;
        m_phdma_spi1_rx->Init.MemDataAlignment              = DMA_MDATAALIGN_BYTE;
        m_phdma_spi1_rx->Init.Mode                          = DMA_NORMAL;
        m_phdma_spi1_rx->Init.Priority                      = DMA_PRIORITY_LOW;
        if (HAL_DMA_Init(m_phdma_spi1_rx) != HAL_OK)
        {
            //_Error_Handler(__FILE__, __LINE__);
             return HAL_ERROR;
        }
        
        __HAL_LINKDMA(m_phspi_1,hdmarx,*m_phdma_spi1_rx);
        
        /* SPI1_TX Init */
        m_phdma_spi1_tx->Instance                           = DMA1_Channel3;
        m_phdma_spi1_tx->Init.Direction                     = DMA_MEMORY_TO_PERIPH;
        m_phdma_spi1_tx->Init.PeriphInc                     = DMA_PINC_DISABLE;
        m_phdma_spi1_tx->Init.MemInc                        = DMA_MINC_ENABLE;
        m_phdma_spi1_tx->Init.PeriphDataAlignment           = DMA_PDATAALIGN_BYTE;
        m_phdma_spi1_tx->Init.MemDataAlignment              = DMA_MDATAALIGN_BYTE;
        m_phdma_spi1_tx->Init.Mode                          = DMA_NORMAL;
        m_phdma_spi1_tx->Init.Priority                      = DMA_PRIORITY_LOW;
        
        if (HAL_DMA_Init(m_phdma_spi1_tx) != HAL_OK)
        {
           // _Error_Handler(__FILE__, __LINE__);
            return HAL_ERROR;
        }
        
        __HAL_LINKDMA(m_phspi_1,hdmatx,*m_phdma_spi1_tx);
        
        m_phspi_1->Init.Mode                = SPI_MODE_MASTER;
        m_phspi_1->Init.Direction           = SPI_DIRECTION_2LINES;
        m_phspi_1->Init.DataSize            = SPI_DATASIZE_8BIT;
        m_phspi_1->Init.CLKPolarity         = SPI_POLARITY_LOW;
        m_phspi_1->Init.CLKPhase            = SPI_PHASE_1EDGE;
        m_phspi_1->Init.NSS                 = SPI_NSS_HARD_OUTPUT;
        m_phspi_1->Init.BaudRatePrescaler   = SPI_BAUDRATEPRESCALER_256;//SPI_BAUDRATEPRESCALER_2;
        m_phspi_1->Init.FirstBit            = SPI_FIRSTBIT_MSB;
        m_phspi_1->Init.TIMode              = SPI_TIMODE_DISABLE;
        m_phspi_1->Init.CRCCalculation      = SPI_CRCCALCULATION_DISABLE;
        m_phspi_1->Init.CRCPolynomial       = 10;
        
        if (HAL_SPI_Init(m_phspi_1) != HAL_OK)
        {
            return HAL_ERROR;
        }    
        
        Peripherals::Interrupt::RegisterInterrupt_Vct_Table(SPI1__IRQHandler,static_cast<Peripherals::Interrupt::IRQn>(SPI1_IRQHandler));
        Peripherals::Interrupt::RegisterInterrupt_Vct_Table(DMA_Ch2_IRQHandler,static_cast<Peripherals::Interrupt::IRQn>(DMA1_Channel2_IRQn),0,0);
        Peripherals::Interrupt::RegisterInterrupt_Vct_Table(DMA_Ch3_IRQHandler,static_cast<Peripherals::Interrupt::IRQn>(DMA1_Channel3_IRQn),0,0);
    }
    else if(m_spix == SPI2_B12_B13_B14_B15)
    {        
        m_pChipSelect_SPI2->HwInit(); 
        
        m_phspi_2->Instance = SPI2;
        
        /* Peripheral clock enable */
        __HAL_RCC_SPI2_CLK_ENABLE();
        
        /* DMA controller clock enable */
        __HAL_RCC_DMA1_CLK_ENABLE();    
        
        /**SPI2 GPIO Configuration    
        PB12     ------> SPI2_NSS
        PB13     ------> SPI2_SCK
        PB14     ------> SPI2_MISO
        PB15     ------> SPI2_MOSI 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        
        GPIO_InitStruct.Pin = GPIO_PIN_14;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        
        /* SPI2 DMA Init */
        /* SPI2_RX Init */
        m_phdma_spi2_rx->Instance                   = DMA1_Channel4;
        m_phdma_spi2_rx->Init.Direction             = DMA_PERIPH_TO_MEMORY;
        m_phdma_spi2_rx->Init.PeriphInc             = DMA_PINC_DISABLE;
        m_phdma_spi2_rx->Init.MemInc                = DMA_MINC_ENABLE;
        m_phdma_spi2_rx->Init.PeriphDataAlignment   = DMA_PDATAALIGN_BYTE;
        m_phdma_spi2_rx->Init.MemDataAlignment      = DMA_MDATAALIGN_BYTE;
        m_phdma_spi2_rx->Init.Mode                  = DMA_NORMAL;
        m_phdma_spi2_rx->Init.Priority              = DMA_PRIORITY_LOW;
        
        if (HAL_DMA_Init(m_phdma_spi2_rx) != HAL_OK)
        {
            //_Error_Handler(__FILE__, __LINE__);
            return HAL_ERROR;
        }
        
        __HAL_LINKDMA(m_phspi_2,hdmarx,*m_phdma_spi2_rx);
        
        /* SPI2_TX Init */
        m_phdma_spi2_tx->Instance                   = DMA1_Channel5;
        m_phdma_spi2_tx->Init.Direction             = DMA_MEMORY_TO_PERIPH;
        m_phdma_spi2_tx->Init.PeriphInc             = DMA_PINC_DISABLE;
        m_phdma_spi2_tx->Init.MemInc                = DMA_MINC_ENABLE;
        m_phdma_spi2_tx->Init.PeriphDataAlignment   = DMA_PDATAALIGN_BYTE;
        m_phdma_spi2_tx->Init.MemDataAlignment      = DMA_MDATAALIGN_BYTE;
        m_phdma_spi2_tx->Init.Mode                  = DMA_NORMAL;
        m_phdma_spi2_tx->Init.Priority              = DMA_PRIORITY_LOW;
        
        if (HAL_DMA_Init(m_phdma_spi2_tx) != HAL_OK)
        {
           // _Error_Handler(__FILE__, __LINE__);
            return HAL_ERROR;
        }
        
        __HAL_LINKDMA(m_phspi_2,hdmatx,*m_phdma_spi2_tx);
    
        m_phspi_2->Init.Mode                = SPI_MODE_MASTER;
        m_phspi_2->Init.Direction           = SPI_DIRECTION_2LINES;
        m_phspi_2->Init.DataSize            = SPI_DATASIZE_8BIT;
        m_phspi_2->Init.CLKPolarity         = SPI_POLARITY_LOW;
        m_phspi_2->Init.CLKPhase            = SPI_PHASE_1EDGE;
        m_phspi_2->Init.NSS                 = SPI_NSS_HARD_OUTPUT;
        m_phspi_2->Init.BaudRatePrescaler   = SPI_BAUDRATEPRESCALER_256;//SPI_BAUDRATEPRESCALER_2;
        m_phspi_2->Init.FirstBit            = SPI_FIRSTBIT_MSB;
        m_phspi_2->Init.TIMode              = SPI_TIMODE_DISABLE;
        m_phspi_2->Init.CRCCalculation      = SPI_CRCCALCULATION_DISABLE;
        m_phspi_2->Init.CRCPolynomial       = 10;
        
        if (HAL_SPI_Init(m_phspi_2) != HAL_OK)
        {
            return HAL_ERROR;
        }    
        
        Peripherals::Interrupt::RegisterInterrupt_Vct_Table(SPI2__IRQHandler,static_cast<Peripherals::Interrupt::IRQn>(SPI2_IRQHandler));
        Peripherals::Interrupt::RegisterInterrupt_Vct_Table(DMA_Ch4_IRQHandler,static_cast<Peripherals::Interrupt::IRQn>(DMA1_Channel4_IRQn),0,0);
        Peripherals::Interrupt::RegisterInterrupt_Vct_Table(DMA_Ch5_IRQHandler,static_cast<Peripherals::Interrupt::IRQn>(DMA1_Channel5_IRQn),0,0); 

    }
    else
    {
        return HAL_ERROR;
    }

    return HAL_OK;
    
}

Status_t SPI_DMA::Tx(uint8_t* pTxBuf, uint16_t TxLen)
{
    Status_t Status = 0;
    
    if((pTxBuf == nullptr) || (TxLen == 0U) )   return HAL_ERROR;    
    
    if(m_spix == SPI1_A4_A5_A6_A7)
    {
        m_pChipSelect_SPI1->Off();
        Status = HAL_SPI_Transmit_DMA(m_phspi_1,pTxBuf, TxLen);
    }
    else if(m_spix == SPI2_B12_B13_B14_B15)
    {
        m_pChipSelect_SPI2->Off();
        Status = HAL_SPI_Transmit_DMA(m_phspi_2,pTxBuf, TxLen);
    }
    
    return Status;
}

Status_t SPI_DMA::Rx(uint8_t* pRxBuf, uint16_t RxLen)
{
    Status_t Status = 0;
    
    if((pRxBuf == nullptr) || (RxLen == 0U) )   return HAL_ERROR;    
    
    if(m_spix == SPI1_A4_A5_A6_A7)
    {
        m_pChipSelect_SPI1->Off();
        Status = HAL_SPI_Receive_DMA(m_phspi_1,pRxBuf, RxLen);
    }
    else if(m_spix == SPI2_B12_B13_B14_B15)
    {
        m_pChipSelect_SPI2->Off();
        Status = HAL_SPI_Receive_DMA(m_phspi_2,pRxBuf, RxLen);
    }
    
    return Status;
}

Status_t SPI_DMA::TxRx(uint8_t* pTxBuf, uint8_t* pRxBuf, uint16_t Len)
{
        Status_t Status = 0;
    
     if((pTxBuf == nullptr) || (pRxBuf == nullptr) || (Len == 0U) )    return HAL_ERROR;
    
    if(m_spix == SPI1_A4_A5_A6_A7)
    {
        m_pChipSelect_SPI1->Off();
        Status = HAL_SPI_TransmitReceive_DMA(m_phspi_1,pTxBuf, pRxBuf, Len);
    }
    else if(m_spix == SPI2_B12_B13_B14_B15)
    {
        m_pChipSelect_SPI2->Off();
        Status = HAL_SPI_TransmitReceive_DMA(m_phspi_2,pTxBuf, pRxBuf, Len);
    }
    
    return Status;
}

void SPI_DMA::SPI1__IRQHandler()
{
   HAL_SPI_IRQHandler(m_phspi_1);
}

void SPI_DMA::SPI2__IRQHandler()
{
   HAL_SPI_IRQHandler(m_phspi_2);
}

/* IRQ handler for SP1 DMA RX */
void SPI_DMA::DMA_Ch2_IRQHandler()
{
   HAL_DMA_IRQHandler(m_phspi_1->hdmarx);
}
/* IRQ handler for SP1 DMA TX */
void SPI_DMA::DMA_Ch3_IRQHandler()
{
   HAL_DMA_IRQHandler(m_phspi_1->hdmatx);
}
/* IRQ handler for SP2 DMA RX */
void SPI_DMA::DMA_Ch4_IRQHandler()
{
   HAL_DMA_IRQHandler(m_phspi_2->hdmarx);
}
/* IRQ handler for SP2 DMA TX */
void SPI_DMA::DMA_Ch5_IRQHandler()
{
   HAL_DMA_IRQHandler(m_phspi_2->hdmatx);
}




}




