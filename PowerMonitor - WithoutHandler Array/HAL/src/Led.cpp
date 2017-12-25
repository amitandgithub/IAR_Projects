

#include "stm32f10x.h"
#include "Led.hpp"


Led::Led(PORT Port, u16 Pin):Bsp::GpioOutput(Port, Pin)
{

	HwInit();
}

void Led::On(void)
{
	//GPIO_WriteBit(GPIOC, GPIO_Pin_13,Bit_RESET);
	SetOutput();
	Led_State = ON;
}

void Led::Off(void)
{
	//GPIO_WriteBit(GPIOC, GPIO_Pin_13,Bit_SET);
	ClearOutput();
	Led_State = OFF;
}

void Led::Blink(unsigned int delay)
{
	volatile unsigned int i;
	for(i=0;i<delay;i++);
	ToggleOutput();
}
void Led::Blink(unsigned int on,unsigned int off)
{
	volatile unsigned int i;
	for(i=0;i<off;i++);
	ToggleOutput();
	for(i=0;i<on;i++);
	ToggleOutput();
}




