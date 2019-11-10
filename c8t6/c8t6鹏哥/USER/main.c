/*************************************************************************************
can.c
@author : ICE COFFCE
@action : ������
@data : 2018.12.14
@founction :
		��ʼ����can�����Լ�����
***************************************************************************************/



#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "led.h"
#include "beep.h"

	



int main(void)    //������     **************************************************************
{

	SystemInit();
    delay_init();//��ʱ������ʼ��
	LED_Init();	
	BEEP_Init();
	KEY_Init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	
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

