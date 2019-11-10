/*************************************************************************************
can.c
@author : ICE COFFCE
@action : 主函数
@data : 2018.12.14
@founction :
		初始化及can发送以及接收
***************************************************************************************/



#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "led.h"
#include "beep.h"

	



int main(void)    //主函数     **************************************************************
{

	SystemInit();
    delay_init();//延时函数初始化
	LED_Init();	
	BEEP_Init();
	KEY_Init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
    uart_init(115200);	 	//串口初始化为115200
	
    while(1)
    { 
		switch(key_scan())
		{
			case 1:
				LED_Left();
				break;
			case 2:
				LED_Right();
				break;
			case 3:
				BEEP=!BEEP;
			break;
			case 4:
			{
				LED4 = 1;
				LED1 = 0;
				LED2 = 0;
				LED3 = 0;
				LED5 = 0;
				LED6 = 0;
				break;
			}
			case 5:
				printf("5\r\n");
			break;
			case 6:
				printf("6\r\n");
			break;
			case 7:
				printf("7\r\n");
			break;
			case 8:
				printf("8\r\n");
			break;
			case 9:
				printf("9\r\n");
			break;

		}
			

   }
} 

