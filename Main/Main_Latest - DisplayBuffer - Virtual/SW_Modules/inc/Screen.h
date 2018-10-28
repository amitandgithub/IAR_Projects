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

    class Screen : public DisplayBuffer
{
public:
  	typedef void(*EventHandler_t)();
    
        /* one char has 6 bytes of pixel data and one Line/Row has total 14 chars*/
    constexpr static unsigned char NO_OF_LINES_IN_SCREEN = 6U;  
    constexpr static unsigned char SIZE_OF_SCREEN        = 6U;
	typedef enum
	{
		Touch = 0,
		LongTouch,
		LongLongTouch,
		MaxEvents
	}Event_t;

	Screen();

	virtual ~Screen();

    virtual void EventHandler(Event_t anEvent);
            
    virtual void AddText(char* pText);
        
    virtual char* GetScreenTextArray();
    
    virtual void        DrawChar        (unsigned char Row, unsigned char Col, const char aChar, uint8_t format = NORMAL);
    virtual void        DrawStr         (unsigned char Row, unsigned char Col, const char* Str, uint8_t format = NORMAL);
    virtual void        DrawBuffer      (const char* Str, uint8_t format = NORMAL);
    virtual void        DrawBitmap      (const char* Str);
    virtual void        InvertRow       (unsigned char Row);
    virtual char*       GetBuffer       ();
    virtual void        Clear           ();
    virtual uint32_t    GetSize         ();

private:
    DisplayBuffer m_DisplayBuffer;

};

} /* namespace Peripherals */

#endif /* SCREEN_HPP_ */