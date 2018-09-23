/******************
** FILE: SPI.cpp
**
** DESCRIPTION:
**  SPI implementation in Interrupt mode
**
** CREATED: 9/2/2018, by Amit Chaudhary
******************/

#include "SPI_IT.h"

namespace Peripherals
{

SPI_IT::SPI_IT (SPIx_t spix, GpioOutput* pCS, HZ_t hz,SPI_HandleTypeDef* phspi_x) : m_hz(hz), m_spix(spix)
{
    if((m_spix == SPI1_A4_A5_A6_A7) || (m_spix == SPI1_A15_B3_B4_B5) )
     {
        m_pChipSelect_SPI1 = pCS;
        
       if(phspi_x == nullptr) m_phspi_1 = &m_hspi_1;
        
        if( (m_pChipSelect_SPI1 == nullptr)  )
        {
            while(1); // Fatal Error
        }
        
     }
     else if(m_spix == SPI2_B12_B13_B14_B15)
     {
        m_pChipSelect_SPI2 = pCS;
        
        if(phspi_x == nullptr) m_phspi_2 = &m_hspi_2;
        
        if( (m_pChipSelect_SPI2 == nullptr) )
        {
            while(1); // Fatal Error
        }
     }
     else
     {
         while(1); // Fatal error
     }
}




Status_t SPI_IT::HwInit ()
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
        
    }
    else if(m_spix == SPI1_A15_B3_B4_B5)
    {   
        m_pChipSelect_SPI1->HwInit(); 
       
        m_phspi_1->Instance = SPI1;
        
        __HAL_RCC_GPIOA_CLK_ENABLE();
        
        /* Peripheral clock enable */
        __HAL_RCC_SPI1_CLK_ENABLE();
        
        
        /**SPI1 GPIO Configuration    
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
    }
    else if(m_spix == SPI1_A4_A5_A6_A7)
    {   
        m_pChipSelect_SPI2->HwInit(); 
       
        m_phspi_2->Instance = SPI1;
        
        __HAL_RCC_GPIOA_CLK_ENABLE();
        
        /* Peripheral clock enable */
        __HAL_RCC_SPI2_CLK_ENABLE();
        
        
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
        
    }
    else
    {
        return HAL_ERROR;
    }

    return HAL_OK;
    
}

Status_t SPI_IT::Tx(uint8_t* pTxBuf, uint16_t TxLen)
{
    
    Status_t Status = 0;
    
    if((pTxBuf == nullptr) || (TxLen == 0U) )   return HAL_ERROR;    
    
    if(m_spix == SPI1_A4_A5_A6_A7)
    {
        m_pChipSelect_SPI1->Off();
        Status = HAL_SPI_Transmit_IT(m_phspi_1,pTxBuf, TxLen);
    }
    else if(m_spix == SPI2_B12_B13_B14_B15)
    {
        m_pChipSelect_SPI2->Off();
        Status = HAL_SPI_Transmit_IT(m_phspi_2,pTxBuf, TxLen);
    }
    
    return Status;
    
}

Status_t SPI_IT::Rx(uint8_t* pRxBuf, uint16_t RxLen)
{
    Status_t Status = 0;
    
    if((pRxBuf == nullptr) || (RxLen == 0U) )   return HAL_ERROR;  
    
    if(m_spix == SPI1_A4_A5_A6_A7)
    {
        m_pChipSelect_SPI1->Off();
        Status = HAL_SPI_Receive_IT(m_phspi_1,pRxBuf, RxLen);
    }
    else if(m_spix == SPI2_B12_B13_B14_B15)
    {
        m_pChipSelect_SPI2->Off();
        Status = HAL_SPI_Receive_IT(m_phspi_2,pRxBuf, RxLen);
    }
    return Status;
}

Status_t SPI_IT::TxRx(uint8_t* pTxBuf, uint8_t* pRxBuf, uint16_t Len)
{
    Status_t Status = 0;
    
    if((pTxBuf == nullptr) || (pRxBuf == nullptr) || (Len == 0U) )    return HAL_ERROR;
    
    if(m_spix == SPI1_A4_A5_A6_A7)
    {
        m_pChipSelect_SPI1->Off();
        Status = HAL_SPI_TransmitReceive_IT(m_phspi_1,pTxBuf, pRxBuf, Len);
    }
    else if(m_spix == SPI2_B12_B13_B14_B15)
    {
        m_pChipSelect_SPI2->Off();
        Status = HAL_SPI_TransmitReceive_IT(m_phspi_2,pTxBuf, pRxBuf, Len);
    }
    return Status;
}

}

