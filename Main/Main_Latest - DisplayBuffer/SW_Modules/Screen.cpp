/*
 * Screen.cpp
 *
 *  Created on: 25-Dec-2017
 *      Author: Amit Chaudhary
 *  21-Oct-2018: Modifed to add display buffer support.
 */

#include "Screen.h"

namespace Peripherals {

Screen::Screen():m_DisplayBuffer()
{
    
}

Screen::Screen(char* pText):m_DisplayBuffer(pText)
{
    
}

Screen::~Screen()
{

}

void Screen::EventHandler(Event_t anEvent)
{
  //unsigned char LActiveScreen = Peripherals::UI::GetActiveScreen();

    if(anEvent == Touch)
	{
           Peripherals::UI::GoToPreviousScreen();
	}
	else if(anEvent == LongTouch)
	{
            Peripherals::UI::GoToNextScreen();
	}
	else if(anEvent == LongLongTouch)
	{
            //Peripherals::UI::GoToNextScreen();
	}
	else
	{
		// Nothing To Do
	}

}


} /* namespace Peripherals */