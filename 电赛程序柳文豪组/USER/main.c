#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "key.h"
#include "timer.h"
#include "led.h"
#include "oled.h"
#include "bmp.h"
#include "pid.h"

extern	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
extern TIM_OCInitTypeDef  TIM_OCInitStructure;

void Since_the_aim_model(void);


int main()
{    
	int mb;
	int d = 0;
	int c = 0;
	int i=0;
	int T,A;
	int key;	
	int arr[6] = {0,0,0,0,0,0};
	
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	uart_init(115200); 	
	KEY_Init();
	TIM3_PWM_Init(19999,71);
	OLED_Init();
	OLED_ShowChinese(0,0,0,16);
	OLED_ShowChinese(20,0,1,16);
	OLED_ShowChinese(40,0,2,16);
	OLED_ShowChinese(60,0,3,16);
	OLED_ShowChinese(80,0,4,16);
	OLED_ShowChinese(100,0,5,16);

	OLED_ShowString(4,18,"d=",16);//8*16 ¡°ABC¡±
	OLED_ShowString(72,18,"c=",16);//8*16 ¡°ABC¡±
	OLED_Refresh();
	TIM_SetCompare2(TIM3,2300);
	TIM_SetCompare3(TIM3,1500);
	TIM_SetCompare4(TIM3,800);
	printf("OK\r\n");
	
	while(1)
	{
		key=key_scan();	//µÃµ½¼ü	
		switch(key)
		{				 
			case 0:	//0
			{       
				mb=0;
				i++;
				key=15;							 
				break;
			}												
			case 1:	//1	 
			{ 
				mb=1;
				i++;
				key=15; 	
				break;
			}
			case 2:	//2 
			{
				mb=2;
				i++;
				key=15;	                            
				break;
			}
			case 3:	//3
		  {       
				mb=3;
				i++;	
				key=15;		                          										 
				break;
			}												
			case 4:	//4	 
			{ 
				mb=4;
				i++;
				key=15;
				break;
			}
			case 5:	//5
			{
				mb=5;
				i++;
				key=15;
				break;
			}
			case 6:	//6
			{       
				mb=6;
				i++;	
				key=15;												 
				break;
			}												
			case 7:	//7
			{ 
				mb=7;
				i++;
				key=15;
				break;
			}
			case 8:	//8
			{
				mb=8;
				i++;
				key=15;
				break;
			}
			case 9:	//9
			{       
				mb=9;
				i++;
				key=15;
				break;
			}
			case 14:	//9
			{       
				mb=14;
				key=15;
				break;
			}
		}
		arr[i]=mb;
		 
		if(i == 3)
		{int w=0;
			d = arr[1]*100 + arr[2]*10 + arr[3];
			OLED_ShowNum(22,18,d,3,16);
			OLED_Refresh();
			if(d==300)
			{
			TIM_SetCompare2(TIM3,2368);//PB^5
      }
			if(d==290)
			{
			TIM_SetCompare2(TIM3,2370);//PB^5
      }
			if(d==280)
			{
			TIM_SetCompare2(TIM3,2373);//PB^5
      }
			if(d==270)
			{
			TIM_SetCompare2(TIM3,2371);//PB^5
      }
			if(d==260)
			{
			TIM_SetCompare2(TIM3,2382);//PB^5
      }
			if(d==250)
			{
			TIM_SetCompare2(TIM3,2375);//PB^5
      }
			if(d==240)
			{
			TIM_SetCompare2(TIM3,2397);//PB^5
      }
			if(d==230)
			{
			TIM_SetCompare2(TIM3,2406);//PB^5
      }
			if(d==220)
			{
			TIM_SetCompare2(TIM3,2415);//PB^5
      }
			if(d==210)
			{
			TIM_SetCompare2(TIM3,2425);//PB^5
      }
			if(d==200)
			{
			TIM_SetCompare2(TIM3,2434);//PB^5
      }
		}
		
		if(i == 5)
		{
			c= arr[4]*10 + arr[5];
			A=1300+c*7;
			OLED_ShowNum(92,18,c,2,16);
			OLED_Refresh();
			TIM_SetCompare3(TIM3,A);
			i = 0;
		
	
		delay_ms(65000);
		delay_ms(65000);
	
	
		TIM_SetCompare4(TIM3,900);
			delay_ms(1000);
			TIM_SetCompare4(TIM3,700);
		}
		if(mb ==14)
		{
			Since_the_aim_model();
		}
	}
}

u16 cx;
u16 cy;
u16 Lengh;

void Since_the_aim_model(void)
{
	
	PID_init();
	
	OLED_Clear();
	OLED_ShowChinese(0,0,6,16);
	OLED_ShowChinese(20,0,7,16);
	OLED_ShowChinese(40,0,8,16);
	OLED_ShowChinese(60,0,9,16);
	OLED_ShowString(0,20,"CX:",16);
	OLED_ShowString(60,20,"CY:",16);
	OLED_ShowString(0,40,"Lengh:",16);
	
	OLED_Refresh();
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{
			cx = (USART_RX_BUF[0]-48)*100 + (USART_RX_BUF[1]-48)*10 + (USART_RX_BUF[2]-48);
			cy = (USART_RX_BUF[3]-48)*100 + (USART_RX_BUF[4]-48)*10 + (USART_RX_BUF[5]-48);
			Lengh = (USART_RX_BUF[6]-48)*1000 + (USART_RX_BUF[7]-48)*100 + (USART_RX_BUF[8]-48)*10 + (USART_RX_BUF[9]-48);
			
			OLED_ShowNum(30,20,cx,3,16);
			OLED_ShowNum(90,20,cy,3,16);
			OLED_ShowNum(50,40,Lengh,4,16);
			OLED_Refresh();
			
			float pidOut = PID_realize(160);
			
			u32 cmpare = TIM3->CCR3;
			
			cmpare += pidOut;
			
			if(cmpare > 1833)
			{
				cmpare = 1833;
			}
			
			else if(cmpare < 1167)
			{
				cmpare= 1167;
			}
			
			TIM_SetCompare3(TIM3,cmpare);
			
			for(int i = 0; i < 15 ; i++)
			{
				USART_RX_BUF[i] = 0;
			}
			
	
		}
	}
	
}




