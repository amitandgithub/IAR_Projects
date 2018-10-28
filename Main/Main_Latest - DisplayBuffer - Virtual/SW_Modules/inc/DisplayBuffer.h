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
    static const        uint8_t SIZE_OF_1_CHAR      = 6;
    static const        uint8_t NO_OF_CHAR_IN_LINE  = 14;
    static const        uint8_t TOTAL_ROWS          = 6;
    static constexpr    uint32_t BUFFER_SIZE        = (SIZE_OF_1_CHAR*NO_OF_CHAR_IN_LINE*TOTAL_ROWS);
    
    typedef struct 
    { 
        char Chars[NO_OF_CHAR_IN_LINE][SIZE_OF_1_CHAR];
//        char Char1 [SIZE_OF_1_CHAR];
//        char Char2 [SIZE_OF_1_CHAR];
//        char Char3 [SIZE_OF_1_CHAR];
//        char Char4 [SIZE_OF_1_CHAR];
//        char Char5 [SIZE_OF_1_CHAR];
//        char Char6 [SIZE_OF_1_CHAR];
//        char Char7 [SIZE_OF_1_CHAR];
//        char Char8 [SIZE_OF_1_CHAR];
//        char Char9 [SIZE_OF_1_CHAR];
//        char Char10[SIZE_OF_1_CHAR];
//        char Char11[SIZE_OF_1_CHAR];
//        char Char12[SIZE_OF_1_CHAR];
//        char Char13[SIZE_OF_1_CHAR];
        
    }LineText_t;
    
    typedef struct 
    { 
        LineText_t Line[TOTAL_ROWS];
//        LineText_t Line1;
//        LineText_t Line2;
//        LineText_t Line3;
//        LineText_t Line4;
//        LineText_t Line5;
        
    }DisplayBufferText_t;
    
    typedef union
    {
        char Array[BUFFER_SIZE];
        DisplayBufferText_t Struct;
        
    }DisplayBufferMem_t;
        
    static const uint8_t NORMAL  = 0x0C;
	static const uint8_t INVERSE = 0x0D;
    
            DisplayBuffer   (){Clear();}
    
            ~DisplayBuffer  (){};
    
    virtual void        DrawChar        (unsigned char Row, unsigned char Col, const char aChar, uint8_t format = NORMAL);
    virtual void        DrawStr         (unsigned char Row, unsigned char Col, const char* Str, uint8_t format = NORMAL);
    virtual void        DrawBuffer      (const char* Str, uint8_t format = NORMAL);
    virtual void        DrawBitmap      (const char* Str);
    virtual void        InvertRow       (unsigned char Row);
    virtual char*       GetBuffer       (){return &DisplayBufferMem.Array[0];}
    virtual void        Clear           (){ memset(&DisplayBufferMem.Array[0],0,BUFFER_SIZE);};
    virtual uint32_t    GetSize         (){return BUFFER_SIZE; }

private:
    DisplayBufferMem_t DisplayBufferMem;    
};


}

#endif //DisplayBuffer_h
