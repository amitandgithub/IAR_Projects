

#include <stddef.h>
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "I2C_Master.hpp"
#include "I2C_Slave.hpp"
#include <INA219.hpp>
#include "GpioOutput.hpp"
#include "GpioInput.hpp"
#include "SPI_Poll.h"

extern void GpioTest();
extern void I2C_Master_Test();
extern void I2C_Slave_Test();
extern void INA219_Test();
extern void SPI_Poll_Test();