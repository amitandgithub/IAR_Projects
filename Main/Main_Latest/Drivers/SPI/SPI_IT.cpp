/******************
** FILE: SPI.cpp
**
** DESCRIPTION:
**  SPI implementation in polling mode
**
** CREATED: 9/2/2018, by Amit Chaudhary
******************/

#include "SPI_IT.h"

namespace Peripherals
{
    
SPI_HandleTypeDef SPI_IT::m_hspi;    
SPI_IT::Callback_t SPI_IT::TxDoneCallback;
SPI_IT::Callback_t SPI_IT::RxDoneCallback;
SPI_IT::Callback_t SPI_IT::TxRxDoneCallback;
SPI_IT::Callback_t SPI_IT::TxHalfDoneCallback;
SPI_IT::Callback_t SPI_IT::RxHalfDoneCallback;
SPI_IT::Callback_t SPI_IT::TxRxHalfDoneCallback;

SPI_IT::SPI_IT (SPIx_t spix , uint32_t hz) : m_hz(hz), m_spix(spix)
{
   m_pDefault_CS = nullptr;  
}



Status_t SPI_IT::HwInit ()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    
    /* SPI1 parameter configuration*/
    if(m_spix == SPI1_A4_A5_A6_A7)
    {
        static Peripherals::GpioOutput CS(GPIOA,GPIO_PIN_4);
        CS.HwInit();
        m_pDefault_CS = &CS;
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

        Peripherals::Interrupt::RegisterInterrupt_Vct_Table(IRQHandler,static_cast<Peripherals::Interrupt::IRQn>(SPI1_IRQHandler));
        
    }
    else if(m_spix == SPI1_A15_B3_B4_B5)
    {
        static Peripherals::GpioOutput CS(GPIOA,GPIO_PIN_15);
        CS.HwInit();
        m_pDefault_CS = &CS;
        m_hspi.Instance = SPI1;
        Peripherals::Interrupt::RegisterInterrupt_Vct_Table(IRQHandler,static_cast<Peripherals::Interrupt::IRQn>(SPI1_IRQHandler));
    }
    else if(m_spix == SPI2_B12_B13_B14_B15)
    {
        static Peripherals::GpioOutput CS(GPIOB,GPIO_PIN_12);
        CS.HwInit();
        m_pDefault_CS = &CS;
        m_hspi.Instance = SPI2;
        Peripherals::Interrupt::RegisterInterrupt_Vct_Table(IRQHandler,static_cast<Peripherals::Interrupt::IRQn>(SPI2_IRQHandler));
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

Status_t SPI_IT::Send(uint8_t* pTxBuf, uint16_t TxLen, GpioOutput* CS)
{
    Status_t Status = 0;
    
    if((pTxBuf == nullptr) || (TxLen == 0U) )   return HAL_ERROR;
    
    if (CS == nullptr)  CS = m_pDefault_CS; 
    
    CS->Off();
    Status = HAL_SPI_Transmit_IT(&m_hspi,pTxBuf, TxLen);
    CS->On();
    
    return Status;
}

Status_t SPI_IT::Read(uint8_t* pRxBuf, uint16_t RxLen, GpioOutput* CS)
{
    Status_t Status = 0;
    
    if((pRxBuf == nullptr) || (RxLen == 0U) )   return HAL_ERROR;
    
    if (CS == nullptr)  CS = m_pDefault_CS; 
    
    CS->Off();
    Status = HAL_SPI_Receive_IT(&m_hspi,pRxBuf, RxLen);
    CS->On();
    
    return Status;
}

Status_t SPI_IT::Xfer(uint8_t* pTxBuf, uint8_t* pRxBuf, uint16_t Len, GpioOutput* CS)
{
    Status_t Status = 0;
    
    if((pTxBuf == nullptr) || (pRxBuf == nullptr) || (Len == 0U) )    return HAL_ERROR;
    
    if (CS == nullptr)   CS = m_pDefault_CS; 
    
    CS->Off();
    Status = HAL_SPI_TransmitReceive_IT(&m_hspi,pTxBuf, pRxBuf, Len);
    CS->On();
    
    return Status;
}

void SPI_IT::IRQHandler()
{
   HAL_SPI_IRQHandler(&m_hspi);
}



}


extern "C"
{
 
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
      if(Peripherals::SPI_IT::TxDoneCallback != nullptr)
        Peripherals::SPI_IT::TxDoneCallback();
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
      if(Peripherals::SPI_IT::RxDoneCallback != nullptr)
        Peripherals::SPI_IT::RxDoneCallback();    
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
      if(Peripherals::SPI_IT::TxRxDoneCallback != nullptr)
        Peripherals::SPI_IT::TxRxDoneCallback();    
}

void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
      if(Peripherals::SPI_IT::TxHalfDoneCallback != nullptr)
        Peripherals::SPI_IT::TxHalfDoneCallback();    
    
}

void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
      if(Peripherals::SPI_IT::RxHalfDoneCallback != nullptr)
        Peripherals::SPI_IT::RxHalfDoneCallback();    
    
}

void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
      if(Peripherals::SPI_IT::TxRxHalfDoneCallback != nullptr)
        Peripherals::SPI_IT::TxRxHalfDoneCallback();    
}

}












