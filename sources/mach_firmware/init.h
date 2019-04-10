// ----------------------------------------------------------------------------
/**
 
   Property of Kartech  
   (c) Copyright Kartech 2011-2019 jaroslaw.karwik@gmail.com
   
   See license.txt for details

   Author:      Jarosaw Karwik
   E-Mail:     jaroslaw.karwik(at)gmail.com
   
**/
// ----------------------------------------------------------------------------


#ifndef INIT_H
#define INIT_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"


#define DIM(x_)      (sizeof(x_)/sizeof(x_[0]))

void init_main(void);
void init_net(void);

#endif //INIT_H

