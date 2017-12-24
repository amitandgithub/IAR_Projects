/*
 * UI.hpp
 *
 *  Created on: 01-Nov-2017
 *      Author: Amit Chaudhary
 */

#ifndef APP_INC_UI_HPP_
#define APP_INC_UI_HPP_

#include"Line.hpp"
#include"Menu.hpp"
#include"Nokia5110LCD.hpp"
#include <cstring>

namespace App
{


class UI
{
public:

	const static unsigned char NO_OF_MENUS_IN_UI = 3U;

	UI(Nokia5110LCD* m_pNokiaLCD);
	~UI(){};
	bool Init();
	void AddMenu(Menu& rMenu){Menus[0] = rMenu;}

	void AddMenu(Menu& rMenu, unsigned char Slot){ Menus[Slot] = rMenu; }

	bool DeleteMenu(unsigned char Slot){return true;}

	void DisplayMenu(unsigned char Slot);

	void Run();

	void EventHamdler(Menu::Event_t& rEvent);

	inline Menu& GetActiveMenu() {return Menus[ActiveMenu];}

	inline void SetActiveMenu(unsigned char Slot) { ActiveMenu = (Slot % NO_OF_MENUS_IN_UI); }

	inline void SetMenuLineTest(unsigned char Menu, unsigned char Line, unsigned char Col, const char* pText)
	{
		Menus[Menu % NO_OF_MENUS_IN_UI].SetLineText(Line,Col,pText);
	}


	Menu Menus[NO_OF_MENUS_IN_UI];
private:

	unsigned char ActiveMenu;
	Nokia5110LCD* m_pNokiaLCD;
};

























}

























#endif /* APP_INC_UI_HPP_ */
