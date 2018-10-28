/*
 * UI.hpp
 *
 *  Created on: 01-Nov-2017
 *      Author: Amit Chaudhary
 *  13-Oct-2018 : Modified for the New version based upon STM32_HAL
 */

#ifndef APP_INC_UI_HPP_
#define APP_INC_UI_HPP_

#include"Nokia5110LCD.h"
#include <cstring>
#include "Screen.h"

namespace Peripherals
{


class UI
{
public:
	const static unsigned char NO_OF_MENUS_IN_UI = 10U;
    constexpr static unsigned char NO_OF_SCREENS_IN_UI = 10U;
    typedef uint8_t ScreenHandle_t;

	UI(Nokia5110LCD* pNokiaLCD);
	~UI(){};
	bool Init();        
        inline ScreenHandle_t AddScreen(Screen* pScreen ){m_Screens[TotalAddeedScreens%NO_OF_SCREENS_IN_UI] = pScreen; return TotalAddeedScreens++;}// ++TotalRegisteredScreens %= NO_OF_SCREENS_IN_UI ;}
        inline void AddScreen(Screen* pScreen, unsigned char Slot ){m_Screens[Slot%NO_OF_SCREENS_IN_UI] = pScreen; TotalAddeedScreens++;}// ++TotalRegisteredScreens %= NO_OF_SCREENS_IN_UI;}
        inline static void GoToPreviousScreen(){SetActiveScreen(PreviousActiveScreen);  }
        inline static void GoToNextScreen(){ PreviousActiveScreen = ActiveScreen; ++ActiveScreen %= TotalRegisteredScreens ; }
        inline static ScreenHandle_t GetActiveScreen(){return ActiveScreen; }
        inline static void SetActiveScreen(ScreenHandle_t ScreenNo){ PreviousActiveScreen = ActiveScreen; ActiveScreen = ScreenNo; }
        void DisplayScreen();//{ if(m_aScreens[ActiveScreen % NO_OF_SCREENS_IN_UI]) m_pNokiaLCD->DrawBuffer( m_aScreens[ActiveScreen % NO_OF_SCREENS_IN_UI]->GetScreenTextArray() );}
       	inline void Run(){DisplayScreen();}
        void EventHamdler(Screen::Event_t& rEvent);

private:
        Screen* m_Screens[NO_OF_SCREENS_IN_UI];
        static ScreenHandle_t ActiveScreen;
        static unsigned char PreviousActiveScreen;
        static unsigned char TotalRegisteredScreens;
        unsigned char TotalAddeedScreens;
        Nokia5110LCD* LCD;
};

























}

























#endif /* APP_INC_UI_HPP_ */
