#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
 
#define LED1 PAout(6)
#define LED2 PAout(7)	
#define LED3 PAout(8)
#define LED4 PAout(11)	
#define LED5 PAout(12)
#define LED6 PAout(13)	

void LED_Init(void);//≥ı ºªØ
void LED_Left(void);
void LED_Right(void);
		 				    
#endif
