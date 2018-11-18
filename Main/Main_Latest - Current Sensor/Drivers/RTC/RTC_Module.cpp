/******************
** FILE: RTC.cpp
**
** DESCRIPTION:
**  RTC functionality
**
** CREATED: 10/7/2018, by Amit Chaudhary
******************/

#include "RTC_Module.h"

#define BUILD_YEAR_CH0 (__DATE__[ 7])
#define BUILD_YEAR_CH1 (__DATE__[ 8])
#define BUILD_YEAR_CH2 (__DATE__[ 9])
#define BUILD_YEAR_CH3 (__DATE__[10])


#define BUILD_MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_FEB (__DATE__[0] == 'F')
#define BUILD_MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define BUILD_MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define BUILD_MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define BUILD_MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
#define BUILD_MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define BUILD_MONTH_IS_SEP (__DATE__[0] == 'S')
#define BUILD_MONTH_IS_OCT (__DATE__[0] == 'O')
#define BUILD_MONTH_IS_NOV (__DATE__[0] == 'N')
#define BUILD_MONTH_IS_DEC (__DATE__[0] == 'D')


#define BUILD_MONTH_CH0 \
    ((BUILD_MONTH_IS_OCT || BUILD_MONTH_IS_NOV || BUILD_MONTH_IS_DEC) ? '1' : '0')

#define BUILD_MONTH_CH1 \
    ( \
        (BUILD_MONTH_IS_JAN) ? '1' : \
        (BUILD_MONTH_IS_FEB) ? '2' : \
        (BUILD_MONTH_IS_MAR) ? '3' : \
        (BUILD_MONTH_IS_APR) ? '4' : \
        (BUILD_MONTH_IS_MAY) ? '5' : \
        (BUILD_MONTH_IS_JUN) ? '6' : \
        (BUILD_MONTH_IS_JUL) ? '7' : \
        (BUILD_MONTH_IS_AUG) ? '8' : \
        (BUILD_MONTH_IS_SEP) ? '9' : \
        (BUILD_MONTH_IS_OCT) ? '0' : \
        (BUILD_MONTH_IS_NOV) ? '1' : \
        (BUILD_MONTH_IS_DEC) ? '2' : \
        /* error default */    '?' \
    )

#define BUILD_DAY_CH0 ((__DATE__[4] >= '0') ? (__DATE__[4]) : '0')
#define BUILD_DAY_CH1 (__DATE__[ 5])



// Example of __TIME__ string: "21:06:19"
//                              01234567

#define BUILD_HOUR_CH0 (__TIME__[0])
#define BUILD_HOUR_CH1 (__TIME__[1])

#define BUILD_MIN_CH0 (__TIME__[3])
#define BUILD_MIN_CH1 (__TIME__[4])

#define BUILD_SEC_CH0 (__TIME__[6])
#define BUILD_SEC_CH1 (__TIME__[7])

namespace Peripherals
{

RTC_HandleTypeDef RTC_Module::hrtc;


RTC_Module::RTC_Module()
{
    
}
   
Status_t RTC_Module::HwInit()
{
  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef DateToUpdate;

    /* Initialize RTC Only */    
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM; //RTC_OUTPUTSOURCE_SECOND;// 
  
  HAL_PWR_EnableBkUpAccess();
  /* Enable BKP CLK enable for backup registers */
  __HAL_RCC_BKP_CLK_ENABLE();
  
  /* Peripheral clock enable */
  __HAL_RCC_RTC_ENABLE();
  
  //__HAL_RCC_RTC_CONFIG(RCC_RTCCLKSOURCE_LSE);
    
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
      return HAL_ERROR;
  }

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
      return HAL_ERROR;
  }


  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  {
      return HAL_ERROR;
  }

  InitDateAndTime();

  return HAL_OK;

}

void RTC_Module::InitDateAndTime()
{    
    RTC_Date_t RTC_Date;
    RTC_Time_t RTC_Time;
    
    RTC_Time.Seconds = (uint8_t)((BUILD_SEC_CH0 - '0')<<4 | (BUILD_SEC_CH1 - '0'));
    RTC_Time.Minutes = (uint8_t)((BUILD_MIN_CH0 - '0')<<4 | (BUILD_MIN_CH1 - '0'));
    RTC_Time.Hours   = (uint8_t)((BUILD_HOUR_CH0 - '0')<<4 | (BUILD_HOUR_CH1 - '0'));
    SetTime( &RTC_Time,RTC_FORMAT_BCD);
    

    RTC_Date.Month = (uint8_t)((BUILD_MONTH_CH0 - '0')<<4 | (BUILD_MONTH_CH1 - '0'));
    RTC_Date.Date  = (uint8_t)((BUILD_DAY_CH0 - '0')<<4 | (BUILD_DAY_CH1 - '0'));
    RTC_Date.Year  = (uint8_t)((BUILD_YEAR_CH2 - '0')<<4 | (BUILD_YEAR_CH3 - '0'));
    SetDate( &RTC_Date,RTC_FORMAT_BCD);
}

Status_t RTC_Module::HwDeinit()
{ 
    return HAL_RTC_DeInit(&hrtc);
}
 
Status_t RTC_Module::GetTime( RTC_Time_t* pRTC_Time, uint32_t Format )
{ 
    return HAL_RTC_GetTime(&hrtc, pRTC_Time, Format);
}
    
Status_t RTC_Module::SetTime( RTC_Time_t* pRTC_Time, uint32_t Format )
{ 
    return HAL_RTC_SetTime(&hrtc, pRTC_Time, Format);
} 
    
Status_t RTC_Module::GetDate( RTC_Date_t* pRTC_Date, uint32_t Format )
{ 
    return HAL_RTC_GetDate(&hrtc, pRTC_Date, Format);
}    

Status_t RTC_Module::SetDate( RTC_Date_t* pRTC_Date, uint32_t Format )
{ 
    return HAL_RTC_SetDate(&hrtc, pRTC_Date, Format);
}
 
Status_t RTC_Module::GetTime( char * pStr, uint32_t Format )
{ 
    Status_t Status;
    RTC_Time_t RTC_Time;
    
    if(pStr)
    {
        if ( (Status = HAL_RTC_GetTime(&hrtc, &RTC_Time, Format)) != HAL_OK )
        {
            return Status;
        }
        
        intToStr(RTC_Time.Hours, pStr, 2);
        pStr[2] = ':';
        intToStr(RTC_Time.Minutes, &pStr[3], 2);
        pStr[5] = ':';
        intToStr(RTC_Time.Seconds, &pStr[6], 2);         
    }
    
    return Status;
} 


Status_t RTC_Module::GetDate( char * pStr, uint32_t Format )
{ 
    Status_t Status;
    RTC_Date_t RTC_Date;
    const char Weekdays[][4] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    const char Months  [][4] = {"   ","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    
    if(pStr)
    {
        if ( (Status = GetDate(&RTC_Date, Format)) != HAL_OK )
        {
            return Status;
        }        
#if 1
        mem_cpy(&pStr[0],Weekdays[RTC_Date.WeekDay],3);
        pStr[3] = ',';
        intToStr(RTC_Date.Date, &pStr[4], 2);
        pStr[6] = ' ';
        mem_cpy(&pStr[7],Months[RTC_Date.Month],3);
        pStr[10] = ' ';
        intToStr(RTC_Date.Year, &pStr[11], 2);
#else
        mem_cpy(&pStr[0],Weekdays[RTC_Date.WeekDay],3);
        pStr[3] = ',';
        mem_cpy(&pStr[4],Months[RTC_Date.Month],3);
        pStr[7] = '-';
        intToStr(RTC_Date.Year, &pStr[8], 2);
#endif
    }
    
    return Status;
} 

uint32_t RTC_Module::GetTimeCounter()
{ 
    uint32_t Hi, Lo;
    Hi = RTC->CNTH & RTC_CNTH_RTC_CNT;
    Lo = RTC->CNTL & RTC_CNTL_RTC_CNT;
    return ( Hi<<16U | Lo );
}

void RTC_Module::SetTimeCounter(uint32_t Curent_Counter)
{ 
  /* Wait till RTC is in INIT state and if Time out is reached exit */
  while((RTC->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET);
  SET_BIT(RTC->CRL, RTC_CRL_CNF);

    
    RTC->CNTH  = Curent_Counter>>16;
    RTC->CNTL  = Curent_Counter & 0xFFFFU;
    
    CLEAR_BIT(RTC->CRL, RTC_CRL_CNF);
    while( (RTC->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET );
}

void RTC_Module::DateToStr(RTC_Date_t* Date, char* pStr)
{
    const char Weekdays[][4] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
    const char Months  [][4] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
          //char Year      [2];  
    
    if((pStr == nullptr) || ( Date == nullptr))
        return;
    
    
    
    mem_cpy(&pStr[0],Weekdays[Date->WeekDay],3);
    mem_cpy(&pStr[3],Months[Date->Month],3);
    intToStr(Date->Year, &pStr[6], 2);    
    
}


void RTC_Module::CounterToTime(char* pStr)
{
    uint8_t Hours,Minutes,Seconds;
    static uint32_t Initial_Count = GetTimeCounter();
    uint32_t counter_time = GetTimeCounter() - Initial_Count;
    
    Hours = counter_time / 3600U;
    Minutes  = (uint8_t)((counter_time % 3600U) / 60U);
    Seconds  = (uint8_t)((counter_time % 3600U) % 60U);
    
    intToStr(Hours, pStr, 2);
    pStr[2] = ':';
    intToStr(Minutes, &pStr[3], 2);
    pStr[5] = ':';
    intToStr(Seconds, &pStr[6], 2); 
    pStr[8] = '\0';
    
}
    

    
}