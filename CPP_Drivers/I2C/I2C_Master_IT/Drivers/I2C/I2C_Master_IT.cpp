/******************
** FILE: I2C_Master_IT.cpp
**
** DESCRIPTION:
**  I2C class Implementation
**
** CREATED: 8/14/2018, by Amit Chaudhary
******************/

#include "I2C_Master_IT.hpp"
#include "GpioOutput.hpp"
extern Peripherals::GpioOutput A1;

namespace Peripherals
{
#define I2C_TIMEOUT_FLAG          35U         /*!< Timeout 35 ms             */
#define I2C_TIMEOUT_BUSY_FLAG     25U         /*!< Timeout 25 ms             */

volatile uint32_t  I2C_Master_IT::m_TxDone = DONE;
volatile uint32_t  I2C_Master_IT::m_RxDone = DONE;

I2C_HandleTypeDef       I2C_Master_IT::m_hi2c;

I2C_Master_IT::Callback_t              I2C_Master_IT::m_RxCallback = nullptr;
I2C_Master_IT::Callback_t              I2C_Master_IT::m_TxCallback = nullptr;

I2C_Master_IT::I2C_Master_IT(I2CPort_t I2CPort, I2CBaudRate_t I2CBaudRate) : m_I2CPort(I2CPort)
{
    if( (I2CPort == I2C1_SCL_B6_SDA_B7) || (I2CPort == I2C1_SCL_B8_SDA_B9) )
    {
        m_hi2c.Instance = I2C1;
    }
    else if(I2CPort == I2C2_SCL_B11_SDA_B12)
    {
        m_hi2c.Instance = I2C2; 
    }
    else
    {
        m_hi2c.Instance = I2C1;
    }
    if(I2CBaudRate == BAUD_100K )
    {
        m_hi2c.Init.ClockSpeed = 100000;
    }
    else if(I2CBaudRate == BAUD_400K)
    {
        m_hi2c.Init.ClockSpeed = 400000;
    }
    else
    {
        m_hi2c.Init.ClockSpeed = 100000;
    }
        
}

Status_t I2C_Master_IT::HwInit()
{    
    GPIO_InitTypeDef GPIO_InitStruct;
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    if(m_hi2c.Instance==I2C1)
    {  
         __HAL_RCC_I2C1_CLK_ENABLE();
        if(m_I2CPort == I2C1_SCL_B6_SDA_B7)
        {
            /**I2C1 GPIO Configuration    
            PB6     ------> I2C1_SCL
            PB7     ------> I2C1_SDA 
            */
            GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
            GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
            HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
            
        }
        else if(m_I2CPort == I2C1_SCL_B8_SDA_B9)
        {
            /**I2C1 GPIO Configuration    
            PB8     ------> I2C1_SCL
            PB9     ------> I2C1_SDA 
            */
            GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
            GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
            HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);           
        }        
        /* Peripheral clock enable */
       
    }
    else if(m_hi2c.Instance==I2C2)
    {
        /**I2C1 GPIO Configuration    
        PB10     ------> I2C1_SCL
        PB11     ------> I2C1_SDA 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);              
        /* Peripheral clock enable */
        __HAL_RCC_I2C2_CLK_ENABLE();        
    }
    
    m_hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
    m_hi2c.Init.OwnAddress1 = 0;
    m_hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    m_hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    m_hi2c.Init.OwnAddress2 = 0;
    m_hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    m_hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&m_hi2c) != HAL_OK)
    {
        return -1;
    }
    Peripherals::Interrupt::RegisterInterrupt_Vct_Table(EventISR,static_cast<Peripherals::Interrupt::IRQn>(I2C1_EV_IRQHandler));
    Peripherals::Interrupt::RegisterInterrupt_Vct_Table(ErrorISR,static_cast<Peripherals::Interrupt::IRQn>(I2C1_ER_IRQHandler));
    return 0;
}
  
Status_t I2C_Master_IT::Send ( uint16_t DevAddress, uint8_t *pTxBuf, uint16_t Len)
{
    return HAL_I2C_Master_Transmit_IT(&m_hi2c, DevAddress, pTxBuf, Len);
}

Status_t I2C_Master_IT::Send (uint16_t DevAddress, uint8_t *pTxBuf, uint16_t Len, uint32_t XferOptions )
{
    return HAL_I2C_Master_Sequential_Transmit_IT(&m_hi2c, DevAddress, pTxBuf, Len, XferOptions);
}

Status_t I2C_Master_IT::Read (uint16_t DevAddress, uint8_t *pRxBuf, uint16_t Len)
{
    return HAL_I2C_Master_Receive_IT(&m_hi2c, DevAddress, pRxBuf, Len);
}

Status_t I2C_Master_IT::Read (uint16_t DevAddress, uint8_t *pRxBuf, uint16_t Len, uint32_t XferOptions)
{
    return HAL_I2C_Master_Sequential_Receive_IT(&m_hi2c, DevAddress, pRxBuf, Len, XferOptions);
}

void I2C_Master_IT::EventISR(void)
{
    HAL_I2C_EV_IRQHandler(&Peripherals::I2C_Master_IT::m_hi2c);
}  
void I2C_Master_IT::ErrorISR(void)
{
    HAL_I2C_ER_IRQHandler(&Peripherals::I2C_Master_IT::m_hi2c);
} 

Status_t I2C_Master_IT::Reset ()
{
    m_hi2c.Instance->CR1 = 1<<15;
    
    m_hi2c.Instance->CR1 &= ~(1<<15); 
    
    HwInit();
        
    return HAL_OK;    
}

Status_t I2C_Master_IT::Scan(uint16_t *DevAddress, uint16_t len )
{
    uint16_t idx = 0;
   if( DevAddress && (len>0))
   {
    for(uint16_t i = 0; i< 256; i++)
    {
        if (HAL_OK == HAL_I2C_IsDeviceReady(&m_hi2c, i<<1, 2, 2))
            DevAddress[idx++ % len] = i;
    }  
   return HAL_OK;
   }
   return HAL_ERROR;
  
}

#define DELAY  1100 + 400
#define DELAY1 1500 + 400
#define DELAY2 1850 + 400


Status_t I2C_Master_IT::Xfer(uint16_t DevAddress, uint8_t *pTxBuf, uint16_t TxLen, uint8_t *pRxBuf, uint16_t RxLen)
{  
    if( (pTxBuf == nullptr) && (TxLen == 0U) && (pRxBuf == nullptr) && (RxLen == 0U) )
    {
        return HAL_ERROR;
    }    
    else if( ((pTxBuf == nullptr) && (TxLen == 0U) ) && ( (pRxBuf != nullptr) && (RxLen != 0U) ) )
    {
       // while(m_TxDone != DONE);
        
        if( HAL_I2C_Master_Receive_IT(&m_hi2c, DevAddress, pRxBuf, RxLen) == HAL_OK )
        {
            //HAL_Delay(1); 
            return HAL_OK;
        }
        else
        {
            return HAL_ERROR;
        }
    }
    else if( ((pTxBuf != nullptr) && (TxLen != 0U) ) && ( (pRxBuf == nullptr) && (RxLen == 0U) ) )
    {
        //while(m_RxDone != DONE);
        //A1.ToggleOutput();
        if( HAL_I2C_Master_Transmit_IT(&m_hi2c, DevAddress, pTxBuf, TxLen) == HAL_OK )
        {
            //HAL_Delay(1); 
            for(volatile int i = 0; i<DELAY2;i++); 
            return HAL_OK;
        }
        else
        {
            return HAL_ERROR;
        }
    }
    else if( ((pTxBuf != nullptr) && (TxLen != 0U) ) && ( (pRxBuf != nullptr) && (RxLen != 0U) ) )
    {

        // Transmit
        //A1.ToggleOutput();
        if( HAL_I2C_Master_Sequential_Transmit_IT(&m_hi2c, DevAddress, pTxBuf, TxLen, I2C_FIRST_FRAME) == HAL_OK )
        {
            m_TxDone = BUSY;
            //HAL_Delay(1); 
            for(volatile int i = 0; i<DELAY;i++);            
        }

        
        
        // Receive   
        if( HAL_I2C_Master_Sequential_Receive_IT(&m_hi2c, DevAddress, pRxBuf, RxLen, I2C_LAST_FRAME) == HAL_OK )
        {
            m_RxDone = BUSY;
           // HAL_Delay(1); 
            for(volatile int i = 0; i<DELAY1;i++);
        }

    }
    
    return HAL_ERROR;
}



}

extern "C"
{

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
      if (Peripherals::I2C_Master_IT::m_RxCallback != nullptr)
            Peripherals::I2C_Master_IT::m_RxCallback();
}


void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
      if (Peripherals::I2C_Master_IT::m_TxCallback != nullptr)
            Peripherals::I2C_Master_IT::m_TxCallback();
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
    if((Peripherals::I2C_Master_IT::m_hi2c.ErrorCode & 4) == 4)
    {
        Peripherals::I2C_Master_IT::m_TxDone =  Peripherals::I2C_Master_IT::DONE;
        Peripherals::I2C_Master_IT::m_RxDone =  Peripherals::I2C_Master_IT::DONE;
    }
    
}


}





