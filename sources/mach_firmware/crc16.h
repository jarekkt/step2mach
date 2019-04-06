// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jaros³aw Karwik
   E-Mail:     jaroslaw.karwik(at)gnail.com
   
**/
// ----------------------------------------------------------------------------


#define CRC_INIT 0xFFFF


Uint16_t crc_sum(const unsigned char* message, int length,Uint16_t crc);
void   crc_single(unsigned char cc, Uint16_t * crc);

int    crc_verify(const unsigned char* message, unsigned long length);
void   crc_append(unsigned char* message, int length);

