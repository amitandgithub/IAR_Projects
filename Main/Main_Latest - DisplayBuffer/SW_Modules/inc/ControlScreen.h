/*
 * ControlScreen.hpp
 *
 *  Created on: 25-Dec-2017
 *      Author: Amit Chaudhary
 *  23-Oct-2018: Modifed to add display buffer support.
 */

#ifndef CONTROLSCREEN_HPP_
#define CONTROLSCREEN_HPP_

#include "Screen.h"

namespace Peripherals {

class ControlScreen : public Screen
{
public:
    
    constexpr static unsigned char LAST_LINE = (NO_OF_LINES_IN_SCREEN-1U);
	const static unsigned char FIRST_LINE = 0U;
    
	ControlScreen();
    
    ControlScreen(char * pText){m_Screen.DrawBuffer(pText);}
    
	virtual ~ControlScreen();

	typedef enum
	{
		Up = 0,
		Down
	}Direction_t;
    
    typedef struct
    {
        EventHandler_t LongTouchHandler;
        EventHandler_t LLongTouchHandler;        
    }LineEventHandler_t;
    
    typedef struct
    {
        LineEventHandler_t Array[NO_OF_LINES_IN_SCREEN];       
    }ControlScreenHandler_t;
    
	char m_Pointer;
	char m_Space;


    void AddHandler(unsigned char LineNo, EventHandler_t LongTouchHandler, EventHandler_t LLongTouchHandler);

	void EventHandler(Event_t anEvent);

	unsigned char GetActiveLine() const {return ActiveLine;}

    void DrawChar(unsigned char Row, unsigned char Col, const char aChar)    {m_Screen.DrawChar(Row,Col,aChar);}
    void DrawStr(unsigned char Row, unsigned char Col, const char* Str)      {m_Screen.DrawStr(Row,Col,Str);}
    void DrawBuffer(char* pBuffer)                                           {m_Screen.DrawBuffer(pBuffer);}
    void DrawBitmap(char* pBuffer)                                           {m_Screen.DrawBitmap(pBuffer);}
    void InvertRow (unsigned char Row)                                       {m_Screen.InvertRow(Row);}
    char* GetBuffer()                                                        { return m_Screen.GetBuffer();}
    
private:
    void MovePointer(Direction_t Direction);
private:
  	Screen m_Screen;
    ControlScreenHandler_t m_EventHandlers;
	unsigned char ActiveLine;

};

} /* namespace Peripherals */

#endif /* CONTROLSCREEN_HPP_ */