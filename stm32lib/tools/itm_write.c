#include "stm32f4xx.h"
#include "itm-write.h"


int printf(const char* format, ...)
{
    char str[128];
    char *s = str; // pointer for the buffer
    int ch_count = 0;

    va_list args; // holds args
    va_start(args, format); // format - last defined param name
    vsprintf(str, format, args); // formatting

    while (*s)
    {
    	ITM_SendChar((*s++));
        ch_count++;
    }
    va_end(args);
    return ch_count;
}
