/*
 * UI.cpp
 *
 *  Created on: 01-Nov-2017
 *      Author: Amit Chaudhary
 */

#include"UI.hpp"
#include"Line.hpp"
#include"Menu.hpp"
#include"Page.hpp"
#include"Nokia5110LCD.hpp"

using namespace std;

namespace App
{

unsigned char UI::ActiveScreen = 0; 
unsigned char UI::TotalRegisteredScreens = 0;
unsigned char UI::PreviousActiveScreen = 0;

UI::UI(Nokia5110LCD* m_pNokiaLCD): m_pNokiaLCD(m_pNokiaLCD)
{

}
bool UI::Init()
{
	m_pNokiaLCD->HwInit();
	m_pNokiaLCD->DrawLine(0, 0, "Initializing");
	return true;
}
void UI::DisplayMenu(unsigned char Slot)
{
	if( Slot <= NO_OF_MENUS_IN_UI)
	{
		m_pNokiaLCD->DrawBuffer(Menus[Slot].GetMenuAddress() );
	}
}

void UI::EventHamdler(Screen::Event_t& rEvent)
{
	if( rEvent != Screen::MaxEvents )
	{
          m_aScreens[ActiveScreen % NO_OF_SCREENS_IN_UI]->EventHandler(rEvent);
	  rEvent = Screen::MaxEvents;
	}
}















}


