/*
 * Screen.hpp
 *
 *  Created on: 25-Dec-2017
 *      Author: Amit Chaudhary
 *  21-Oct-2018: Modifed to add display buffer support.
 */

#include <cstring>
#include<stdio.h>
#include"UI.h"

#ifndef SCREEN_HPP_
#define SCREEN_HPP_


#include "DisplayBuffer.h"

namespace Peripherals
{

class Screen
{
public:
  	typedef void(*EventHandler_t)();
    
    static const        uint8_t NO_OF_LINES_IN_SCREEN          = 6U;
    
	typedef enum
	{
		Touch = 0,
		LongTouch,
		LongLongTouch,
		MaxEvents
	}Event_t;

	Screen();
    
    Screen(char* pText);

	virtual ~Screen();
    
    void DrawChar(unsigned char Row, unsigned char Col, const char aChar)    {m_DisplayBuffer.DrawChar(Row,Col,aChar);}
    void DrawStr(unsigned char Row, unsigned char Col, const char* Str)      {m_DisplayBuffer.DrawStr(Row,Col,Str);}
    void DrawBuffer(char* pBuffer)                                           {m_DisplayBuffer.DrawBuffer(pBuffer);}
    void DrawBitmap(char* pBuffer)                                           {m_DisplayBuffer.DrawBitmap(pBuffer);}
    void InvertRow (unsigned char Row)                                       {m_DisplayBuffer.InvertRow(Row);}
    char* GetBuffer()                                                        { return m_DisplayBuffer.GetBuffer();}
    
    void EventHandler(Event_t anEvent);

private:
    DisplayBuffer m_DisplayBuffer;

};

} /* namespace Peripherals */

#endif /* SCREEN_HPP_ */