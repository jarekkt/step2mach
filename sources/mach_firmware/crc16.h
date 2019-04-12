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


uint16_t crc_sum(const uint8_t * message, uint32_t  length,uint16_t crc);
void   crc_single(uint8_t  cc, uint16_t * crc);

int    crc_verify(const uint8_t * message,uint32_t length);
void   crc_append(uint8_t  * message, int length);

