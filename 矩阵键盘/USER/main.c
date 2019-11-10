#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"

int RX_BUF[USART_REC_LEN] ;
u16 RX_STA = 0;
	
 int main(void)
 {	
	int t,i,res;
	delay_init();	    	 //��ʱ������ʼ��	  
	LED_Init();		  	 
	KEY_Init();          	//��ʼ���밴�����ӵ�Ӳ���ӿ�
	uart_init(19200);
	while(1)
	{
		t = Return_Angle();
		i = Return_Data();
		
		res = USART_ReceiveData(USART1);
		if((RX_STA&0x8000)==0)//����δ���
			{
			if(RX_STA&0x4000)//���յ���0x0d
				{
				if(res!=0x0a)RX_STA=0;//���մ���,���¿�ʼ
				else RX_STA|=0x8000;	//��������� 
				}
			else //��û�յ�0X0D
				{	
				if(res==0x0d)RX_STA|=0x4000;
				else
					{
					RX_BUF[RX_STA&0X3FFF]=res ;
					RX_STA++;
					if(RX_STA>(USART_REC_LEN-1))RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}   		 
		 
	}	



	
}
