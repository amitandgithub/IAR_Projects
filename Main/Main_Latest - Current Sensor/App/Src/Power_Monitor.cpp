

#include"Power_Monitor.h"

namespace App
{

#define TIMER_ROW 1

#define I_ROW 2
#define V_ROW 3
#define C_ROW 4
#define P_ROW 5

#define TIMER_ROW 1
#define TIMER_COL 1

#define CURRENT_DISPLAY_FREQ    1000
#define CURRENT_SAMPLING_FREQ   10
#define VOLTAGE_DISPLAY_FREQ    250   
    
    
/* Globals for Current Sensor task*/
#define INA219_ADDR 0x80U
INA219::Power_t Power;
char PowerStr[20];

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

/* Globals for UI task*/
Screen::Event_t gEvent = Screen::MaxEvents;
Peripherals::UI MyUI(&LCD);


/* Globals for RTC task*/
Peripherals::RTC_Module rtc;
char TimeStr[10];


/* Globals for RTC task*/
Peripherals::GpioOutput CS2(GPIOB,GPIO_PIN_12,Peripherals::GpioOutput::AF_PP, Peripherals::GpioOutput::HIGH, Peripherals::GpioOutput::PULL_UP);
Peripherals::SPI_Poll SPI2_Obj(Peripherals::SPI_Poll::SPI2_B12_B13_B14_B15, &CS2, 25000000);    
SD SD_Card(&SPI2_Obj,&CS2);
FATFS fs;
FIL fil;
FRESULT fr;

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
    HwButton_A8.HwInit();
    HwButton_A8.RegisterEventHandler(HwButton::Click,HwButton_ClickEvent);
    HwButton_A8.RegisterEventHandler(HwButton::LongPress,HwButton_LongPressEvent);
    HwButton_A8.RegisterEventHandler(HwButton::LongLongPress,HwButton_LongLongPressEvent); 
    
    INA219_Obj.HwInit(); 
    
    MyUI.Init();
    MyUI.AddScreen(&HomeScreen);
    MyUI.AddScreen(&Menu);
    Menu.SetScreenHandler(ScreenTouchHandler,ScreenLongTouchHandler,nullptr);
    rtc.HwInit();
    SD_Card.HwInit();
    
    
    
}
uint32_t Ticks;
float Sampled_Current;
void Run_Power_Monitor()
{    
    volatile int len_I,len_V;
    
    Ticks = HAL_GetTick();
    
    rtc.GetTime(TimeStr);
    HomeScreen.DrawStr(TIMER_ROW,4,TimeStr);
    
    HwButton_A8.RunStateMachine();
    
    INA219_Obj.Run(&Power);     
    
    len_I = ftoa(Power.Current, &PowerStr[0], 2);
    HomeScreen.DrawStr(I_ROW,4,&PowerStr[0]);

    PowerStr[len_I++] = ',';
    
    len_V = ftoa(Power.Voltage, &PowerStr[len_I], 2);
    HomeScreen.DrawStr(V_ROW,4,&PowerStr[len_I]);
    PowerStr[len_I + len_V] = '\n';
    len_V++;
    MyUI.EventHamdler(gEvent);
    
    MyUI.Run();
    
//    PowerStr[18]= '\n';
//    PowerStr[19]= '\0';
    Save_To_SD_Card(&PowerStr[0],len_I + len_V);
    
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

bool Save_To_SD_Card(char* pData, uint32_t len)
{ 
    if(pData == nullptr)
        return false;
    
    pData[len] = '\0';
    fr = SD_Card.mount(&fs, "", 1); // 1861648
	if (fr != FR_OK) 
	{
		return false;
	}
    fr = SD_Card.open(&fil, "Power_2.txt", FA_WRITE | FA_OPEN_ALWAYS);
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


void mem_cpy (void* dst, const void* src, UINT cnt) 
{
	BYTE *d = (BYTE*)dst;
	const BYTE *s = (const BYTE*)src;

#if _WORD_ACCESS == 1
	while (cnt >= sizeof (int)) {
		*(int*)d = *(int*)s;
		d += sizeof (int); s += sizeof (int);
		cnt -= sizeof (int);
	}
#endif
	while (cnt--)
		*d++ = *s++;
}

}
