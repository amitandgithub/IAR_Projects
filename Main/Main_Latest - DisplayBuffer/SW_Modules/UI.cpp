/*
 * UI.cpp
 *
 *  Created on: 01-Nov-2017
 *      Author: Amit Chaudhary
 *  23-Oct-2018: Modifed to add display buffer support.
 */

#include"UI.h"
#include"Nokia5110LCD.h"

using namespace std;

namespace Peripherals
{

unsigned char UI::ActiveScreen = 0; 
unsigned char UI::TotalRegisteredScreens = 0;
unsigned char UI::PreviousActiveScreen = 0;

UI::UI(Nokia5110LCD* pNokiaLCD): LCD(pNokiaLCD)
{

}
bool UI::Init()
{
	LCD->HwInit();
	LCD->DisplayStr(0, 0, "Initializing");
        TotalAddeedScreens = 0;
        for(uint8_t i = 0; i < NO_OF_SCREENS_IN_UI; i++)
        {
          m_Screens[i] = nullptr;
        }
        
	return true;
}

void UI::EventHamdler(Screen::Event_t& rEvent)
{
	if( rEvent != Screen::MaxEvents )
	{
          m_Screens[ActiveScreen % NO_OF_SCREENS_IN_UI]->EventHandler(rEvent);
	  rEvent = Screen::MaxEvents;
	}
}

void UI::DisplayScreen()
{ 
  if(m_Screens[ActiveScreen % NO_OF_SCREENS_IN_UI]) 
  {
      LCD->DisplayBuf( m_Screens[ActiveScreen % NO_OF_SCREENS_IN_UI]->GetBuffer() );
  }
  else
  {
    if(m_Screens[0])
      LCD->DisplayBuf( m_Screens[0]->GetBuffer() );
  }
  LCD->Refresh();
}














}


