/******************
** FILE: UartBase.cpp
**
** DESCRIPTION:
**  Uart base ckass  implementation
**
** CREATED: 1/5/2019, by Amit Chaudhary
******************/
#include "UartBase.h"

namespace Peripherals
{
    
UartBase::UartBase(UartX_t UartX, uint32_t BaudRate , DataLen_t DataLen, StopBits_t stopbits, Parity_t parity ) : m_BaudRate(BaudRate),m_DataLen(DataLen),m_stopbits(stopbits),m_parity(parity)
{
    if(UartX == UART_1)       m_USARTx = USART1;
    else if(UartX == UART_2)  m_USARTx = USART2;
    else if(UartX == UART_3)  m_USARTx = USART3;
}

UartBase::~UartBase()
{
    
}

Status_t UartBase::HwConfig(void* pConfigStruct)
{
    Status_t Status;
    LL_USART_InitTypeDef *USART_InitStruct;
    USART_InitStruct =  reinterpret_cast <LL_USART_InitTypeDef *>(pConfigStruct);
    LL_USART_InitTypeDef L_USART_InitStruct;
    
    if(pConfigStruct == nullptr) return -1;
    
    
    L_USART_InitStruct.BaudRate            = USART_InitStruct->BaudRate;
    L_USART_InitStruct.DataWidth           = USART_InitStruct->DataWidth;
    L_USART_InitStruct.StopBits            = USART_InitStruct->StopBits;
    L_USART_InitStruct.Parity              = USART_InitStruct->Parity;
    L_USART_InitStruct.TransferDirection   = USART_InitStruct->TransferDirection;
    L_USART_InitStruct.HardwareFlowControl = USART_InitStruct->HardwareFlowControl;
#if defined(USART_CR1_OVER8)
    L_USART_InitStruct.OverSampling        = USART_InitStruct->OverSampling;
#endif /* USART_OverSampling_Feature */    
    
    Disable();
    Status =  LL_USART_Init(m_USARTx, &L_USART_InitStruct);
    Enable();
    return Status;
        
}

Status_t UartBase::HwInit()
{    
    Status_t Status;
    GPIO_InitTypeDef GPIO_InitStruct;
    LL_USART_InitTypeDef L_USART_InitStruct;   
    
    L_USART_InitStruct.BaudRate            = m_BaudRate;
    L_USART_InitStruct.DataWidth           = m_DataLen;
    L_USART_InitStruct.StopBits            = m_stopbits;
    L_USART_InitStruct.Parity              = m_parity;
    L_USART_InitStruct.TransferDirection   = LL_USART_DIRECTION_TX_RX;
    L_USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
#if defined(USART_CR1_OVER8)
    L_USART_InitStruct.OverSampling        = LL_USART_OVERSAMPLING_16;
#endif /* USART_OverSampling_Feature */
    
    /* Peripheral clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    Status =  LL_USART_Init(m_USARTx, &L_USART_InitStruct);
    Enable();
    return Status;
}

inline void UartBase::Enable(void)
{
    SET_BIT(m_USARTx->CR1, USART_CR1_UE);
}

inline void UartBase::Disable(void)
{
    CLEAR_BIT(m_USARTx->CR1, USART_CR1_UE);
}

Status_t UartBase::HwDeinit()
{
    return 0;
}

inline UartBase::UART_Status_t UartBase::TxByte(uint8_t abyte, uint32_t Timeout)
{
    /* Wait until tx is busy*/
    if( WaitOnRegisterBitUntilTimeout(m_USARTx->SR,USART_SR_TXE,RESET,Timeout) == 0 )
        return UART_TIMEOUT;
    
    m_USARTx->DR = abyte;
    
    /* Wait until tx is busy*/
    if( WaitOnRegisterBitUntilTimeout(m_USARTx->SR,USART_SR_TC,RESET,Timeout) == 0 )
        return UART_TIMEOUT;
    
    return UART_SUCCESS;
}

inline UartBase::UART_Status_t UartBase::RxByte(uint8_t* pbyte, uint32_t Timeout)
{
    if(pbyte == nullptr) return UART_ERROR;
    
    /* Wait until rx is empty*/
    if( WaitOnRegisterBitUntilTimeout(m_USARTx->SR,USART_SR_RXNE,RESET,0xff) == 0 )
        return UART_TIMEOUT;
    
    *pbyte = m_USARTx->DR;
    
    return UART_SUCCESS;
}

UartBase::UART_Status_t UartBase::Tx(uint8_t* pTxBuf, uint16_t TxLen)
{
    uint32_t failcount = 0;
    uint32_t idx;
    
    for(idx = 0; idx<TxLen; idx++)
    {
        if ( TxByte( pTxBuf[idx], UART_DEFAULT_TIMEOUT) != UART_SUCCESS) 
        {
            failcount++;
            
            if(failcount >= UART_RETRY_LIMIT )
                return UART_ERROR;
        }
        HAL_Delay(1);
        failcount = 0;
    }
    
    return UART_SUCCESS;
}

UartBase::UART_Status_t UartBase::Rx(uint8_t* pRxBuf, uint16_t RxLen)
{
    return UART_SUCCESS;
}


uint32_t UartBase::WaitOnRegisterBitUntilTimeout(uint32_t Registor, uint32_t mask, FlagStatus Status, uint32_t Timeout)
{
   /* Wait until flag is set for a period of "Timeout"*/
   //while( ((Registor & mask) != mask) && (Timeout-- != 0) );
    
   // while( ( READ_BIT(Registor, mask) != mask ) && (--Timeout != 0U) );
    while( (( READ_BIT(Registor, mask) ? SET : RESET) == Status) && (--Timeout != 0U) ) ;
    
   return Timeout;
}


}