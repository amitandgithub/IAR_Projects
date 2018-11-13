/******************
** FILE: RTC.cpp
**
** DESCRIPTION:
**  RTC functionality
**
** CREATED: 10/7/2018, by Amit Chaudhary
******************/

#include "RTC_Module.h"

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
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  
  HAL_PWR_EnableBkUpAccess();
  /* Enable BKP CLK enable for backup registers */
  __HAL_RCC_BKP_CLK_ENABLE();
  /* Peripheral clock enable */
  __HAL_RCC_RTC_ENABLE();
    
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
   // _Error_Handler(__FILE__, __LINE__);
      return HAL_ERROR;
  }

    /**Initialize RTC and set the Time and Date 
    */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
      return HAL_ERROR;
  }
  /* USER CODE BEGIN RTC_Init 3 */

  /* USER CODE END RTC_Init 3 */

  DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
  DateToUpdate.Month = RTC_MONTH_JANUARY;
  DateToUpdate.Date = 0x1;
  DateToUpdate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  {
   // _Error_Handler(__FILE__, __LINE__);
      return HAL_ERROR;
  }


  return HAL_OK;

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
    const char Weekdays[][4] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
    const char Months  [][4] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    //char Year            [2]; 
    
    if(pStr)
    {
        if ( (Status = GetDate(&RTC_Date, Format)) != HAL_OK )
        {
            return Status;
        }
        
        
        
        mem_cpy(&pStr[0],Weekdays[RTC_Date.WeekDay],3);
        pStr[3] = ',';
        mem_cpy(&pStr[4],Months[RTC_Date.Month],3);
        pStr[7] = '-';
        intToStr(RTC_Date.Year, &pStr[8], 2);
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
//RTC_Module::RTC_Time_t  RTC_Time1;
//RTC_Module::RTC_Date_t  RTC_Date1;
//void RTC_Module::SetCurrentDateAmdTime()
//{
//    //"Jul 27 2012"
//    //21:06:19    
//    const char Weekdays[][4] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
//    const char Months  [][4] = {"   ","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
//
//   
//   RTC_Time1.Seconds   = a2d(__TIME__[1]) + a2d(__TIME__[0]); 
//   RTC_Time1.Minutes  = a2d(__TIME__[3]) + a2d(__TIME__[4]); 
//   RTC_Time1.Hours    = a2d(__TIME__[6]) + a2d(__TIME__[7]); 
//   SetTime(&RTC_Time1);
//   for(uint32_t i = 0; i<7; i++)
//   {
//      
//   }
//   //mem_cmp()
//   
//    
//}
//    
    
    
}