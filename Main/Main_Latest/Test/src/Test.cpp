


#include"Test.h"

using namespace Peripherals;

void GpioTest()
{
    Peripherals::GpioOutput LED(GPIOC,GPIO_PIN_13);
    LED.HwInit();
    while(1)
    {
        LED.ToggleOutput();
        HAL_Delay(100);
    }
}

void I2C_Master_Test()
{
    static uint16_t I2C_array[120];
    static uint8_t array[] = "Amit";
    static uint8_t array1[10];
    Peripherals::I2C_Master I2C1_Master(I2C_Master::I2C1_SCL_B6_SDA_B7);
    I2C1_Master.HwInit();
    
    while(1)
    {
        I2C1_Master.Scan(I2C_array,120);
        
        while(I2C1_Master.Send(0x28,array,4) != HAL_OK);
        
        while(I2C1_Master.GetState() != HAL_I2C_STATE_READY);
        
        while(I2C1_Master.Read(0x28,array1,9) != HAL_OK);
        
        HAL_Delay(10);
    }
}

void I2C_Slave_Test()
{
    uint8_t array[] = "Amit Chaudhary";
    uint8_t array1[10];
    static I2C_Slave I2C1_Slave(I2C_Slave::I2C1_SCL_B6_SDA_B7);
    I2C1_Slave.HwInit();
    
    //I2C1_Slave.m_RxCallback = I2c_RxCallback;
    //I2C1_Slave.m_TxCallback = I2c_TxCallback;
    
    while(1)
    {
        
        //I2C1_Slave.StartListening();
        while(I2C1_Slave.Read(array1,4,I2C_FIRST_FRAME) != HAL_OK);
        //I2C1_Slave.Read(array1,1,I2C_FIRST_FRAME);
        while(I2C1_Slave.GetState() != HAL_I2C_STATE_READY);
        
        //HAL_Delay(100);
        
        while(I2C1_Slave.Send(&array[5],9,I2C_LAST_FRAME)!= HAL_OK);
        //I2C1_Slave.Send(&array[5],3,I2C_LAST_FRAME);
        
        
        while(I2C1_Slave.GetState() != HAL_I2C_STATE_READY);
        
        // HAL_Delay(100);  
        
    }
}

void INA219_Test()
{
    static INA219::Power_t Power;
    static Peripherals::I2C_Master I2C1_Master(I2C_Master::I2C1_SCL_B6_SDA_B7);
    static INA219 INA219_Obj(&I2C1_Master,0x80);
    I2C1_Master.HwInit();
    INA219_Obj.SetCalibration_32V_2A();
    while(1)
    {
        INA219_Obj.Run(&Power);
        printf("V = %f      I = %f \n",Power.Voltage,Power.Current);
        HAL_Delay(100);
    }    
}


void SPI_Poll_Test()
{
    static uint8_t array[4] = {0xA5,0xA5,0xA5,0xA5};
    Peripherals::GpioOutput LED(GPIOB,GPIO_PIN_0);
    static Peripherals::SPI_Poll SPI_Obj(Peripherals::SPI_Poll::SPI1_A4_A5_A6_A7, 100000);
    SPI_Obj.HwInit();
    LED.HwInit();
    while(1)
    {
        SPI_Obj.Send(array,4);
        HAL_Delay(1);
    }    
}

void Nokia5110LCD_Test()
{
    #define DEL 300
    static Peripherals::SPI_IT SPI_Obj(Peripherals::SPI_Poll::SPI1_A4_A5_A6_A7, 100000);
    static Peripherals::GpioOutput D_C(GPIOB,GPIO_PIN_1);
    static Peripherals::GpioOutput Reset(GPIOB,GPIO_PIN_0);
    static Peripherals::GpioOutput Backlight(GPIOB,GPIO_PIN_10);
    static Peripherals::Nokia5110LCD LCD(&SPI_Obj,&D_C,&Reset,&Backlight);
    LCD.HwInit();
    while(1)
    {
        LCD.DrawLine(0,0,"Amit Chaudhary");
        HAL_Delay(DEL);
        LCD.DrawLine(1,0,"IS");
        HAL_Delay(DEL);
        LCD.DrawLine(2,2,"A");
        HAL_Delay(DEL);
        LCD.DrawLine(3,3,"Good");
        HAL_Delay(DEL);
        LCD.DrawLine(4,7,"Boy");
        HAL_Delay(DEL);
        LCD.Clear();
    }    
}




