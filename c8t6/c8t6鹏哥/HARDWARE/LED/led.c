#include "led.h"	   
#include "sys.h"
#include "delay.h"
//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化

//流水灯端口pa678,11 12 13
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6;	//流水灯			
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 

}
void LED_Right()
{
	LED6=0;
	LED1=0;
	LED2=0;
	LED3=0;
	LED4=0;
	LED5=0;

	delay_ms(500);

	
	LED6=0;
	LED1=1;
	LED2=0;
	LED3=0;
	LED4=0;
	LED5=0;
	delay_ms(500);
	LED6=0;
	LED1=0;
	LED2=1;
	LED3=0;
	LED4=0;
	LED5=0;
	delay_ms(500);
		LED6=0;
	LED1=0;
	LED2=0;
	LED3=1;
	LED4=0;
	LED5=0;
	delay_ms(500);
		LED6=0;
	LED1=0;
	LED2=0;
	LED3=0;
	LED4=1;
	LED5=0;
	delay_ms(500);
		LED6=0;
	LED1=0;
	LED2=0;
	LED3=0;
	LED4=0;
	LED5=1;
	delay_ms(500);
		LED6=1;
	LED1=0;
	LED2=0;
	LED3=0;
	LED4=0;
	LED5=0;
	delay_ms(500);
}
void LED_Left()
{
	LED6=0;
	LED1=0;
	LED2=0;
	LED3=0;
	LED4=0;
	LED5=0;

	delay_ms(500);
	
	
	LED6=1;
	LED1=0;
	LED2=0;
	LED3=0;
	LED4=0;
	LED5=0;
	delay_ms(500);
	LED6=0;
	LED1=0;
	LED2=0;
	LED3=0;
	LED4=0;
	LED5=1;
	delay_ms(500);
		LED6=0;
	LED1=0;
	LED2=0;
	LED3=0;
	LED4=1;
	LED5=0;
	delay_ms(500);
		LED6=0;
	LED1=0;
	LED2=0;
	LED3=1;
	LED4=0;
	LED5=0;
	delay_ms(500);
		LED6=0;
	LED1=0;
	LED2=1;
	LED3=0;
	LED4=0;
	LED5=0;
	delay_ms(500);
		LED6=0;
	LED1=1;
	LED2=0;
	LED3=0;
	LED4=0;
	LED5=0;
	delay_ms(500);
}
