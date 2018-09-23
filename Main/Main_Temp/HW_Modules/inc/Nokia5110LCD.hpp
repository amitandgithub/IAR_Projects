/*
 * Nokia5110LCD.hpp
 *
 *  Created on: 28-Oct-2017
 *      Author: Amit Chaudhary
 */

#ifndef APP_INC_NOKIA5110LCD_HPP_
#define APP_INC_NOKIA5110LCD_HPP_


#include "SPI_Poll.h"
#include "SPI_IT.h"
#include "SPI_DMA.h"
#include "GpioInput.hpp"
#include "GpioOutput.hpp"


namespace Peripherals
{



class Nokia5110LCD
{
public:
    //typedef Peripherals::SPI_Poll SPIDrv_t;
    //typedef Peripherals::SPI_IT SPIDrv_t;
    typedef Peripherals::SPI_DMA SPIDrv_t;
	typedef enum
	{
		COMMAND = 0,
		DATA
	}DC_t;

	static const uint8_t NORMAL  = 0x0C;
	static const uint8_t INVERSE = 0x0D;

	static const uint8_t LCD_X  = 84;
	static const uint8_t LCD_Y  = 48;

	static const uint8_t SIZE_OF_1_CHAR = 6;
    static const uint8_t NO_OF_CHAR_IN_LINE = 14;

	Nokia5110LCD(SPIDrv_t*   pSpiDriverLCD ,
				 GpioOutput* pDataCommandSelectGpio,
				 GpioOutput* pResetPinGpio,
                 GpioOutput* pBackLightGpio);
    
    Nokia5110LCD(SPIDrv_t::SPIx_t Spix,
				 GpioOutput::PORT_t ResetPort, GpioOutput::PIN_t ResetPin,
				 GpioOutput::PORT_t DCPort, GpioOutput::PIN_t DCPin,
				 GpioOutput::PORT_t BKLPort, GpioOutput::PIN_t BKLPin);
    
	~Nokia5110LCD(){};
	bool HwInit();
	bool DisplayInit();
	void SetMode(uint8_t LCDMode);
	void Write(DC_t DC, unsigned char data);
	void GoToXY(int x, int y);
	void Clear();
	void DrawLine(unsigned char Row, unsigned char Col, const char* Str);
	void DrawString(const char *characters);
	void DrawBitmap(const char my_array[]);
	void LCDCharacter(const char character);
	void DrawChar(unsigned char Row, unsigned char Col, const char aChar);
	void DrawBuffer(char* pBuffer);
    void SetBrigntness(uint8_t Brightness = 0x13){m_Brightness = Brightness;HwInit();}

private:
//    SPIDrv_t   SpiDriverLCD(SPIDrv_t::SPIx_t Spix, uint32_t hz);
//	GpioOutput DataCommandSelectGpio(GpioOutput::PORT_t D_C_Port, GpioOutput::PIN_t D_C_Pin);
//	GpioOutput ResetPinGpio(GpioOutput::PORT_t ResetPinGpio_Port, GpioOutput::PIN_t ResetPinGpio_Pin);
//	GpioOutput BackLightGpio(GpioOutput::PORT_t BackLightGpio_Port, GpioOutput::PIN_t BackLightGpio_Pin);
    SPIDrv_t*   m_pSpiDriverLCD;
	GpioOutput* m_pDataCommandSelectGpio;
	GpioOutput* m_pResetPinGpio;
	GpioOutput* m_pBackLightGpio;
    uint8_t     m_Brightness;
};






















}

























#endif /* APP_INC_NOKIA5110LCD_HPP_ */
