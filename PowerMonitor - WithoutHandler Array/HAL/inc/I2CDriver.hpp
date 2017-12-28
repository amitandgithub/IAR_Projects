/*
 * I2CDriver.hpp
 *
 *  Created on: 16-Dec-2017
 *      Author: Amit Chaudhary
 */

#ifndef APP_INC_I2CDRIVER_HPP_
#define APP_INC_I2CDRIVER_HPP_

#include"Peripheral.hpp"
#include "stm32f10x.h"
#define Timed(x) Timeout = 0xFFFF; while (x) { if (Timeout -- == 0) goto errReturn ;}
namespace Bsp
{

class I2CDriver : public Peripheral
{
public:
typedef enum
{
I2C_ERROR_NONE = 0,
I2C_ERROR_RECIEVE_NACK,
I2C_ERROR_BUSY_TRANSMITTING,
I2C_ERROR_BUSY_RECEIVING,
}I2C_STATUS;
;
	typedef void(*I2CIsr_t)();
	typedef enum{
		I2C1_B6_B7 = 0,
		I2C1_B8_B9,
		I2C2_B11_B12
	}I2CInstance_t;
	typedef enum{
		BaudRate_100000   = 100000,
		BaudRate_400000   = 400000
	}I2CBaudRate_t;
	typedef enum{
		Master = 0,
		Slave  = 1
	}I2CMode_t;

	virtual ~I2CDriver();
	I2CDriver(I2CInstance_t I2CInstance, I2CIsr_t aI2CIsr = nullptr, I2CMode_t I2CMode = Master, I2CBaudRate_t I2CBaudRate = BaudRate_100000 );
	bool HwInit();
	I2C_STATUS HwStart();
	I2C_STATUS HwStop();
	I2C_STATUS HwSendAddressWithDirection(uint8_t address, uint8_t direction);
	I2C_STATUS HwSendACK();
	I2C_STATUS HwSendNACK();
	I2C_STATUS HwReset();
	uint8_t    HwRead(u8 SlaveAddress);
	I2C_STATUS HwWrite(u8 SlaveAddress);
	I2C_STATUS Send   (u8 SlaveAddress, u8* pBuf, u32 Bytes);
	I2C_STATUS Receive(u8 SlaveAddress, u8* pBuf, u32 Bytes);
	uint8_t ScanDevice(uint8_t SlaveAddress);
        uint8_t ScanBus(uint8_t* pResult, uint8_t Len);

private :
	I2CInstance_t m_I2CInstance;
	I2CIsr_t      m_I2CIsr;
	I2CMode_t     m_I2CMode;
	I2CBaudRate_t m_I2CBaudRate;
	I2C_TypeDef*  m_I2Cx;

};

} /* namespace Bsp */

#endif /* APP_INC_I2CDRIVER_HPP_ */
