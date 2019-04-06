#include "types.h"

#define CRC_INIT 0xFFFF


Uint16_t crc_sum(const unsigned char* message, int length,Uint16_t crc);
void   	 crc_single(unsigned char cc, Uint16_t * crc);

int    	crc_verify(const unsigned char* message, unsigned long length);
void    crc_append(unsigned char* message, int length);

