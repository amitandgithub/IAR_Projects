/******************
** CLASS: UartBase
**
** DESCRIPTION:
**  Basic implementation of uart
**
** CREATED: 1/5/2019, by Amit Chaudhary
**
** FILE: UartBase.h
**
******************/
#ifndef UartBase_h
#define UartBase_h

#include"Peripheral.hpp"
#include"stm32f1xx_ll_usart.h"

namespace Peripherals
{
    
class UartBase: public Peripheral
{
public:
    static const uint32_t UART_DEFAULT_TIMEOUT = 0xFF;
    static const uint32_t UART_RETRY_LIMIT = 10;
    
    
    typedef enum
    {
        UART_SUCCESS = 0,
        UART_TIMEOUT,
        UART_ERROR
    }UART_Status_t;
    
    typedef enum
    {
        UART_1 = 1,
        UART_2 = 2,
        UART_3 = 3        
    }UartX_t;
    
    typedef enum
    {
        UART_DATALENGTH_8B = 0x00000000U,
        UART_WORDLENGTH_9B = ((uint32_t)USART_CR1_M)        
    }DataLen_t;  
    
    typedef enum
    {
        UART_STOPBITS_1 = 0x00000000U,
        UART_STOPBITS_2 = ((uint32_t)USART_CR2_STOP_1)       
    }StopBits_t; 
    
    typedef enum
    {
        UART_PARITY_NONE = 0x00000000U,
        UART_PARITY_EVEN = ((uint32_t)USART_CR1_PCE),
        UART_PARITY_ODD = ((uint32_t)(USART_CR1_PCE | USART_CR1_PS))
    }Parity_t; 
    
  UartBase(UartX_t UartX, uint32_t BaudRate = 9600, DataLen_t DataLen = UART_DATALENGTH_8B, StopBits_t stopbits = UART_STOPBITS_1, Parity_t parity = UART_PARITY_NONE );
  
  ~UartBase();
  
    virtual       Status_t       HwInit             ();
    
    virtual       Status_t       HwDeinit           ();
    
    virtual       Status_t       HwConfig           (void* pConfigStruct = nullptr);
    
    virtual       UART_Status_t       TxByte             (uint8_t abyte, uint32_t Timeout);
                  
    virtual       UART_Status_t       RxByte             (uint8_t* pbyte, uint32_t Timeout);
    
    virtual       UART_Status_t       Tx                 (uint8_t* pTxBuf, uint16_t TxLen);
                  
    virtual       UART_Status_t       Rx                 (uint8_t* pRxBuf, uint16_t RxLen);
    
                  void                Enable             (); 
                  
                  void                Disable            ();
    
                  uint32_t       WaitOnRegisterBitUntilTimeout            (uint32_t Registor, uint32_t mask, FlagStatus Status, uint32_t Timeout);
                             
    
private:
    USART_TypeDef*  m_USARTx;
    uint32_t        m_BaudRate;
    DataLen_t       m_DataLen;
    StopBits_t      m_stopbits;
    Parity_t        m_parity;
  
};
#endif //UartBase_h

}