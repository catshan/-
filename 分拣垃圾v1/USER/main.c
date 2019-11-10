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
 ����openmv�Ӿ��ּ�����Ͱ
 ���ߣ� @ICECOFFFEE
************************************************/

 int main(void)
 {	
	u8 Res;
	delay_init();
	hongwai_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //���� NVIC �жϷ��� 2
	uart_init(19200); //���ڳ�ʼ��������Ϊ 115200
	TIM3_PWM_Init(19999,35);	 //����Ƶ��0.02s=(19999+1)*(35+1)/36000000  APB1
	TIM4_PWM_Init(19999,35);
	Sort_Init();
	 while(1)
	 {
		 if(hongwai==1) //	//������ʶ�����߽�  �����Ի��ɲ��ظ�����ģʽ���������䷶Χ�ڻ��
		  {
			Put_In();
			delay_ms(1000);
			break;
		  }
		Transport();

		Res = USART_ReceiveData(USART1);	//��ȡ���յ�OPENMV������
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
