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


UI::UI(Nokia5110LCD* m_pNokiaLCD): ActiveMenu(0), m_pNokiaLCD(m_pNokiaLCD)
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
		//m_pNokiaLCD->DrawBuffer(reinterpret_cast<char *>(&Menus[Slot]) );
		m_pNokiaLCD->DrawBuffer(&Menus[Slot].MenuText[0] );
	}
}
void UI::Run()
{
	DisplayMenu( ActiveMenu % NO_OF_MENUS_IN_UI);
}

void UI::EventHamdler(Menu::Event_t& rEvent)
{
	if( rEvent != Menu::MaxEvents )
	{
		Menus[ActiveMenu].EventHandler(rEvent);
		rEvent = Menu::MaxEvents;
	}
}















}


