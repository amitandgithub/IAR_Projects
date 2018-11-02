/******************
** FILE: SD.cpp
**
** DESCRIPTION:
**  SD card functionality
**
** CREATED: 10/31/2018, by Amit Chaudhary
******************/

#include "SD.h"

namespace Peripherals
{

    
SD::SPIDrv_t*   SD::m_pSpiDriverSD;
GpioOutput* SD::m_pSD_CS;
    
SPI_Base::SPIx_t SD::m_SPIx;

SD::SD(SPIDrv_t*   pSpiDriverSD, GpioOutput* pCS)
{
     m_pSpiDriverSD = pSpiDriverSD;
     m_pSD_CS = pCS;
}

void SD::HwInit()
{
    m_SPIx = m_pSpiDriverSD->GetSPIx();
                                        
    if( (m_pSpiDriverSD->GetStatus(m_SPIx) & Peripherals::SPI_Base::SPI_INIT_DONE) != Peripherals::SPI_Base::SPI_INIT_DONE )
    {
       m_pSpiDriverSD->HwInit(); 
    }
   	
    m_pSD_CS->HwInit();
   
}

uint8_t SD::spi_txrx(uint8_t data)
{
    uint8_t rx;
    m_pSpiDriverSD->TxRx(&data, &rx,1);     
    return rx;
}



} // Namespace Peripherals
