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
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	 
	KEY_Init();          	//初始化与按键连接的硬件接口
	uart_init(19200);
	while(1)
	{
		t = Return_Angle();
		i = Return_Data();
		
		res = USART_ReceiveData(USART1);
		if((RX_STA&0x8000)==0)//接收未完成
			{
			if(RX_STA&0x4000)//接收到了0x0d
				{
				if(res!=0x0a)RX_STA=0;//接收错误,重新开始
				else RX_STA|=0x8000;	//接收完成了 
				}
			else //还没收到0X0D
				{	
				if(res==0x0d)RX_STA|=0x4000;
				else
					{
					RX_BUF[RX_STA&0X3FFF]=res ;
					RX_STA++;
					if(RX_STA>(USART_REC_LEN-1))RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}   		 
		 
	}	



	
}
