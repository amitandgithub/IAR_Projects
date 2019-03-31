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
SPI_TypeDef* SD::m_SPI_SD;    
SPI_Base::SPIx_t SD::m_SPIx;

SD::SD(SPIDrv_t*   pSpiDriverSD, GpioOutput* pCS)
{
     m_pSpiDriverSD = pSpiDriverSD;
     m_pSD_CS = pCS;     
     m_SPIx = m_pSpiDriverSD->GetSPIx();
     
#if SPI_BM 
     if(m_SPIx == Peripherals::SPI_Poll::SPI1_A4_A5_A6_A7)
     {
          m_SPI_SD = SPI1;
     }
     else if(m_SPIx == Peripherals::SPI_Poll::SPI2_B12_B13_B14_B15)
     {
          m_SPI_SD = SPI2;
     }
     else
     {
         m_SPI_SD = SPI1;
     }
    
#endif
}

void SD::HwInit()
{  
        
   
                                        
    if( (m_pSpiDriverSD->GetStatus(m_SPIx) & Peripherals::SPI_Base::SPI_INIT_DONE) != Peripherals::SPI_Base::SPI_INIT_DONE )
    {
       m_pSpiDriverSD->HwInit(); 
    }
   	
    m_pSD_CS->HwInit();
    
#if SPI_BM    
     m_SPI_SD->CR1 |=  SPI_CR1_SPE;
 #endif  
}

uint8_t SD::spi_txrx(uint8_t data)
{
#if SPI_HAL
    
    uint8_t rx;
    
    m_pSpiDriverSD->TxRx(&data, &rx,1);   
    
    return rx;
    
#elif SPI_BM
    
    m_SPI_SD->DR = data;
    
	while ((m_SPI_SD->SR & SPI_FLAG_RXNE) == 0);
    
	return m_SPI_SD->DR;
    
#endif

}



} // Namespace Peripherals
