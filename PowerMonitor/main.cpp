
/* Includes */
#include<stddef.h>
#include<stdio.h>
#include<math.h>
#include"stm32f10x.h"
#include"Led.hpp"
#include"GpioOutput.hpp"
#include"GpioInput.hpp"
#include"HwButton.hpp"
#include"HwButtonIntr.hpp"
#include"SysTickTimer.hpp"
#include"SpiDriver.hpp"
#include"Nokia5110LCD.hpp"
#include"UI.hpp"
#include"Line.hpp"
#include"Menu.hpp"
#include"I2CDriver.hpp"
#include"INA219.hpp"
#include"I2c.hpp"

using namespace Bsp;
using namespace App;

void reverse(char *str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char *res, int afterpoint);


static void prvSetupHardware( void );
void ClickEvent(void);
void LongPressEvent(void);
void LongLongPressEvent(void);

void Led_PC13BlinkTwice(void);
void Led_PC13BlinkOnce(void);
void Led_PC13Toggle(void);

void Line0Menu0LongLongTouchHandler();
void Line0Menu0LongTouchHandler();


Bsp::HwButtonIntr HwButton_A2(GPIOA, GPIO_Pin_3,Bsp::GpioInput::EXTI_Trigger_Rising, Bsp::GpioInput::EXTI_Mode_Interrupt);

static Led Led_PC13(GPIOC,GPIO_Pin_13);
static Led Led_PC14(GPIOC,GPIO_Pin_14);


Nokia5110LCD NokiaLCD(SpiDriver::SPI_1_A7_A6_A5_A4,
		              GPIOB,GPIO_Pin_0, // Reset Pin on B0
					  GPIOB,GPIO_Pin_1,	// Data/Command Pin on B1
					  GPIOB,GPIO_Pin_10	// Backlight Pin on B10
					  );
I2CDriver INA219_I2C(I2CDriver::I2C1_B6_B7, nullptr, I2CDriver::Master, I2CDriver::BaudRate_100000 ); // I2C1_B6_B7
INA219 INA219_Obj(&INA219_I2C,0x80);

UI MyUI(&NokiaLCD);
Menu::Event_t gEvent = Menu::MaxEvents;
char aPower[6][12];

uint8_t aCurrent[9];
uint8_t aVoltage[9];
float BusVoltage = 0.00;
int main(void)
{
    prvSetupHardware();
    
    Line Line1("Live Power",Led_PC13BlinkOnce,Line0Menu0LongTouchHandler,Line0Menu0LongLongTouchHandler);
    static INA219::Power_t Power;
    Menu MyMenu;

    MyMenu.AddLine(Line1,0);

  // Start SysTick Timer for 1ms (1000 us) tick resolution
  SysTickTimer::HwInit(1000UL);

  HwButton_A2.HwInit();
  INA219_I2C.HwInit();
  INA219_Obj.SetCalibration_32V_2A();
  HwButton_A2.RegisterEventHandler(Bsp::HwButtonIntr::Click,static_cast<Bsp::HwButtonIntr::BtnHandler>(ClickEvent));
  HwButton_A2.RegisterEventHandler(Bsp::HwButtonIntr::LongPress,static_cast<Bsp::HwButtonIntr::BtnHandler>(LongPressEvent));
  HwButton_A2.RegisterEventHandler(Bsp::HwButtonIntr::LongLongPress,static_cast<Bsp::HwButtonIntr::BtnHandler>(LongLongPressEvent));
  MyUI.Init();
  MyUI.AddMenu(MyMenu,0);  
  INA219_I2C.HwInit();
  while(1)
  {
    HwButton_A2.RunStateMachine();
    MyUI.EventHamdler(gEvent);
    MyUI.Run();
    INA219_Obj.Run(&Power); 
    ftoa(Power.Voltage, (char*)aVoltage, 6);
    ftoa(Power.Current, (char*)aCurrent, 6);
    MyUI.SetMenuLineTest(0,1,0,"V = ");
    MyUI.SetMenuLineTest(0,1,4,(char*)aVoltage);
    MyUI.SetMenuLineTest(0,2,0,"I = ");
    MyUI.SetMenuLineTest(0,2,4,(char*)aCurrent);
    ftoa(Power.Power, (char*)aCurrent, 6);
    MyUI.SetMenuLineTest(0,3,0,"P = ");
    MyUI.SetMenuLineTest(0,3,4,(char*)aCurrent);
  }

}

void ClickEvent(void)
{
	gEvent = Menu::Touch;
}
void LongPressEvent(void)
{
	gEvent = Menu::LongTouch;
}
void LongLongPressEvent(void)
{
	gEvent = Menu::LongLongTouch;
}


void Line0Menu0LongTouchHandler()
{
	MyUI.SetMenuLineTest(0,0,7,"   HI");
}

void Line0Menu0LongLongTouchHandler()
{
	MyUI.SetMenuLineTest(0,0,7,"  BYE");
}

void Line1Menu0LongTouchHandler()
{
	MyUI.SetMenuLineTest(0,1,5,"     ON");
}

void Line1Menu0LongLongTouchHandler()
{
	MyUI.SetMenuLineTest(0,1,5,"    OFF");
}

void Line2Menu0LongTouchHandler()
{
	MyUI.SetMenuLineTest(0,2,8,"  ON");
}

void Line2Menu0LongLongTouchHandler()
{
	MyUI.SetMenuLineTest(0,2,8," OFF");
}

void Line3Menu0LongTouchHandler()
{
	MyUI.SetMenuLineTest(0,3,5,"     ON");
}

void Line3Menu0LongLongTouchHandler()
{
	MyUI.SetMenuLineTest(0,3,5,"    OFF");
}
void Line4Menu0LongTouchHandler()
{
	MyUI.SetMenuLineTest(0,4,6,"    ON");
}

void Line4Menu0LongLongTouchHandler()
{
	MyUI.SetMenuLineTest(0,4,6,"   OFF");
}

void Line5Menu0LongTouchHandler()
{
	MyUI.SetMenuLineTest(0,5,8,"  ON");
	MyUI.SetActiveMenu(0);
}

void Line5Menu0LongLongTouchHandler()
{
	MyUI.SetMenuLineTest(0,5,8," OFF");
	MyUI.SetActiveMenu(1);
}

void Led_PC13Toggle(void)
{
	Led_PC13.Toggle();
}
void Led_PC13BlinkOnce(void)
{
	Led_PC13.Toggle();
	SysTickTimer::DelayTicks(100);
	Led_PC13.Toggle();
}
void Led_PC13BlinkTwice(void)
{
	Led_PC13.Toggle();
	SysTickTimer::DelayTicks(100);
	Led_PC13.Toggle();
	SysTickTimer::DelayTicks(100);
	Led_PC13.Toggle();
	SysTickTimer::DelayTicks(100);
	Led_PC13.Toggle();

}

static void prvSetupHardware( void )
{
	/* Start with the clocks in their expected state. */
	RCC_DeInit();

	/* Enable HSE (high speed external clock). */
	RCC_HSEConfig( RCC_HSE_ON );

	/* Wait till HSE is ready. */
	while( RCC_GetFlagStatus( RCC_FLAG_HSERDY ) == RESET )
	{
	}

	/* 2 wait states required on the flash. */
	*( ( unsigned long * ) 0x40022000 ) = 0x02;

	/* HCLK = SYSCLK */
	RCC_HCLKConfig( RCC_SYSCLK_Div1 );

	/* PCLK2 = HCLK */
	RCC_PCLK2Config( RCC_HCLK_Div1 );

	/* PCLK1 = HCLK/2 */
	RCC_PCLK1Config( RCC_HCLK_Div2 );

	/* PLLCLK = 8MHz * 9 = 72 MHz. */
	RCC_PLLConfig( RCC_PLLSource_HSE_Div1, RCC_PLLMul_9 );

	/* Enable PLL. */
	RCC_PLLCmd( ENABLE );

	/* Wait till PLL is ready. */
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
	{
	}

	/* Select PLL as system clock source. */
	RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK );

	/* Wait till PLL is used as system clock source. */
	while( RCC_GetSYSCLKSource() != 0x08 )
	{
	}

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );

	/* Set the Vector Table base address at 0x08000000 */
	NVIC_SetVectorTable( NVIC_VectTab_FLASH, 0x0 );

	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

	/* Configure HCLK clock as SysTick clock source. */
	SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK );

}

// reverses a string 'str' of length 'len'

void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}
 
 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }
 
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
 
    reverse(str, i);
    str[i] = '\0';
    return i;
}
// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
 
    // Extract floating part
    float fpart = n - (float)ipart;
 
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
 
    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot
 
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10.0, afterpoint);
 
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}