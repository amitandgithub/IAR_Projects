

#include"Power_Monitor.h"

namespace App
{

    
/* Globals for Current Sensor task*/
#define INA219_ADDR 0x80U
INA219::Power_t Power;
char PowerStr[25];

Peripherals::I2C_Master I2C1_Master(I2C_Master::I2C1_SCL_B6_SDA_B7);
INA219 INA219_Obj(&I2C1_Master,INA219_ADDR);


/* Globals for Nokia LCD task*/
#define LCD_SPI_FREQ 9000000
Peripherals::GpioOutput      CS(GPIOA,GPIO_PIN_4);
Peripherals::SPI_DMA         SPI_Obj(Peripherals::SPI_Base::SPI1_A4_A5_A6_A7,&CS,LCD_SPI_FREQ );
Peripherals::GpioOutput      D_C(GPIOB,GPIO_PIN_1);
Peripherals::GpioOutput      Backlight(GPIOA,GPIO_PIN_1);
Peripherals::GpioOutput      Reset(GPIOB,GPIO_PIN_0);
Peripherals::Nokia5110LCD    LCD(&SPI_Obj,&CS,&D_C,&Reset,&Backlight);



/* Globals for Touch Button task*/
Peripherals::HwButton HwButton_A8(GPIOA, GPIO_PIN_8);
Peripherals::GpioOutput LED(GPIOC, GPIO_PIN_13);

/* Globals for UI task*/
Screen::Event_t gEvent = Screen::MaxEvents;
Peripherals::UI MyUI(&LCD);


/* Globals for RTC task*/
Peripherals::RTC_Module rtc;
char TimeStr[15];

#ifdef SD_CARD
/* Globals for SD_CARD task*/
#define SD_CARD_SAVE_FREQ 100
Peripherals::GpioOutput CS2(GPIOB,GPIO_PIN_12,Peripherals::GpioOutput::AF_PP, Peripherals::GpioOutput::HIGH, Peripherals::GpioOutput::PULL_UP);
Peripherals::SPI_Poll SPI2_Obj(Peripherals::SPI_Poll::SPI2_B12_B13_B14_B15, &CS2, 25000000);    
SD SD_Card(&SPI2_Obj,&CS2);
FATFS fs;
FIL fil;
FRESULT fr;
char FileName[26];
#endif

Screen HomeScreen( (char *)
                   "Tue 06-Nov-18 "
                   "T = 00:00:00  "
                   "I =           "
                   "V =           "
                   "C =           "
                   "P =           "
                   );
ControlScreen Menu( (char *)
                   "Live Power    "
                   "Reset         "
                   "SD Card       "
                   "SD Save       "
                   "Back Light Off"
                   "              "
                   );

void Init_Power_Monitor()
{        

    rtc.HwInit();
    LED.HwInit();
    HwButton_A8.HwInit();
    HwButton_A8.RegisterEventHandler(HwButton::Click,HwButton_ClickEvent);
    HwButton_A8.RegisterEventHandler(HwButton::LongPress,HwButton_LongPressEvent);
    HwButton_A8.RegisterEventHandler(HwButton::LongLongPress,HwButton_LongLongPressEvent); 
    
    INA219_Obj.HwInit(); 
    INA219_Obj.SetCalibration_32V_2A();
    
    MyUI.Init();
    MyUI.AddScreen(&HomeScreen);
    HomeScreen.SetScreenHandler(ScreenTouchHandler,Reset_ScreenTouchHandler,nullptr);
    MyUI.AddScreen(&Menu);
    Menu.SetScreenHandler(ScreenTouchHandler,ScreenLongTouchHandler,nullptr);
    Menu.AddHandler( 0, LivePower_ScreenTouchHandler,   nullptr);
    Menu.AddHandler( 1, Reset_ScreenTouchHandler,       nullptr);
    Menu.AddHandler( 2, SD_CARD_ScreenTouchHandler,     nullptr);
    Menu.AddHandler( 3, SD_Save_ScreenTouchHandler,     nullptr);
    Menu.AddHandler( 4, BackLight_ScreenTouchHandler,   nullptr);
    
    
#ifdef SD_CARD
    SD_Card.HwInit();
    
    mem_cpy(&FileName[0], "Power", 5);
    FileName[5] = '_';
    FileName[6] = __DATE__[0];
    FileName[7] = __DATE__[1];
    FileName[8] = __DATE__[2];
    FileName[9] = '_';
    FileName[10] = __DATE__[4];
    FileName[11] = __DATE__[5];
    FileName[12] = '_';
    FileName[13] = __TIME__[0];
    FileName[14] = __TIME__[1];
    FileName[15] = '_';
    FileName[16] = __TIME__[3];
    FileName[17] = __TIME__[4];
    FileName[18] = '_';
    FileName[19] = __TIME__[6];
    FileName[20] = __TIME__[7];  
    FileName[21] = '.';
    FileName[22] = 't';
    FileName[23] = 'x';
    FileName[24] = 't';
    FileName[25] = 0;
#endif   
}
uint32_t Ticks;
uint32_t Power_PrevTicks, I_Count;
float I_Samples,V_Samples,mWH,mAH;
void Run_Power_Monitor()
{    
    int len_I,len_V,len_C,len_W;
    Ticks = HAL_GetTick();
    
    rtc.GetDate(TimeStr);
    HomeScreen.DrawStr(DATE_ROW,0,TimeStr);
    
    rtc.CounterToTime(TimeStr);
    HomeScreen.DrawStr(TIMER_ROW,4,TimeStr);
    
    HwButton_A8.RunStateMachine();
    

    if(Time_Elapsed(POWER_SAMPLE_FREQ, Ticks, &Power_PrevTicks) == true)
    {                
        INA219_Obj.Run(&Power);
        I_Count++;
        
        I_Samples = I_Samples + Power.Current;
        V_Samples = V_Samples + Power.Voltage;
        
        if(I_Count >= (1000/POWER_SAMPLE_FREQ))
        {
            I_Count = 0;           
            
            I_Samples = (I_Samples*POWER_SAMPLE_FREQ)/1000.0;
            V_Samples = (V_Samples*POWER_SAMPLE_FREQ)/1000.0;
            
            mAH += I_Samples / 3600.0;
            
            mWH = mAH*V_Samples/1000.0;
            
            I_Samples = 0;
            V_Samples = 0;
        }
    }
    
    len_I = ftoa(Power.Current, &PowerStr[0], 2);
    HomeScreen.DrawStr(I_ROW,4,&PowerStr[0]);
    HomeScreen.DrawStr(I_ROW, 4 + len_I, "mA");
    PowerStr[len_I++] = ',';
    
    len_V = ftoa(Power.Voltage, &PowerStr[len_I], 2);
    HomeScreen.DrawStr(V_ROW,4,&PowerStr[len_I]);
    HomeScreen.DrawChar(V_ROW, 4 + len_V, 'V');
    PowerStr[len_I + len_V++] = ',';
    
    len_C = ftoa(mAH, &PowerStr[len_I + len_V], 2);
    HomeScreen.DrawStr(C_ROW,4,&PowerStr[len_I + len_V]);
    HomeScreen.DrawStr(C_ROW, 4 + len_C, "mAH");    
    PowerStr[len_I + len_V + len_C++] = ',';
    
    len_W = ftoa(mWH, &PowerStr[len_I + len_V + len_C], 2);
    HomeScreen.DrawStr(W_ROW,4,&PowerStr[len_I + len_V + len_C]);
    HomeScreen.DrawStr(W_ROW, 4 + len_W, "WH");    
    PowerStr[len_I + len_V + len_C + len_W++] = '\n';
 
    MyUI.EventHamdler(gEvent);
    
    MyUI.Run();
    
#ifdef SD_CARD
    Save_To_SD_Card(FileName,&PowerStr[0],len_I + len_V + len_C + len_W);
#endif
}


void HwButton_ClickEvent()
{
    gEvent = Screen::Touch;
}

void HwButton_LongPressEvent()
{
    gEvent = Screen::LongTouch;
}

void HwButton_LongLongPressEvent()
{
    gEvent = Screen::LongLongTouch;
}

void ScreenTouchHandler()
{
	Peripherals::UI::GoToNextScreen();
}

void ScreenLongTouchHandler()
{
	Peripherals::UI::GoToPreviousScreen();
}

void LivePower_ScreenTouchHandler()
{
	Peripherals::UI::GoToScreen(&HomeScreen);
}

void Reset_ScreenTouchHandler()
{
	Reset_Power_Readings();
}
void SD_CARD_ScreenTouchHandler()
{
	
}
void SD_Save_ScreenTouchHandler()
{
	
}
void BackLight_ScreenTouchHandler()
{
    if(LCD.GetBackLightState())
    {
        LCD.BackLightOFF();
        Menu.DrawStr(BACK_LIGHT_ROW,11,"OFF",3,0x0D);
    }
    else
    {
        LCD.BackLightON();
        Menu.DrawStr(BACK_LIGHT_ROW,11,"ON ",3,0x0D);
    }
}


void Reset_Power_Readings()
{
    mAH = 0;
    mWH = 0;
    rtc.HwInit();    
}

#ifdef SD_CARD

bool Save_To_SD_Card(const char* FileName, char* pData, uint32_t len)
{ 
#ifndef SD_CARD_SAVE_FREQ_MAX
    
    static uint32_t Previous_Ticks;
    uint32_t Current_Ticks = HAL_GetTick()  ;
    
    if( Current_Ticks < Previous_Ticks + SD_CARD_SAVE_FREQ ) 
        return false;
    
    Previous_Ticks = Current_Ticks;
#endif
    
    if(pData == nullptr)
        return false;
    
    // Mark the end of the string to be saved on SD card
    pData[len] = '\0';
    
    fr = SD_Card.mount(&fs, "", 1); // 1861648
	if (fr != FR_OK) 
	{
		return false;
	}
    fr = SD_Card.open(&fil, FileName, FA_WRITE | FA_OPEN_ALWAYS);
    if (fr == FR_OK) 
	{
		/* Seek to end of the file to append data */
		fr = f_lseek(&fil, f_size(&fil)); 
        
		if (fr != FR_OK) SD_Card.close(&fil);
                    
		SD_Card.print(&fil,pData);
        
		SD_Card.close(&fil); // 1143384

		
		fr = SD_Card.mount(0, "", 0); // 117
		if (fr != FR_OK) 
		{
			return false;
		}
        return true;
    }
    return false;
    
    
}
#endif

bool Time_Elapsed(uint32_t Freq, uint32_t CurrentTicks,uint32_t *pPreviousTicks)
{
    if(CurrentTicks > Freq + *pPreviousTicks)
    {
        *pPreviousTicks = CurrentTicks;
        return true;
    }    
    return false;
}


}
