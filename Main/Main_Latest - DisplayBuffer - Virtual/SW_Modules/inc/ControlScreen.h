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
	ControlScreen();
	virtual ~ControlScreen();

	typedef enum
	{
		Up = 0,
		Down

	}Direction_t;
	const static unsigned char NO_OF_HANDLERS_IN_LINE = 2U;
	char m_Pointer;
	char m_Space;
	constexpr static unsigned char LAST_LINE = (TOTAL_ROWS-1U);
	const static unsigned char FIRST_LINE = 0U;
	constexpr static unsigned char SIZE_OF_HANDLER = ( TOTAL_ROWS * NO_OF_HANDLERS_IN_LINE ) ;

	inline void AddText(char * pText){std::memcpy(m_Screen.GetScreenTextArray(), pText, SIZE_OF_SCREEN);}

    void AddHandler(unsigned char LineNo, EventHandler_t LongTouchHandler, EventHandler_t LLongTouchHandler);

    virtual void SetText(unsigned char Line, unsigned char Col, const char* pText, unsigned char Len);//{m_Screen.SetText(Line,Col,pText,Len);}

	void EventHandler(Event_t anEvent);

	inline unsigned char GetActiveLine() const {return ActiveLine;}

    inline char * GetScreenTextArray(){return m_Screen.GetScreenTextArray();}

private:
  	Screen m_Screen;
	EventHandler_t m_EventHandlers[SIZE_OF_HANDLER];
	void MovePointer(Direction_t Direction);
	unsigned char ActiveLine;

};

} /* namespace Peripherals */

#endif /* CONTROLSCREEN_HPP_ */