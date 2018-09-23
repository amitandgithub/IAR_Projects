/******************
** FILE: SPI.cpp
**
** DESCRIPTION:
**  SPI implementation in polling mode
**
** CREATED: 9/2/2018, by Amit Chaudhary
******************/

#include "SPI_Poll.h"

namespace Peripherals
{
  


SPI_Poll::SPI_Poll (SPIx_t spix , GpioOutput* CS, uint32_t hz) : m_hz(hz), m_spix(spix),m_pCS(CS)
{

}



Status_t SPI_Poll::HwInit ()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    
    /* SPI1 parameter configuration*/
    if(m_spix == SPI1_A4_A5_A6_A7)
    {
        m_pCS->HwInit();

        m_hspi.Instance = SPI1;
        
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
        
    }
    else if(m_spix == SPI1_A15_B3_B4_B5)
    {
        m_pCS->HwInit();
        m_hspi.Instance = SPI1;
    }
    else if(m_spix == SPI2_B12_B13_B14_B15)
    {
        m_pCS->HwInit();
        m_hspi.Instance = SPI2;
    }
    else
    {
        return HAL_ERROR;
    }
    
    m_hspi.Init.Mode                = SPI_MODE_MASTER;
    m_hspi.Init.Direction           = SPI_DIRECTION_2LINES;
    m_hspi.Init.DataSize            = SPI_DATASIZE_8BIT;
    m_hspi.Init.CLKPolarity         = SPI_POLARITY_LOW;
    m_hspi.Init.CLKPhase            = SPI_PHASE_1EDGE;
    m_hspi.Init.NSS                 = SPI_NSS_HARD_OUTPUT;
    m_hspi.Init.BaudRatePrescaler   = SPI_BAUDRATEPRESCALER_256;//SPI_BAUDRATEPRESCALER_2;
    m_hspi.Init.FirstBit            = SPI_FIRSTBIT_MSB;
    m_hspi.Init.TIMode              = SPI_TIMODE_DISABLE;
    m_hspi.Init.CRCCalculation      = SPI_CRCCALCULATION_DISABLE;
    m_hspi.Init.CRCPolynomial       = 10;
    
    if (HAL_SPI_Init(&m_hspi) != HAL_OK)
    {
        return HAL_ERROR;
    } 
    
    return HAL_OK;
    
}

Status_t SPI_Poll::Tx(uint8_t* pTxBuf, uint16_t TxLen)
{
    Status_t Status = 0;
    
    if((pTxBuf == nullptr) || (TxLen == 0U) )   return HAL_ERROR;
    
    m_pCS->Off();
    Status = HAL_SPI_Transmit(&m_hspi,pTxBuf, TxLen, SPI_POLL_DELAY);
    m_pCS->On();
    
    return Status;
}

Status_t SPI_Poll::Rx(uint8_t* pRxBuf, uint16_t RxLen)
{
    Status_t Status = 0;
    
    if((pRxBuf == nullptr) || (RxLen == 0U) )   return HAL_ERROR;
    
    m_pCS->Off();
    Status = HAL_SPI_Receive(&m_hspi,pRxBuf, RxLen, SPI_POLL_DELAY);
    m_pCS->On();
    
    return Status;
}

Status_t SPI_Poll::TxRx(uint8_t* pTxBuf, uint8_t* pRxBuf, uint16_t Len)
{
    Status_t Status = 0;
    
    if((pTxBuf == nullptr) || (pRxBuf == nullptr) || (Len == 0U) )    return HAL_ERROR;
    
    m_pCS->Off();
    Status = HAL_SPI_TransmitReceive(&m_hspi,pTxBuf, pRxBuf, Len, SPI_POLL_DELAY);
    m_pCS->On();
    
    return Status;
}











}