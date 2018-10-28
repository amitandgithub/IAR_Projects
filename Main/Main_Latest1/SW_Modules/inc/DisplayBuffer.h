/******************
** CLASS: DisplayBuffer 
**
** DESCRIPTION:
**  Display Buffer class
**
** CREATED: 10/15/2018, by Amit Chaudhary
**
** FILE: DisplayBuffer.h
**
******************/
#ifndef DisplayBuffer_h
#define DisplayBuffer_h

#include"stdint.h"
#include<cstring>

namespace Peripherals
{
    
    
    
class DisplayBuffer
{
public:
    static const uint8_t NORMAL  = 0x0C;
	static const uint8_t INVERSE = 0x0D;
    
    static const uint8_t SIZE_OF_1_CHAR = 6;
    static const uint8_t NO_OF_CHAR_IN_LINE = 14;
    static const uint8_t TOTAL_ROWS = 6;
    static constexpr uint16_t BUFFER_SIZE = (SIZE_OF_1_CHAR*NO_OF_CHAR_IN_LINE*TOTAL_ROWS);
    
    DisplayBuffer(){};
    ~DisplayBuffer(){};
    
    void DrawChar(unsigned char Row, unsigned char Col, const char aChar, uint8_t format = NORMAL);
    void DrawStr (unsigned char Row, unsigned char Col, const char* Str, uint8_t format = NORMAL);
    void DrawBitmap(const char* Str, uint8_t format);
    void InvertRow(unsigned char Row);
    


private:
    char Buffer[BUFFER_SIZE];
    
};





}

#endif //DisplayBuffer_h
