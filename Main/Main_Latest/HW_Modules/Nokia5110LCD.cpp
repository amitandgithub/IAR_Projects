/*
 * Nokia5110LCD.cpp
 *
 *  Created on: 28-Oct-2017
 *
 *      Author: Amit Chaudhary
 * 19-Sep-2018 - Added more functions like DisWriteChar,DisWriteStr,DisWriteBuf
 * 
 * 
 */


/*
 * Nokia5110LCD.cpp
 *
 *  Created on: 28-Oct-2017
 *      Author: Amit Chaudhary
 */


#include "Nokia5110LCD.h"

namespace Peripherals
{

//This table contains the hex values that represent pixels
//for a font that is 6 pixels wide and 8 pixels high
   static const int8_t ASCII[][6] = {
   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 20
  ,{0x00, 0x00, 0x5f, 0x00, 0x00, 0x00} // 21 !
  ,{0x00, 0x07, 0x00, 0x07, 0x00, 0x00} // 22 "
  ,{0x14, 0x7f, 0x14, 0x7f, 0x14, 0x00} // 23 #
  ,{0x24, 0x2a, 0x7f, 0x2a, 0x12, 0x00} // 24 $
  ,{0x23, 0x13, 0x08, 0x64, 0x62, 0x00} // 25 %
  ,{0x36, 0x49, 0x55, 0x22, 0x50, 0x00} // 26 &
  ,{0x00, 0x05, 0x03, 0x00, 0x00, 0x00} // 27 '
  ,{0x00, 0x1c, 0x22, 0x41, 0x00, 0x00} // 28 (
  ,{0x00, 0x41, 0x22, 0x1c, 0x00, 0x00} // 29 )
  ,{0x14, 0x08, 0x3e, 0x08, 0x14, 0x00} // 2a *
  ,{0x08, 0x08, 0x3e, 0x08, 0x08, 0x00} // 2b +
  ,{0x00, 0x50, 0x30, 0x00, 0x00, 0x00} // 2c ,
  ,{0x08, 0x08, 0x08, 0x08, 0x08, 0x00} // 2d -
  ,{0x00, 0x60, 0x60, 0x00, 0x00, 0x00} // 2e .
  ,{0x20, 0x10, 0x08, 0x04, 0x02, 0x00} // 2f /
  ,{0x3e, 0x51, 0x49, 0x45, 0x3e, 0x00} // 30 0
  ,{0x00, 0x42, 0x7f, 0x40, 0x00, 0x00} // 31 1
  ,{0x42, 0x61, 0x51, 0x49, 0x46, 0x00} // 32 2
  ,{0x21, 0x41, 0x45, 0x4b, 0x31, 0x00} // 33 3
  ,{0x18, 0x14, 0x12, 0x7f, 0x10, 0x00} // 34 4
  ,{0x27, 0x45, 0x45, 0x45, 0x39, 0x00} // 35 5
  ,{0x3c, 0x4a, 0x49, 0x49, 0x30, 0x00} // 36 6
  ,{0x01, 0x71, 0x09, 0x05, 0x03, 0x00} // 37 7
  ,{0x36, 0x49, 0x49, 0x49, 0x36, 0x00} // 38 8
  ,{0x06, 0x49, 0x49, 0x29, 0x1e, 0x00} // 39 9
  ,{0x00, 0x36, 0x36, 0x00, 0x00, 0x00} // 3a :
  ,{0x00, 0x56, 0x36, 0x00, 0x00, 0x00} // 3b ;
  ,{0x08, 0x14, 0x22, 0x41, 0x00, 0x00} // 3c <
  ,{0x14, 0x14, 0x14, 0x14, 0x14, 0x00} // 3d =
  ,{0x00, 0x41, 0x22, 0x14, 0x08, 0x00} // 3e >
  ,{0x02, 0x01, 0x51, 0x09, 0x06, 0x00} // 3f ?
  ,{0x32, 0x49, 0x79, 0x41, 0x3e, 0x00} // 40 @
  ,{0x7e, 0x11, 0x11, 0x11, 0x7e, 0x00} // 41 A
  ,{0x7f, 0x49, 0x49, 0x49, 0x36, 0x00} // 42 B
  ,{0x3e, 0x41, 0x41, 0x41, 0x22, 0x00} // 43 C
  ,{0x7f, 0x41, 0x41, 0x22, 0x1c, 0x00} // 44 D
  ,{0x7f, 0x49, 0x49, 0x49, 0x41, 0x00} // 45 E
  ,{0x7f, 0x09, 0x09, 0x09, 0x01, 0x00} // 46 F
  ,{0x3e, 0x41, 0x49, 0x49, 0x7a, 0x00} // 47 G
  ,{0x7f, 0x08, 0x08, 0x08, 0x7f, 0x00} // 48 H
  ,{0x00, 0x41, 0x7f, 0x41, 0x00, 0x00} // 49 I
  ,{0x20, 0x40, 0x41, 0x3f, 0x01, 0x00} // 4a J
  ,{0x7f, 0x08, 0x14, 0x22, 0x41, 0x00} // 4b K
  ,{0x7f, 0x40, 0x40, 0x40, 0x40, 0x00} // 4c L
  ,{0x7f, 0x02, 0x0c, 0x02, 0x7f, 0x00} // 4d M
  ,{0x7f, 0x04, 0x08, 0x10, 0x7f, 0x00} // 4e N
  ,{0x3e, 0x41, 0x41, 0x41, 0x3e, 0x00} // 4f O
  ,{0x7f, 0x09, 0x09, 0x09, 0x06, 0x00} // 50 P
  ,{0x3e, 0x41, 0x51, 0x21, 0x5e, 0x00} // 51 Q
  ,{0x7f, 0x09, 0x19, 0x29, 0x46, 0x00} // 52 R
  ,{0x46, 0x49, 0x49, 0x49, 0x31, 0x00} // 53 S
  ,{0x01, 0x01, 0x7f, 0x01, 0x01, 0x00} // 54 T
  ,{0x3f, 0x40, 0x40, 0x40, 0x3f, 0x00} // 55 U
  ,{0x1f, 0x20, 0x40, 0x20, 0x1f, 0x00} // 56 V
  ,{0x3f, 0x40, 0x38, 0x40, 0x3f, 0x00} // 57 W
  ,{0x63, 0x14, 0x08, 0x14, 0x63, 0x00} // 58 X
  ,{0x07, 0x08, 0x70, 0x08, 0x07, 0x00} // 59 Y
  ,{0x61, 0x51, 0x49, 0x45, 0x43, 0x00} // 5a Z
  ,{0x00, 0x7f, 0x41, 0x41, 0x00, 0x00} // 5b [
  ,{0x02, 0x04, 0x08, 0x10, 0x20, 0x00} // 5c /
  ,{0x00, 0x41, 0x41, 0x7f, 0x00, 0x00} // 5d ]
  ,{0x04, 0x02, 0x01, 0x02, 0x04, 0x00} // 5e ^
  ,{0x40, 0x40, 0x40, 0x40, 0x40, 0x00} // 5f _
  ,{0x00, 0x01, 0x02, 0x04, 0x00, 0x00} // 60 `
  /*,{0x00, 0x00, 0x00, 0x00, 0x, 0x0000} // 20 // Padded to fix the bug, when try to print a, it prints b*/
  ,{0x20, 0x54, 0x54, 0x54, 0x78, 0x00} // 61 a
  ,{0x7f, 0x48, 0x44, 0x44, 0x38, 0x00} // 62 b
  ,{0x38, 0x44, 0x44, 0x44, 0x20, 0x00} // 63 c
  ,{0x38, 0x44, 0x44, 0x48, 0x7f, 0x00} // 64 d
  ,{0x38, 0x54, 0x54, 0x54, 0x18, 0x00} // 65 e
  ,{0x08, 0x7e, 0x09, 0x01, 0x02, 0x00} // 66 f
  ,{0x0c, 0x52, 0x52, 0x52, 0x3e, 0x00} // 67 g
  ,{0x7f, 0x08, 0x04, 0x04, 0x78, 0x00} // 68 h
  ,{0x00, 0x44, 0x7d, 0x40, 0x00, 0x00} // 69 i
  ,{0x20, 0x40, 0x44, 0x3d, 0x00, 0x00} // 6a j
  ,{0x7f, 0x10, 0x28, 0x44, 0x00, 0x00} // 6b k
  ,{0x00, 0x41, 0x7f, 0x40, 0x00, 0x00} // 6c l
  ,{0x7c, 0x04, 0x18, 0x04, 0x78, 0x00} // 6d m
  ,{0x7c, 0x08, 0x04, 0x04, 0x78, 0x00} // 6e n
  ,{0x38, 0x44, 0x44, 0x44, 0x38, 0x00} // 6f o
  ,{0x7c, 0x14, 0x14, 0x14, 0x08, 0x00} // 70 p
  ,{0x08, 0x14, 0x14, 0x18, 0x7c, 0x00} // 71 q
  ,{0x7c, 0x08, 0x04, 0x04, 0x08, 0x00} // 72 r
  ,{0x48, 0x54, 0x54, 0x54, 0x20, 0x00} // 73 s
  ,{0x04, 0x3f, 0x44, 0x40, 0x20, 0x00} // 74 t
  ,{0x3c, 0x40, 0x40, 0x20, 0x7c, 0x00} // 75 u
  ,{0x1c, 0x20, 0x40, 0x20, 0x1c, 0x00} // 76 v
  ,{0x3c, 0x40, 0x30, 0x40, 0x3c, 0x00} // 77 w
  ,{0x44, 0x28, 0x10, 0x28, 0x44, 0x00} // 78 x
  ,{0x0c, 0x50, 0x50, 0x50, 0x3c, 0x00} // 79 y
  ,{0x44, 0x64, 0x54, 0x4c, 0x44, 0x00} // 7a z
  ,{0x00, 0x08, 0x36, 0x41, 0x00, 0x00} // 7b {
  ,{0x00, 0x00, 0x7f, 0x00, 0x00, 0x00} // 7c |
  ,{0x00, 0x41, 0x36, 0x08, 0x00, 0x00} // 7d }
  ,{0x10, 0x08, 0x08, 0x10, 0x08, 0x00} // 7e ~
  ,{0x78, 0x46, 0x41, 0x46, 0x78, 0x00} // 7f DEL
};

Nokia5110LCD::Nokia5110LCD(SPIDrv_t::SPIx_t Spix, GpioOutput::PORT_t ResetPort, GpioOutput::PIN_t ResetPin,
				           GpioOutput::PORT_t DCPort, GpioOutput::PIN_t DCPin, GpioOutput::PORT_t BKLPort, GpioOutput::PIN_t BKLPin)

{
//    SpiDriverLCD(Spix, 100000);
//    DataCommandSelectGpio(DCPort,DCPin);
//    ResetPinGpio(ResetPort,ResetPin);
//    BackLightGpio(BKLPort,BKLPin);
}

Nokia5110LCD::Nokia5110LCD(SPIDrv_t*   pSpiDriverLCD ,
                 GpioOutput* pCS,
				 GpioOutput* pDataCommandSelectGpio,
				 GpioOutput* pResetPinGpio,
				 GpioOutput* pBackLightGpio): 
                m_pSpiDriverLCD(pSpiDriverLCD),
                m_pDataCommandSelectGpio(pDataCommandSelectGpio),
                m_pResetPinGpio(pResetPinGpio),
                m_pBackLightGpio(pBackLightGpio),
                m_pCS(pCS),
                m_Brightness(0x13)
#if defined(DUAL_BUFFER)
                ,m_pAppBuf(m_BufferA),
                 m_pSysBuf(m_BufferB)
#endif

{
    
    
    
}

bool Nokia5110LCD::HwInit()
{
    if( (m_pSpiDriverLCD->GetStatus(m_pSpiDriverLCD->GetSPIx()) & Peripherals::SPI_Base::SPI_INIT_DONE) != Peripherals::SPI_Base::SPI_INIT_DONE )
    {
       m_pSpiDriverLCD->HwInit(); 
    }
   	
	m_pDataCommandSelectGpio->HwInit();
	m_pResetPinGpio->HwInit();
	m_pBackLightGpio->HwInit();
    m_pCS->HwInit();
    //m_pCS->On();
	//Initialize the Display
	DisplayInit();

	return true;
}

bool Nokia5110LCD::DisplayInit()
{
	  //Reset the LCD to a known state

	  m_pResetPinGpio->Off();

      HAL_Delay(500);

	  m_pResetPinGpio->On();

	  Write(COMMAND, 0x21); //Tell LCD that extended commands follow
	  Write(COMMAND, 0xBF); //Set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark, Amit: 0xBF works fine with 3.3v
	  Write(COMMAND, 0x04); //Set Temp coefficent
	  Write(COMMAND, m_Brightness); //LCD bias mode 1:48: Try 0x13 or 0x14 ,Amit: 0x13 works fine with 3.3v, for blue display 0x15 works fine

	  Write(COMMAND, 0x20); //We must send 0x20 before modifying the display control mode
	  Write(COMMAND, 0x0C); //Set display control, normal mode. 0x0D for inverse

	  Clear();


	return true;
}


//There are two memory banks in the LCD, data/RAM and commands. This
//function sets the DC pin high or low depending, and then sends
//the data byte
void Nokia5110LCD::Write(DC_t DC, unsigned char data)
{
    
 	if(DC == DATA)
 	{
 		m_pDataCommandSelectGpio->On();
 	}
 	else
 	{
 		m_pDataCommandSelectGpio->Off();
 	}
    
    m_pSpiDriverLCD->Tx(&data,1);
    //m_pSpiDriverLCD->TxDirect(m_pSpiDriverLCD->GetSPIx(), &data,1);
    
}


void Nokia5110LCD::SetMode(uint8_t LCDMode)
{
	if(LCDMode == INVERSE)
	{
		Write(COMMAND,INVERSE);
	}
	else if(LCDMode == NORMAL)
	{
		Write(COMMAND,NORMAL);
	}
	else
	{

	}

}

//Clears the LCD by writing zeros to the entire screen
void Nokia5110LCD::Clear()
{
	int32_t index;
	for (index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
		Write(DATA, 0x00);
	GoToXY(0, 0); //After we clear the display, return to the home position
}

void Nokia5110LCD::GoToXY(int x, int y)
{
	Write(COMMAND, 0x80 | x);  // Column.
	Write(COMMAND, 0x40 | y);  // Row.  ?
}

//This takes a large array of bits and sends them to the LCD
void Nokia5110LCD::DrawBitmap(const char my_array[])
{
	int index;
	for (index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
		Write(DATA, my_array[index]);
}
//This function takes in a character, looks it up in the font table/array
//And writes it to the screen
//Each character is 8 bits tall and 5 bits wide. We pad one blank column of
//pixels on each side of the character for readability.
void Nokia5110LCD::LCDCharacter(const char character)
{
	int32_t index;
	//Write(DATA, 0x00); //Blank vertical line padding

	for (index = 0 ; index < 5 ; index++)
		Write(DATA, ASCII[character - 0x20][index]);
	//0x20 is the ASCII character for Space (' '). The font table starts with this character

	Write(DATA, 0x00); //Blank vertical line padding
}

//Given a string of characters, one by one is passed to the LCD
void Nokia5110LCD::DrawString(const char *characters)
{
  while (*characters)
    LCDCharacter(*characters++);
}

 void Nokia5110LCD::DrawLine(unsigned char Row, unsigned char Col, const char* Str)
{
	uint8_t i=0;
	GoToXY(Col*SIZE_OF_1_CHAR,Row);
	DrawString("              ");

	GoToXY(Col*SIZE_OF_1_CHAR,Row);

	while (*Str && i<NO_OF_CHAR_IN_LINE)
	{
		LCDCharacter(*Str++);
		i++;
	}

}
void Nokia5110LCD::DrawCharBuf(unsigned char Row, unsigned char Col, const char aChar, uint8_t format)
{
    uint32_t i;
    
    if(format == INVERSE)
    {
        for(i = 0; i<SIZE_OF_1_CHAR; i++)
        {
            
#if defined(DUAL_BUFFER)
            m_pAppBuf[Row*84 + Col*6 + i ] = ~ASCII[aChar - 0x20][i];
#else 
             m_BufferA[Row*84 + Col*6 + i ] = ~ASCII[aChar - 0x20][i];
#endif
        }        
    }
    else
    {
        for(i = 0; i<SIZE_OF_1_CHAR; i++)
        {
            
#if defined(DUAL_BUFFER)
            m_pAppBuf[Row*84 + Col*6 + i ] = ASCII[aChar - 0x20][i];
#else 
            m_BufferA[Row*84 + Col*6 + i ] = ASCII[aChar - 0x20][i];
#endif
        }
    }
}

void Nokia5110LCD::DrawStrBuf(unsigned char Row, unsigned char Col, const char* Str, uint8_t format)
{
    uint32_t i;
    
    for(i = 0; (i<NO_OF_CHAR_IN_LINE) && (Str[i] != '\0') ; i++)
    {
        DrawCharBuf(Row, Col+i, Str[i],format);
    }
  
}

void Nokia5110LCD::DrawBitmapBuf(const char* Str, uint8_t format)
{
    uint32_t i,Row,Chars;
        
    if(format == INVERSE)
    {
       for(Row = 0; Row < TOTAL_ROWS; Row++)
       {
           for(Chars = 0; Chars < NO_OF_CHAR_IN_LINE; Chars++)
           {
                for(i = 0; i < SIZE_OF_1_CHAR; i++)
                {
#if defined(DUAL_BUFFER)
                     m_pAppBuf[Row*84 + Chars*6 + i] = ~ASCII[Str[Row*84  + Chars*6 + i] - 0x20][i];
#else
                      m_BufferA[Row*84 + Chars*6 + i] = ~ASCII[Str[Row*84  + Chars*6 + i] - 0x20][i];
#endif
                }              
           }  
       }
      
    }
    else
    {
       for(Row = 0; Row < TOTAL_ROWS; Row++)
       {
           for(Chars = 0; Chars < NO_OF_CHAR_IN_LINE; Chars++)
           {
                for(i = 0; i < SIZE_OF_1_CHAR; i++)
                {
#if defined(DUAL_BUFFER)
                    m_pAppBuf[Row*84 + Chars*6 + i] = ASCII[Str[Row*84  + Chars*6 + i] - 0x20][i];
#else
                    m_BufferA[Row*84 + Chars*6 + i] = ASCII[Str[Row*84  + Chars*6 + i] - 0x20][i];
#endif
                }              
           }  
       }
    }
        
}
uint32_t Nokia5110LCD::Refresh()
{
   static uint32_t Status;


       m_pDataCommandSelectGpio->On();
       
#if defined ( DUAL_BUFFER )
       
       uint8_t* pTempBuf;
       
       __disable_irq();
       
       pTempBuf = m_pAppBuf;
       
       m_pAppBuf = m_pSysBuf;
       
       m_pSysBuf = pTempBuf;
       
       __enable_irq();       
       
       m_CurrentTransaction.TxBuf = m_pSysBuf;       
       m_CurrentTransaction.TxLen = DISPLAY_BUF_SIZE;
       m_CurrentTransaction.pCS = m_pCS;
       m_CurrentTransaction.TxnStatus.TimeValue = HAL_GetTick();
       m_CurrentTransaction.TxnStatus.Event &=  ~(SPI_Base::SPI_TX_COMPLETE);     
       
       Status =  m_pSpiDriverLCD->Post(&m_CurrentTransaction); 
#else     
     m_CurrentTransaction.TxBuf = m_BufferA;     
     m_CurrentTransaction.TxLen = DISPLAY_BUF_SIZE;
     m_CurrentTransaction.pCS = m_pCS;
     m_CurrentTransaction.TxnStatus.TimeValue = 0;
     m_CurrentTransaction.TxnStatus.Event &=  ~(SPI_Base::SPI_TX_COMPLETE);  
//     while((m_CurrentTransaction.TxnStatus.Event & SPI_Base::SPI_TX_COMPLETE) == SPI_Base::SPI_TX_COMPLETE);
     
     Status = m_pSpiDriverLCD->Post(&m_CurrentTransaction);
     
#endif
     
     return Status;


    
}

void Nokia5110LCD::DrawChar(unsigned char Row, unsigned char Col, const char aChar)
{
	GoToXY(Col*SIZE_OF_1_CHAR,Row);
	LCDCharacter(aChar);

}

void Nokia5110LCD::DrawBuffer(char* pBuffer)
{
	GoToXY(0*SIZE_OF_1_CHAR,0);

	for(int i = 0; i < NO_OF_CHAR_IN_LINE*6 ; i++)
	LCDCharacter(pBuffer[i]);

}

void Nokia5110LCD::ClearBuffer()
{
#if 0
    uint32_t i,Row,Chars;
    
	GoToXY(0*SIZE_OF_1_CHAR,0);

       for(Row = 0; Row < TOTAL_ROWS; Row++)
       {
           for(Chars = 0; Chars < NO_OF_CHAR_IN_LINE; Chars++)
           {
                for(i = 0; i < SIZE_OF_1_CHAR; i++)
                {
#if defined(DUAL_BUFFER)
                     m_pAppBuf[Row*84 + Chars*6 + i] = 0x00;
#else
                     m_BufferA[Row*84 + Chars*6 + i] = 0x00;
#endif
                }              
           }  
       }
#endif
       
#if defined(DUAL_BUFFER)
       //m_pAppBuf[Row*84 + Chars*6 + i] = 0x00;
       for(uint32_t count = 0; count< DISPLAY_BUF_SIZE; count++)
           m_pAppBuf[count] = 0;
#else
      // m_BufferA[Row*84 + Chars*6 + i] = 0x00;
       for(uint32_t count = 0; count< DISPLAY_BUF_SIZE; count++)
           m_BufferA[count] = 0;
#endif

}



void Nokia5110LCD::PowerDown( )
{
    uint8_t cmd = 0x08 | 0x04;
    
    Clear();
    
    m_pDataCommandSelectGpio->Off();         
    m_pSpiDriverLCD->Tx(&cmd,1);

}

void Nokia5110LCD::InvertRowBuf(unsigned char Row)
{
    uint32_t i;
    
    for(i = 0; (i<84) ; i++)
    {
#if defined(DUAL_BUFFER)
        m_pAppBuf[Row*84 + i] = ~m_pAppBuf[Row*84 + i];
#else
        m_BufferA[Row*84 + i] = ~m_BufferA[Row*84 + i];
#endif
    }
    

                      
}



}