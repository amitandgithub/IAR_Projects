/*
 * I2CDriver.cpp
 *
 *  Created on: 16-Dec-2017
 *      Author: Amit Chaudhary
 */

#include <I2CDriver.hpp>
#include "stm32f10x_i2c.h"

namespace Bsp {
  
I2CDriver::I2CDriver(I2CInstance_t I2CInstance, I2CIsr_t aI2CIsr, I2CMode_t aI2CMode, I2CBaudRate_t aI2CBaudRate )
{
	m_I2CInstance = I2CInstance;
	m_I2CIsr      = aI2CIsr;
	m_I2CMode     = aI2CMode;
	m_I2CBaudRate = aI2CBaudRate;
	m_I2Cx        = nullptr;

}

uint8_t I2CDriver::ScanBus(uint8_t* pResult, uint8_t Len)
{
    uint8_t index=0;
    for(volatile uint8_t i = 0; i<0xff;i++)
    {
      if( ScanDevice(i) == 0 )
      {
        pResult[(index++)%Len] = i;
      }
      HwInit();
    }
    return index;
}


I2CDriver::~I2CDriver()
{

}
uint8_t I2CDriver::ScanDevice(uint8_t SlaveAddress)
{
   vu32 Timeout = 0;

  Timed(I2C_GetFlagStatus(m_I2Cx , I2C_FLAG_BUSY));
  // Intiate Start Sequence
  I2C_GenerateSTART(m_I2Cx , ENABLE);
  Timed (! I2C_CheckEvent(m_I2Cx , I2C_EVENT_MASTER_MODE_SELECT));
  // Send Address EV5
  I2C_Send7bitAddress(m_I2Cx , SlaveAddress ,	I2C_Direction_Transmitter);
  Timed (! I2C_CheckEvent(m_I2Cx , I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));  
  return 0;
 errReturn:
  return 1;
}

bool I2CDriver::HwInit()
{
	I2C_InitTypeDef I2cConfig;
	GPIO_InitTypeDef GPIO_InitStructure;
	ClockManager* pClockManager  = GetClockManager();
        
	if( m_I2CInstance == I2C1_B6_B7)
	{
            m_I2Cx = I2C1;
            pClockManager->PeripheralClockEnable(ClockManager::APB1Periph_I2C1);
            pClockManager->PeripheralClockEnable(ClockManager::APB2Periph_GPIOB);

            /* Enable I2C1 clock */
            RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );

            /* Enable GPIOB clock */
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );

            /* Configure I2C SCL and SDA as Alternate Output Push Pull configuration */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
            GPIO_Init( GPIOB, &GPIO_InitStructure );
            
            //GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);

            /* I2C1 Reset */
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1 , ENABLE);
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1 , DISABLE);

            I2cConfig.I2C_Ack = I2C_Ack_Enable;
            I2cConfig.I2C_Mode = I2C_Mode_I2C;
            I2cConfig.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
            I2cConfig.I2C_DutyCycle = I2C_DutyCycle_2;
            I2cConfig.I2C_ClockSpeed = m_I2CBaudRate;
            I2cConfig.I2C_OwnAddress1 = 0x50;
	}
	else if( m_I2CInstance == I2C1_B8_B9)
	{
		m_I2Cx = I2C1;
                pClockManager->PeripheralClockEnable(ClockManager::APB1Periph_I2C1);
                pClockManager->PeripheralClockEnable(ClockManager::APB2Periph_GPIOB);

                /* Enable I2C1 clock */
                RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );

                /* Enable GPIOB clock */
                RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );

                /* Configure I2C SCL and SDA as Alternate Output Push Pull configuration */
                GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
                GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
                GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
                GPIO_Init( GPIOB, &GPIO_InitStructure );
                
                //GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);

                /* I2C1 Reset */
                RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1 , ENABLE);
                RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1 , DISABLE);

                I2cConfig.I2C_Ack = I2C_Ack_Enable;
                I2cConfig.I2C_Mode = I2C_Mode_I2C;
                I2cConfig.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
                I2cConfig.I2C_DutyCycle = I2C_DutyCycle_2;
                I2cConfig.I2C_ClockSpeed = m_I2CBaudRate;
                I2cConfig.I2C_OwnAddress1 = 0x50;
	}
        else if( m_I2CInstance == I2C2_B11_B12)
	{
		m_I2Cx = I2C2;
                pClockManager->PeripheralClockEnable(ClockManager::APB1Periph_I2C2);
                pClockManager->PeripheralClockEnable(ClockManager::APB2Periph_GPIOB);

                /* Enable I2C2 clock */
                RCC_APB2PeriphClockCmd( RCC_APB1Periph_I2C2, ENABLE );

                /* Enable GPIOB clock */
                RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );

                /* Configure I2C SCL and SDA as Alternate Output Push Pull configuration */
                GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
                GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
                GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
                GPIO_Init( GPIOB, &GPIO_InitStructure );
                
               // GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);

                /* I2C2 Reset */
                RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2 , ENABLE);
                RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2 , DISABLE);

                I2cConfig.I2C_Ack = I2C_Ack_Enable;
                I2cConfig.I2C_Mode = I2C_Mode_I2C;
                I2cConfig.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
                I2cConfig.I2C_DutyCycle = I2C_DutyCycle_2;
                I2cConfig.I2C_ClockSpeed = m_I2CBaudRate;
                I2cConfig.I2C_OwnAddress1 = 0x50;
	}


	I2C_Init(m_I2Cx,&I2cConfig);
	I2C_Cmd(m_I2Cx,ENABLE);
      return 1;

}

I2CDriver::I2C_STATUS I2CDriver::Send(u8 SlaveAddress, u8* pBuf, u32 Bytes)
{
	volatile uint32_t Timeout = 0;
	if (Bytes)
	{
		Timed(I2C_GetFlagStatus(m_I2Cx , I2C_FLAG_BUSY));

		// Initiate Start Sequence
		I2C_GenerateSTART(m_I2Cx , ENABLE);

		Timed (! I2C_CheckEvent(m_I2Cx , I2C_EVENT_MASTER_MODE_SELECT));

		// Send Address EV5
		I2C_Send7bitAddress(m_I2Cx , SlaveAddress ,	I2C_Direction_Transmitter);

		Timed (! I2C_CheckEvent(m_I2Cx , I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

		// EV6 Write first byte EV8_1
		I2C_SendData(m_I2Cx , *pBuf ++);

		while (--Bytes)
		{
			// wait on BTF
			Timed (! I2C_GetFlagStatus(m_I2Cx , I2C_FLAG_BTF));
			I2C_SendData(m_I2Cx , *pBuf ++);
		}

		Timed (! I2C_GetFlagStatus(m_I2Cx , I2C_FLAG_BTF));
		I2C_GenerateSTOP(m_I2Cx , ENABLE);
		Timed(I2C_GetFlagStatus(m_I2Cx , I2C_FLAG_STOPF));
	}
	return I2C_ERROR_NONE;
	errReturn:
        HwInit();
	return I2C_ERROR_BUSY_TRANSMITTING;
}

I2CDriver::I2C_STATUS I2CDriver::Receive(u8 SlaveAddress, u8* pBuf, u32 Bytes)
{
	 vu32 Timeout = 0;
	  if (!Bytes)
	    return I2C_ERROR_NONE;

		// Wait for idle I2C interface

	  Timed(I2C_GetFlagStatus(m_I2Cx, I2C_FLAG_BUSY));

	  // Enable Acknowledgement, clear POS flag

	  I2C_AcknowledgeConfig(m_I2Cx, ENABLE);
	  I2C_PECPositionConfig(m_I2Cx, I2C_PECPosition_Current);

	  // Intiate Start Sequence (wait for EV5

	  I2C_GenerateSTART(m_I2Cx, ENABLE);
	  Timed(!I2C_CheckEvent(m_I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

	  // Send Address

	  I2C_Send7bitAddress(m_I2Cx, SlaveAddress, I2C_Direction_Receiver);

	  // EV6

	  Timed(!I2C_GetFlagStatus(m_I2Cx, I2C_FLAG_ADDR));

	  if (Bytes == 1)
	    {

	      // Clear Ack bit

	      I2C_AcknowledgeConfig(m_I2Cx, DISABLE);

	      // EV6_1 -- must be atomic -- Clear ADDR, generate STOP

	      __disable_irq();
	      (void) m_I2Cx->SR2;
	      I2C_GenerateSTOP(m_I2Cx,ENABLE);
	      __enable_irq();

	      // Receive data   EV7

	      Timed(!I2C_GetFlagStatus(m_I2Cx, I2C_FLAG_RXNE));
	      *pBuf++ = I2C_ReceiveData(m_I2Cx);

	    }
	  else if (Bytes == 2)
	    {
	      // Set POS flag

	      I2C_PECPositionConfig(m_I2Cx, I2C_PECPosition_Next);

	      // EV6_1 -- must be atomic and in this order

	      __disable_irq();
	      (void) m_I2Cx->SR2;                           // Clear ADDR flag
	      I2C_AcknowledgeConfig(m_I2Cx, DISABLE);       // Clear Ack bit
	      __enable_irq();

	      // EV7_3  -- Wait for BTF, program stop, read data twice

	      Timed(!I2C_GetFlagStatus(m_I2Cx, I2C_FLAG_BTF));

	      __disable_irq();
	      I2C_GenerateSTOP(m_I2Cx,ENABLE);
	      *pBuf++ = m_I2Cx->DR;
	      __enable_irq();

	      *pBuf++ = m_I2Cx->DR;

	    }
	  else
	    {
	      (void) m_I2Cx->SR2;                           // Clear ADDR flag
	      while (Bytes-- != 3)
		{
		  // EV7 -- cannot guarantee 1 transfer completion time, wait for BTF
	    //        instead of RXNE

		  Timed(!I2C_GetFlagStatus(m_I2Cx, I2C_FLAG_BTF));
		  *pBuf++ = I2C_ReceiveData(m_I2Cx);
		}

	      Timed(!I2C_GetFlagStatus(m_I2Cx, I2C_FLAG_BTF));

	      // EV7_2 -- Figure 1 has an error, doesn't read N-2 !

	      I2C_AcknowledgeConfig(m_I2Cx, DISABLE);           // clear ack bit

	      __disable_irq();
	      *pBuf++ = I2C_ReceiveData(m_I2Cx);             // receive byte N-2
	      I2C_GenerateSTOP(m_I2Cx,ENABLE);                  // program stop
	      __enable_irq();

	      *pBuf++ = I2C_ReceiveData(m_I2Cx);             // receive byte N-1

	      // wait for byte N

	      Timed(!I2C_CheckEvent(m_I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
	      *pBuf++ = I2C_ReceiveData(m_I2Cx);

	      Bytes = 0;

	    }

	  // Wait for stop

	  Timed(I2C_GetFlagStatus(m_I2Cx, I2C_FLAG_STOPF));
	  return I2C_ERROR_BUSY_TRANSMITTING;

	 errReturn:
         HwInit();
	 return I2C_ERROR_NONE;
}

} /* namespace Bsp */
