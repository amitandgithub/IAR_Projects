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
#include"Page.hpp"
#include <cstring>
#include <Screen.hpp>

namespace App
{


class UI
{
public:
	const static unsigned char NO_OF_MENUS_IN_UI = 3U;
        constexpr static unsigned char NO_OF_SCREENS_IN_UI = 5U;

	UI(Nokia5110LCD* m_pNokiaLCD);
	~UI(){};
	bool Init();
	void AddMenu(Menu& rMenu){Menus[0] = rMenu;}
        
        inline void AddScreen(Screen* pScreen ){m_aScreens[0] = pScreen;TotalRegisteredScreens++;}
        inline void AddScreen(Screen* pScreen, unsigned char Slot ){m_aScreens[Slot%NO_OF_SCREENS_IN_UI] = pScreen; TotalRegisteredScreens++;}
       // inline static void GoToPreviousScreen(){ if(ActiveScreen>0){PreviousActiveScreen = ActiveScreen; ActiveScreen -= 1 ;} } // --ActiveScreen %= TotalRegisteredScreens  
        inline static void GoToPreviousScreen(){SetActiveScreen(PreviousActiveScreen);  }
        inline static void GoToNextScreen(){ PreviousActiveScreen = ActiveScreen; ++ActiveScreen %= TotalRegisteredScreens ; }
        inline static unsigned char GetActiveScreen(){return ActiveScreen; }
        inline static void SetActiveScreen(unsigned char ScreenNo){ PreviousActiveScreen = ActiveScreen; ActiveScreen = ScreenNo; }
        //inline void DisplayScreen(){ m_pNokiaLCD->DrawBuffer( m_aScreens[ActiveScreen % NO_OF_SCREENS_IN_UI]->GetScreenTextArray() );}
        inline void DisplayScreen(){ if(m_aScreens[ActiveScreen % NO_OF_SCREENS_IN_UI]) m_pNokiaLCD->DrawBuffer( m_aScreens[ActiveScreen % NO_OF_SCREENS_IN_UI]->GetScreenTextArray() );}
        

	void AddMenu(Menu& rMenu, unsigned char Slot){ Menus[Slot] = rMenu; }

	bool DeleteMenu(unsigned char Slot){return true;}

	void DisplayMenu(unsigned char Slot);

	inline void Run(){DisplayScreen();}

	void EventHamdler(Screen::Event_t& rEvent);

	inline Menu& GetActiveMenu() {return Menus[ActiveMenu];}

	inline void SetActiveMenu(unsigned char Slot) { ActiveMenu = (Slot % NO_OF_MENUS_IN_UI); }

	inline void SetMenuLineTest(unsigned char Menu, unsigned char Line, unsigned char Col, const char* pText)
	{
		Menus[Menu % NO_OF_MENUS_IN_UI].SetLineText(Line,Col,pText);
	}


	Menu Menus[NO_OF_MENUS_IN_UI];
private:
        Screen* m_aScreens[NO_OF_SCREENS_IN_UI];
        static unsigned char ActiveScreen;
        static unsigned char PreviousActiveScreen;
        static unsigned char TotalRegisteredScreens;
	unsigned char ActiveMenu;
	Nokia5110LCD* m_pNokiaLCD;
};

























}

























#endif /* APP_INC_UI_HPP_ */
