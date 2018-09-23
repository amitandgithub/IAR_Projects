/******************
** FILE: SPI_Base.cpp
**
** DESCRIPTION:
**  SPI Base Class functions
**
** CREATED: 9/2/2018, by Amit Chaudhary
******************/
#include "SPI_Base.h"

namespace Peripherals
{
        
SPI_Base::Callback_t                            SPI_Base::SPI1_TxDoneCallback;
SPI_Base::Callback_t                            SPI_Base::SPI1_RxDoneCallback;
SPI_Base::Callback_t                            SPI_Base::SPI1_TxRxDoneCallback;
SPI_Base::Callback_t                            SPI_Base::SPI1_TxHalfDoneCallback;
SPI_Base::Callback_t                            SPI_Base::SPI1_RxHalfDoneCallback;
SPI_Base::Callback_t                            SPI_Base::SPI1_TxRxHalfDoneCallback;

SPI_Base::Callback_t                            SPI_Base::SPI2_TxDoneCallback;
SPI_Base::Callback_t                            SPI_Base::SPI2_RxDoneCallback;
SPI_Base::Callback_t                            SPI_Base::SPI2_TxRxDoneCallback;
SPI_Base::Callback_t                            SPI_Base::SPI2_TxHalfDoneCallback;
SPI_Base::Callback_t                            SPI_Base::SPI2_RxHalfDoneCallback;
SPI_Base::Callback_t                            SPI_Base::SPI2_TxRxHalfDoneCallback;

Peripherals::GpioOutput* SPI_Base::m_pChipSelect_SPI1;
Peripherals::GpioOutput* SPI_Base::m_pChipSelect_SPI2;
SPI_HandleTypeDef  SPI_Base::m_hspi_1; 
SPI_HandleTypeDef  SPI_Base::m_hspi_2; 

}



extern "C"
{
 /* Transmit complete callback*/
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if(hspi->Instance == SPI1)
    {
        Peripherals::SPI_Base::m_pChipSelect_SPI1->On();
        if(Peripherals::SPI_Base::SPI1_TxDoneCallback != nullptr)
            Peripherals::SPI_Base::SPI1_TxDoneCallback();
    }
    else if(hspi->Instance == SPI2)
    {
        Peripherals::SPI_Base::m_pChipSelect_SPI2->On();
        if(Peripherals::SPI_Base::SPI2_TxDoneCallback != nullptr)
            Peripherals::SPI_Base::SPI2_TxDoneCallback();   
    }

}
 /* Receive complete callback*/
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if(hspi->Instance == SPI1)
    {
        if(Peripherals::SPI_Base::SPI1_RxDoneCallback != nullptr)
            Peripherals::SPI_Base::SPI1_RxDoneCallback();
    }
    else if(hspi->Instance == SPI2)
    {
        if(Peripherals::SPI_Base::SPI2_RxDoneCallback != nullptr)
            Peripherals::SPI_Base::SPI2_RxDoneCallback();   
    }    
}
 /* Transmit and Receive complete callback*/
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if(hspi->Instance == SPI1)
    {
        Peripherals::SPI_Base::m_pChipSelect_SPI1->On();
        if(Peripherals::SPI_Base::SPI1_TxRxDoneCallback != nullptr)
            Peripherals::SPI_Base::SPI1_TxRxDoneCallback();
    }
    else if(hspi->Instance == SPI2)
    {
        Peripherals::SPI_Base::m_pChipSelect_SPI2->On();
        if(Peripherals::SPI_Base::SPI2_TxRxDoneCallback != nullptr)
            Peripherals::SPI_Base::SPI2_TxRxDoneCallback();   
    }   
}

 /* Transmit complete Half callback*/
void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
    if(hspi->Instance == SPI1)
    {
        if(Peripherals::SPI_Base::SPI1_TxHalfDoneCallback != nullptr)
            Peripherals::SPI_Base::SPI1_TxHalfDoneCallback();
    }
    else if(hspi->Instance == SPI2)
    {
        if(Peripherals::SPI_Base::SPI2_TxHalfDoneCallback != nullptr)
            Peripherals::SPI_Base::SPI2_TxHalfDoneCallback();   
    }

}
 /* Receive complete Half callback*/
void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
    if(hspi->Instance == SPI1)
    {
        if(Peripherals::SPI_Base::SPI1_RxHalfDoneCallback != nullptr)
            Peripherals::SPI_Base::SPI1_RxHalfDoneCallback();
    }
    else if(hspi->Instance == SPI2)
    {
        if(Peripherals::SPI_Base::SPI2_RxHalfDoneCallback != nullptr)
            Peripherals::SPI_Base::SPI2_RxHalfDoneCallback();   
    }    
}
 /* Transmit and Receive Half complete callback*/
void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
    if(hspi->Instance == SPI1)
    {
        if(Peripherals::SPI_Base::SPI1_TxRxHalfDoneCallback != nullptr)
            Peripherals::SPI_Base::SPI1_TxRxHalfDoneCallback();
    }
    else if(hspi->Instance == SPI2)
    {
        if(Peripherals::SPI_Base::SPI2_TxRxHalfDoneCallback != nullptr)
            Peripherals::SPI_Base::SPI2_TxRxHalfDoneCallback();   
    }   
}


}
