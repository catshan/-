#include "stm32f10x.h"
#include "timer.h"
#include "delay.h"
#include "usart.h"
#include "can.h"
#include "sys.h"
#include "hongwai.h"
#include "sort.h"
#include "lcd.h"
/************************************************
 基于openmv视觉分拣垃圾桶
 作者： @ICECOFFFEE
************************************************/

 int main(void)
 {	
	u8 Res;
	delay_init();
	hongwai_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置 NVIC 中断分组 2
	uart_init(19200); //串口初始化波特率为 115200
	TIM3_PWM_Init(19999,35);	 //不分频。0.02s=(19999+1)*(35+1)/36000000  APB1
	TIM4_PWM_Init(19999,35);
	Sort_Init();
	 while(1)
	 {
		 if(hongwai==1) //	//当红外识别到人走近  （可以换成不重复触发模式：人体在其范围内活动，
		  {
			Put_In();
			delay_ms(1000);
			break;
		  }
		Transport();

		Res = USART_ReceiveData(USART1);	//读取接收到OPENMV的数据
		 switch (Res)
		 {
			 case 49:
				 Orange_Recycle();
			 break;
			 default:
				 Blue_Recycle();	
			 break;
			 				 
		 }
delay_ms(100);
	 }
 }
