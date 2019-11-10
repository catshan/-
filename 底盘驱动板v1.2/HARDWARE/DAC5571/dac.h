#ifndef __DAC_H
#define __DAC_H

#include "sys.h"

#define DAC5571_ADDR  0X98

void DAC5571_Init(void);
u8 DAC5571_WriteData(u8 data);
void WriteOneByte(u8 data);
void write1(void);
void write0(void);

u8 VOUT(float val);


#endif


