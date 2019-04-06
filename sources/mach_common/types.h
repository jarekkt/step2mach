// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jaros³aw Karwik
   E-Mail:     jaroslaw.karwik(at)gnail.com
   
**/
// ----------------------------------------------------------------------------




/*------------------------------------------------------------------------
;
;     SYSTEM.h
;
;       Declaration of data types for different targets.
;       Must be included in every software module.
;
;------------------------------------------------------------------------*/

#ifndef SYSTEM_H
#define SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32

typedef unsigned char       Uint8_t;
typedef unsigned short int  Uint16_t;
typedef unsigned int        Uint32_t;
typedef unsigned long long  Uint64_t;
typedef float               Float32_t;
typedef signed char         Int8_t;
typedef signed short int    Int16_t;
typedef signed int          Int32_t;
typedef signed long long    Int64_t;
typedef unsigned char       Bool_t;

#define TRUE    1
#define FALSE   0

#else

typedef unsigned char       Uint8_t;
typedef unsigned int        Uint16_t;
typedef unsigned long       Uint32_t;
typedef unsigned long long  Uint64_t;
typedef float               Float32_t;
typedef signed char         Int8_t;
typedef signed int          Int16_t;
typedef signed long         Int32_t;
typedef signed long long    Int64_t;
typedef unsigned char       Bool_t;

#define TRUE    1
#define FALSE   0

#endif


#ifdef __cplusplus
}
#endif


#endif
