
 
    
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
#include "Utils.h"	
#include <chrono>
#include <ctime>

using namespace Peripherals;
using namespace std;
namespace App
{
    
//#define SD_CARD
    
#define POWER_SAMPLE_FREQ 250
    
#define DATE_ROW  0   
#define TIMER_ROW 1
#define I_ROW 2
#define V_ROW 3
#define C_ROW 4
#define W_ROW 5

#define TIMER_ROW 1
#define TIMER_COL 1

#define CURRENT_DISPLAY_FREQ    1000
#define CURRENT_SAMPLING_FREQ   10
#define VOLTAGE_DISPLAY_FREQ    250  
    
#define LIVE_POWER_ROW      0
#define RESET_ROW           1    
#define SD_CARD_ROW         2
#define SD_CARD_SAVE_ROW    3    
#define BACK_LIGHT_ROW      4

    
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
bool Save_To_SD_Card(const char* FileName, char* pData, uint32_t len);
void LivePower_ScreenTouchHandler();
void Reset_ScreenTouchHandler();
void SD_CARD_ScreenTouchHandler();
void SD_Save_ScreenTouchHandler();
void BackLight_ScreenTouchHandler();
void Reset_Power_Readings();
bool Time_Elapsed(uint32_t Freq, uint32_t CurrentTicks,uint32_t *pPreviousTicks);

}