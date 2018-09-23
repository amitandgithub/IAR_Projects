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
    Status_t Status;
    SPI_HandleTypeDef hspi;
    
    hspi.Init.Mode                = SPI_MODE_MASTER;
    hspi.Init.Direction           = SPI_DIRECTION_2LINES;
    hspi.Init.DataSize            = SPI_DATASIZE_8BIT;
    hspi.Init.CLKPolarity         = SPI_POLARITY_LOW;
    hspi.Init.CLKPhase            = SPI_PHASE_1EDGE;
    hspi.Init.NSS                 = SPI_NSS_HARD_OUTPUT;
    hspi.Init.BaudRatePrescaler   = SPI_BAUDRATEPRESCALER_256;//SPI_BAUDRATEPRESCALER_2;
    hspi.Init.FirstBit            = SPI_FIRSTBIT_MSB;
    hspi.Init.TIMode              = SPI_TIMODE_DISABLE;
    hspi.Init.CRCCalculation      = SPI_CRCCALCULATION_DISABLE;
    hspi.Init.CRCPolynomial       = 10;
        
    Status = SPI_Base::SPI_Init( m_spix, m_hz,&hspi );
    
    if(Status != HAL_OK)
        return HAL_ERROR;
    
    if(m_spix == SPI1_A4_A5_A6_A7)
    { 
        Peripherals::Interrupt::RegisterInterrupt_Vct_Table(SPI1__IRQHandler,static_cast<Peripherals::Interrupt::IRQn>(SPI1_IRQHandler));
    }
    else if(m_spix == SPI1_A15_B3_B4_B5)
    {
        Peripherals::Interrupt::RegisterInterrupt_Vct_Table(SPI1__IRQHandler,static_cast<Peripherals::Interrupt::IRQn>(SPI1_IRQHandler));
    }
    else if(m_spix == SPI1_A15_B3_B4_B5)
    {
        Peripherals::Interrupt::RegisterInterrupt_Vct_Table(SPI2__IRQHandler,static_cast<Peripherals::Interrupt::IRQn>(SPI2_IRQHandler));
    }
    else
    {
        while(1); // Fatal Error
    }
    return Status;
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

