#include "..\..\mach_common\types.h"


#define PM_LENGTH_SIZE (64 * 8 * 3)

void flash_read_pm(char * ptrData, Uint32_t SourceAddr,Uint16_t length);
int  flash_write_pm(char * ptrData, Uint32_t DestAddr,Uint16_t eraselength,Uint16_t writelength);
