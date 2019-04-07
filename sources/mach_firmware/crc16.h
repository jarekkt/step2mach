// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jarosaw Karwik
   E-Mail:     jaroslaw.karwik(at)gmail.com
   
**/
// ----------------------------------------------------------------------------


#define CRC_INIT 0xFFFF


uint16_t crc_sum(const unsigned char* message, int length,uint16_t crc);
void   crc_single(unsigned char cc, uint16_t * crc);

int    crc_verify(const unsigned char* message, unsigned long length);
void   crc_append(unsigned char* message, int length);

