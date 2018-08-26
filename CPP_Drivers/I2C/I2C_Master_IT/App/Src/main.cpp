
/* Includes */
#include <stddef.h>
#include <stdio.h>

#include "stm32f1xx_hal.h"
#include "I2C_Master.hpp"
#include "I2C_Master_IT.hpp"
#include <INA219.hpp>

#include "GpioOutput.hpp"
#include "GpioInput.hpp"

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

void I2c_RxCallback();
void I2c_TxCallback();
using namespace Peripherals;
void SystemClock_Config(void);

Peripherals::GpioOutput A1(GPIOA,GPIO_PIN_1);



Peripherals::I2C_Master_IT I2C1_Master(I2C_Master_IT::I2C1_SCL_B6_SDA_B7);

INA219 INA219_Obj(&I2C1_Master, 0x80);
INA219::Power_t Power;

uint8_t array[] = "Amit";
uint8_t array1[10];
float V;
int main(void)
{	
    volatile uint32_t status;
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  A1.HwInit();
  /* Configure the system clock */
  SystemClock_Config();
  I2C1_Master.HwInit();
  I2C1_Master.m_RxCallback = I2c_RxCallback;
  I2C1_Master.m_TxCallback = I2c_TxCallback;
  
  INA219_Obj.SetCalibration_32V_2A();

 // I2C1_Master.Reset();
  while(1)
  {
#if 0
      while(I2C1_Master.Send(0x28,array,4, I2C_FIRST_FRAME) != HAL_OK);
     // I2C1_Master.Send(0x28,array,1, I2C_FIRST_FRAME);
     // HAL_Delay(50); 
      
      while(I2C1_Master.GetState() != HAL_I2C_STATE_READY);
      
      while(I2C1_Master.Read(0x28,array1,9, I2C_LAST_FRAME)!= HAL_OK);
      //I2C1_Master.Read(0x28,array1,3, I2C_LAST_FRAME);
     // HAL_Delay(50);
      
      while(I2C1_Master.GetState() != HAL_I2C_STATE_READY);
#elif 0
      I2C1_Master.Xfer(0x28,array,4,array1,9);      
      HAL_Delay(50); 
      while(I2C1_Master.GetState() != HAL_I2C_STATE_READY);
      
#elif 1
      while(1)
      {
        INA219_Obj.Run(&Power);
         // V = INA219_Obj.GetBusVoltage_V();
        //HAL_Delay(1);
        //A1.ToggleOutput();
      }
  #endif        
  }
 

}
void I2c_RxCallback()
{
    //Peripherals::I2C_Master_IT::m_RxDone =  Peripherals::I2C_Master_IT::DONE;
    
}


void I2c_TxCallback()
{
    //Peripherals::I2C_Master_IT::m_TxDone =  Peripherals::I2C_Master_IT::DONE;
    //A1.ToggleOutput();
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler((char*)__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler((char*)__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
