

#include <stddef.h>
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "I2C_Master.hpp"
#include "I2C_Slave.hpp"
#include <INA219.hpp>
#include "GpioOutput.hpp"
#include "GpioInput.hpp"
#include "SPI_Poll.h"
#include "SPI_IT.h"
#include "SPI_DMA.h"
#include "Nokia5110LCD.hpp"
#include "Queue.h"

extern void GpioTest();
extern void I2C_Master_Test();
extern void I2C_Slave_Test();
extern void INA219_Test();
extern void SPI_Poll_Test();
extern void SPI_Int_Test();
extern void SPI1_DMA_Test();
extern void SPI2_DMA_Test();
extern void SPI1_DMA_Tx_Complete_Callback();
extern void SPI2_DMA_Tx_Complete_Callback();
extern void Nokia5110LCD_SPI1_Test();
extern void Nokia5110LCD_SPI2_Test(); 
extern void Nokia5110LCD_Dual_Test();
extern void Queue_Test();