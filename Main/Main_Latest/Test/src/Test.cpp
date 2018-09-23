


#include"Test.h"

using namespace Peripherals;
using namespace Utils;

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
    Peripherals::GpioOutput CS(GPIOA,GPIO_PIN_4);
    static Peripherals::SPI_Poll SPI_Obj(Peripherals::SPI_Poll::SPI1_A4_A5_A6_A7, &CS, 100000);
    SPI_Obj.HwInit();
    LED.HwInit();
    while(1)
    {
        SPI_Obj.Tx(array,4);
        HAL_Delay(1);
    }    
}

void SPI_Int_Test()
{
    static uint8_t array[4] = {0xA5,0xA5,0xA5,0xA5};
    Peripherals::GpioOutput LED(GPIOB,GPIO_PIN_0);
    Peripherals::GpioOutput CS(GPIOA,GPIO_PIN_4);
    static Peripherals::SPI_Poll SPI_Obj(Peripherals::SPI_Poll::SPI1_A4_A5_A6_A7, &CS, 100000);
    SPI_Obj.HwInit();
    LED.HwInit();
    while(1)
    {
        SPI_Obj.Tx(array,4);
        HAL_Delay(1);
    }    
}

void SPI1_DMA_Test()
{
    
    static Peripherals::SPI_Base::Transaction_t aTransaction;
    static uint8_t TxBuf[4*1024] = {0xA5,0xA5,0xA5,0xA5};
    static uint8_t RxBuf[4]; 
    Peripherals::GpioOutput CS(GPIOA,GPIO_PIN_4);
    static Peripherals::SPI_DMA SPI_Obj(Peripherals::SPI_Poll::SPI1_A4_A5_A6_A7, &CS, 100000);
    SPI_Obj.HwInit();
    
    aTransaction.TxBuf = TxBuf; 
    aTransaction.TxLen = sizeof(TxBuf);
    aTransaction.RxBuf = RxBuf; 
    aTransaction.RxLen = 0;//sizeof(RxBuf);
    aTransaction.pCS = &CS;
    while(1)
    {
        while(SPI_Obj.Post(&aTransaction) != 1);
        //while( (SPI_Obj.GetStatus() & Peripherals::SPI_Base::SPI_BUSY) == Peripherals::SPI_Base::SPI_BUSY );
        while(1);
        //SPI_Obj.Run();
        //HAL_Delay(100);
    }    
}


void SPI2_DMA_Test()
{
    static Peripherals::SPI_Base::Transaction_t aTransaction;
    static uint8_t TxBuf[4*1024] = {0xA5,0xA5,0xA5,0xA5};
    static uint8_t RxBuf[4]; 
    Peripherals::GpioOutput CS(GPIOB,GPIO_PIN_12);
    static Peripherals::SPI_DMA SPI_Obj(Peripherals::SPI_Poll::SPI2_B12_B13_B14_B15, &CS, 100000);
    SPI_Obj.HwInit();
    
    aTransaction.TxBuf = TxBuf; 
    aTransaction.TxLen = sizeof(TxBuf);
    aTransaction.RxBuf = RxBuf; 
    aTransaction.RxLen = 0;//sizeof(RxBuf);
    aTransaction.pCS = &CS;
    while(1)
    {
        while(SPI_Obj.Post(&aTransaction) != 1);
        while(1);
        //SPI_Obj.Run();
        //HAL_Delay(100); 
    }
}

#define Nokia5110LCD_SPI1_TEST 1

#if Nokia5110LCD_SPI1_TEST
uint32_t i,j;
void Nokia5110LCD_SPI1_Test()
{
    uint8_t Txcomplete=0,Txcomplete1=0;
    #define DEL 1
    static Peripherals::GpioOutput      CS(GPIOA,GPIO_PIN_4);
    static Peripherals::SPI_DMA         SPI_Obj(Peripherals::SPI_Base::SPI1_A4_A5_A6_A7,&CS, 100000);
    static Peripherals::GpioOutput      D_C(GPIOB,GPIO_PIN_1);
    static Peripherals::GpioOutput      Backlight(GPIOB,GPIO_PIN_10);
    static Peripherals::GpioOutput      Reset(GPIOB,GPIO_PIN_0);
    static Peripherals::Nokia5110LCD    LCD(&SPI_Obj,&CS,&D_C,&Reset,&Backlight);
    
    static Peripherals::GpioOutput      CS1(GPIOB,GPIO_PIN_14);
    static Peripherals::GpioOutput      D_C1(GPIOB,GPIO_PIN_13);
    static Peripherals::GpioOutput      Reset1(GPIOB,GPIO_PIN_12);
    static Peripherals::GpioOutput      Backlight1(GPIOB,GPIO_PIN_11);    
    static Peripherals::Nokia5110LCD    LCD1(&SPI_Obj,&CS1,&D_C1,&Reset1,&Backlight1);
    
    LCD.HwInit();
    LCD1.HwInit();
    LCD.SetBrigntness(0x15);
    LCD1.SetBrigntness(0x13);
   
    
    while(1)
    {
#if 1
        if(Txcomplete1 == 0)
        {
            LCD.DrawStrBuf(0,0,"Avni Chaudhary",0xc);
            LCD.DrawStrBuf(1,0,"IS");
            LCD.DrawCharBuf(2,2,i++);
            LCD.DrawStrBuf(3,3,"Good",0xc);
            LCD.DrawStrBuf(4,7,"Girl");
        }

//#elif 0     
        if(Txcomplete1 == 0)
        {
            LCD1.DrawStrBuf(0,0,"Amit Chaudhary",0xc);
            LCD1.DrawStrBuf(1,0,"IS");
            LCD1.DrawCharBuf(2,2,j++);
            LCD1.DrawStrBuf(3,3,"Good",0xc);
            LCD1.DrawStrBuf(4,7,"Boy");
        }
        
        Txcomplete1 = LCD1.Refresh();
        HAL_Delay(DEL);
        Txcomplete = LCD.Refresh();
        HAL_Delay(DEL);

#endif
        
        //HAL_Delay(3*DEL);
        
       // HAL_Delay(DEL);
       // LCD.ClearBuffer();
       // LCD.Refresh();
        
        
    }    
}
#endif

#define Nokia5110LCD_SPI2_Test 0

#if Nokia5110LCD_SPI2_Test
void Nokia5110LCD_SPI2_Test()
{
    #define DEL 200
    Peripherals::GpioOutput CS(GPIOB,GPIO_PIN_12);
    static Peripherals::SPI_DMA SPI_Obj(Peripherals::SPI_Poll::SPI2_B12_B13_B14_B15,&CS, 100000); // Nokia LCD with SPI 2
    static Peripherals::GpioOutput D_C(GPIOA,GPIO_PIN_9);
    static Peripherals::GpioOutput Reset(GPIOA,GPIO_PIN_10);
    static Peripherals::GpioOutput Backlight(GPIOB,GPIO_PIN_10);
    static Peripherals::Nokia5110LCD LCD(&SPI_Obj,&D_C,&Reset,&Backlight);
    LCD.HwInit();
    SPI_Obj.SPI2_TxDoneCallback = SPI2_DMA_Tx_Complete_Callback;
    while(1)
    {
        LCD.DrawLine(0,0,"Avni Chaudhary");
        HAL_Delay(DEL);
        LCD.DrawLine(1,0,"IS");
        HAL_Delay(DEL);
        LCD.DrawLine(2,2,"A");
        HAL_Delay(DEL);
        LCD.DrawLine(3,3,"Good");
        HAL_Delay(DEL);
        LCD.DrawLine(4,7,"Girl");
        HAL_Delay(DEL);
        LCD.Clear();
    }    
}
#endif

#define Nokia5110LCD_Dual_Test 0

#if Nokia5110LCD_Dual_Test
void Nokia5110LCD_Dual_Test()
{
    #define DEL_DUAL 100
    static SPI_HandleTypeDef hspi1;
    static Peripherals::GpioOutput CS1(GPIOA,GPIO_PIN_4);
    static DMA_HandleTypeDef hdma_spi1_rx;
    static DMA_HandleTypeDef hdma_spi1_tx;
    
    /* LCD on SPI 1*/
    static Peripherals::SPI_DMA SPI_Obj1(Peripherals::SPI_Poll::SPI1_A4_A5_A6_A7,&CS1, 100000,&hspi1, &hdma_spi1_rx, &hdma_spi1_tx);
    static Peripherals::GpioOutput D_C1(GPIOB,GPIO_PIN_1);
    static Peripherals::GpioOutput Reset1(GPIOB,GPIO_PIN_0);
    static Peripherals::GpioOutput Backlight1(GPIOB,GPIO_PIN_10);
    static Peripherals::Nokia5110LCD LCD1(&SPI_Obj1,&D_C1,&Reset1,&Backlight1);
    LCD1.HwInit();
    LCD1.SetContrast(0x15);
    
    /* LCD on SPI 2*/
    static SPI_HandleTypeDef hspi2;
    static DMA_HandleTypeDef hdma_spi2_rx;
    static DMA_HandleTypeDef hdma_spi2_tx;
    static Peripherals::GpioOutput CS2(GPIOA,GPIO_PIN_15);
    
    static Peripherals::SPI_DMA SPI_Obj2(Peripherals::SPI_Poll::SPI1_A4_A5_A6_A7, &CS2, 100000,&hspi2, &hdma_spi2_rx, &hdma_spi2_tx); // Nokia LCD with SPI 2
    static Peripherals::GpioOutput D_C2(GPIOA,GPIO_PIN_9);
    static Peripherals::GpioOutput Reset2(GPIOA,GPIO_PIN_10);
    static Peripherals::GpioOutput Backlight2(GPIOB,GPIO_PIN_10);
    static Peripherals::Nokia5110LCD LCD2(&SPI_Obj2,&D_C2,&Reset2,&Backlight2);
    LCD2.HwInit();
    
    
    
    while(1)
    {
        LCD1.DrawLine(0,0,"Amit Chaudhary");
        HAL_Delay(DEL_DUAL);
        LCD1.DrawLine(1,0,"IS");
        HAL_Delay(DEL_DUAL);
        LCD1.DrawLine(2,2,"A");
        HAL_Delay(DEL_DUAL);
        LCD1.DrawLine(3,3,"Good");
        HAL_Delay(DEL_DUAL);
        LCD1.DrawLine(4,7,"Boy");
        HAL_Delay(DEL_DUAL);
        
        
        LCD2.DrawLine(0,0,"Avni Chaudhary");
        HAL_Delay(DEL_DUAL);
        LCD2.DrawLine(1,0,"IS");
        HAL_Delay(DEL_DUAL);
        LCD2.DrawLine(2,2,"A");
        HAL_Delay(DEL_DUAL);
        LCD2.DrawLine(3,3,"Good");
        HAL_Delay(DEL_DUAL);
        LCD2.DrawLine(4,7,"Girl");
        HAL_Delay(DEL_DUAL);
        
        LCD1.Clear();
        LCD2.Clear();
    }    
}
#endif

#define Queue_TEST 1

#if Queue_TEST

void Queue_Test()
{
    using Queue = Queue<uint32_t,10> ;
    static Queue Uint_Q;
    uint32_t Data;
    Queue::QSTATUS status = Queue::QEMPTY;
    
    while(1) 
    {
        while ( status != Queue::QFULL)
        {
           status = Uint_Q.Write(0xDeadBabe);
          // printf("Write -> Status(%d)\n",status);
        }
        
        while ( status != Queue::QEMPTY)
        {
           status = Uint_Q.Read(Data); 
           //printf("Read -> Status(%d)  Data = 0x%x\n",status, Data);           
        } 
    }   
}
#endif