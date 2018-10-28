/*
 * ControlScreen.cpp
 *
 *  Created on: 25-Dec-2017
 *      Author: Amit Chaudhary
 *  23-Oct-2018: Modifed to add display buffer support.
 */

#include "ControlScreen.h"

namespace Peripherals {

ControlScreen::ControlScreen(): ActiveLine(0)
{
  m_Pointer = '>';
  m_Space = ' ';

  for(int i = 0; i<NO_OF_LINES_IN_SCREEN; i++)
  {
		m_EventHandlers.Array[i].LongTouchHandler = nullptr;
        m_EventHandlers.Array[i].LLongTouchHandler = nullptr;
  }
}

ControlScreen::~ControlScreen()
{

}

void ControlScreen::AddHandler(unsigned char LineNo, EventHandler_t LongTouchHandler, EventHandler_t LLongTouchHandler)
{
		m_EventHandlers.Array[LineNo].LongTouchHandler = LongTouchHandler;
        m_EventHandlers.Array[LineNo].LLongTouchHandler = LLongTouchHandler;
}

void ControlScreen::EventHandler(Event_t anEvent)
{
	if(anEvent == Touch)
	{
		//if(EventHandlers[ActiveLine*Menu::NO_OF_HANDLERS_IN_LINE + Touch ])
			//EventHandlers[ActiveLine*Menu::NO_OF_HANDLERS_IN_LINE + Touch ]();

		MovePointer(Down);
	}
	else if(anEvent == LongTouch)
	{
		if(m_EventHandlers.Array[ActiveLine].LongTouchHandler)
			m_EventHandlers.Array[ActiveLine].LongTouchHandler();
	}
	else if(anEvent == LongLongTouch)
	{
		if(m_EventHandlers.Array[ActiveLine].LLongTouchHandler)
			m_EventHandlers.Array[ActiveLine].LLongTouchHandler();
	}
	else
	{
		// Nothing To Do
	}
}

void ControlScreen::MovePointer(Direction_t Direction)
{
	//clear the pointer from current line
        m_Screen.InvertRow(ActiveLine);

	if( (ActiveLine == FIRST_LINE) && (Direction == Up) )
	{
		// Roll over to the last line
		ActiveLine = LAST_LINE;
	}
	else if( (ActiveLine == LAST_LINE) && (Direction == Down) )
	{
		// Roll over to the last line
		ActiveLine = FIRST_LINE;
	}
	else if( Direction == Down )
	{
		// Roll over to the last line
		ActiveLine += 1;
	}
	else if( Direction == Up )
	{
		// Roll over to the First line
		ActiveLine -= 1;

	}
	else
	{

	}

     m_Screen.InvertRow(ActiveLine);
}

} /* namespace Peripherals */