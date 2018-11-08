
 
    
#include<cstdint>
#include <stddef.h>
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "I2C_Master.hpp"
#include "I2C_Slave.hpp"
#include <INA219.h>
#include "GpioOutput.hpp"
#include "GpioInput.hpp"
#include "SPI_Poll.h"
#include "SPI_IT.h"
#include "SPI_DMA.h"
#include "Nokia5110LCD.h"
#include "Queue.h"
#include "HwButton.h"
#include "HwButtonIntr.h"
#include "RTC_Module.h"
#include "Utils.h"
#include "printf.h"
#include "UI.h"
#include "DisplayBuffer.h"
#include "Screen.h"
#include "ControlScreen.h"
#include "SD.h"
#include "ff.h"	

using namespace Peripherals;

namespace App
{
   
void Init_Power_Monitor();
void Run_Power_Monitor();
void Init_Current_Sensor();
void Run_Current_Sensor();
void Init_Display();
void Init_HwButton();
void HwButton_ClickEvent();
void HwButton_LongPressEvent();
void HwButton_LongLongPressEvent();
void Run_HwButton();
void ScreenTouchHandler();
void ScreenLongTouchHandler();
bool Save_To_SD_Card(char* pData, uint32_t len);
void mem_cpy (void* dst, const void* src, UINT cnt) ;


}