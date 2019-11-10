#include "key.h"
#include "delay.h"
#include "sys.h"

int Data=0,H_A=0,dir=0,k=0,l=0;	  
u16 arr[6]={0,0,0,0,0,0};
//按键初始化函数 
//PA15和PC5 设置成输入
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//PA 0 1 2 3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置成推挽输出
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//PA 4 5 6 7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA
	
} 
//按键处理函数



int key_scan(void)
{
	static u8 key_up=1;
	int key_num=0;
	u8 temp=0;								//判断列的数据缓存区
	u8 temp1=0;								//判断行的数据缓存区
	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);			//拉低行线
	delay_us(10);
	temp=GPIO_ReadInputData(GPIOA)&0xff;				//读出A的数据寄存器的值
	delay_us(1);
	if (key_up&&(temp != 0xf0))							//判断键是否按下与是否连按
	{
		delay_ms(10);						//消抖
		key_up=0;							//当有键按下时，将连按标志位挂起
		temp = GPIO_ReadInputData(GPIOA)&0xff;			//消抖后重新得到A的值
		if(temp != 0xf0)
		{			
			switch(temp)								//进入键盘按下的相应行线
			{
				case 0xe0:
				{
					
					GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);		//依次从第一行拉低到第四行，读出A的数据，从而判断
					GPIO_ResetBits(GPIOA,GPIO_Pin_0);										//是哪一行的键盘按下，从而给出相应的键值
					delay_us(10);
					temp1=GPIO_ReadInputData(GPIOA)&0xff;
					if (temp1==0xee)
						key_num=1;
					else
					{
						GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
						GPIO_ResetBits(GPIOA,GPIO_Pin_1);
						delay_us(1);
						temp1=GPIO_ReadInputData(GPIOA)&0xff;
					
						if (temp1==0xed)
							key_num=4;//4
						else
						{
							GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
							GPIO_ResetBits(GPIOA,GPIO_Pin_2);
							delay_us(1);
							temp1=GPIO_ReadInputData(GPIOA)&0xff;
						
							if (temp1==0xeb)
								key_num=7;//7
							else
								key_num=13;//0
						}
					}
				}
				break;
				case 0xd0:
				{
					GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
					GPIO_ResetBits(GPIOA,GPIO_Pin_0);
					delay_us(1);
					temp1=GPIO_ReadInputData(GPIOA)&0xff;
					if (temp1==0xde)
						key_num=2;
					else
					{
							GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
							GPIO_ResetBits(GPIOA,GPIO_Pin_1);
							delay_us(1);
							temp1=GPIO_ReadInputData(GPIOA)&0xff;
						
							if (temp1==0xdd)
								key_num=5;//5
							else
							{
								GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
								GPIO_ResetBits(GPIOA,GPIO_Pin_2);
								delay_us(1);
								temp1=GPIO_ReadInputData(GPIOA)&0xff;
							
								if (temp1==0xdb)
									key_num=8;//8
								else
									key_num=14;//
							}
					}
				}
				break;
				case 0xb0:
				{
					GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
					GPIO_ResetBits(GPIOA,GPIO_Pin_0);
					delay_us(1);
					temp1=GPIO_ReadInputData(GPIOA)&0xff;
					if (temp1==0xbe)
						key_num=3;
					else
					{
							GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
							GPIO_ResetBits(GPIOA,GPIO_Pin_1);
							delay_us(1);
							temp1=GPIO_ReadInputData(GPIOA)&0xff;
						
							if (temp1==0xbd)
								key_num=6;//6
							else
							{
								GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
								GPIO_ResetBits(GPIOA,GPIO_Pin_2);
								delay_us(1);
								temp1=GPIO_ReadInputData(GPIOA)&0xff;
							
								if (temp1==0xbb)
									key_num=9;
								else
									key_num=15;
							}
					}
				}
				break;
				case 0x70:
				{
					GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
					GPIO_ResetBits(GPIOA,GPIO_Pin_0);
					delay_us(1);
					temp1=(GPIO_ReadInputData(GPIOA)&0xff);
					if (temp1==0x7e)
						key_num=100;//+
					else
					{
						GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
						GPIO_ResetBits(GPIOA,GPIO_Pin_1);
						delay_us(1);
						temp1=GPIO_ReadInputData(GPIOA)&0xff;
					
						if (temp1==0x7d)
							key_num = 1000;//-
						else
						{
							GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
							GPIO_ResetBits(GPIOA,GPIO_Pin_2);
							delay_us(1);
							temp1=GPIO_ReadInputData(GPIOA)&0xff;
						
							if (temp1==0x7b)
								key_num=12;
							else
								key_num=16;
						}
					}
				}
				break;
				default :return 0;
			}		
		}
	}
	else if(temp == 0xf0)
	{												//当没有键按下后，将连按标志复位
		key_up=1;
	}
	return key_num;	
}


void Return_Num()
{
	if(k==1)
		{
			l++; //循环标志位
			k=0;//记录按键次数
		}
					switch (l)
	         {
						case 0:
					{
						arr[0]=key_scan();							
						if(arr[0]){
							k=1;
//							printf("input:%d\r\n",arr[0]);
						}
						break;
					}
						case 1:
					{
						arr[1]=key_scan();
						if(arr[1]){
							k=1;
//							printf("input:%d\r\n",arr[1]);
						}
						break;
					}
						case 2:
					{
						arr[2]=key_scan();
						if(arr[2]){
//							printf("input:%d\r\n",arr[2]);
							k=1;
						}
						break;
					}
						case 3:
					{
						arr[3]=key_scan();
						if(arr[3]){
//							printf("input:%d\r\n",arr[3]);
							k=1;
						}
						break;
					}
						case 4:
					{
						arr[4]=key_scan();
						if(arr[4]){
//							printf("input:%d\r\n",arr[4]);
							k=1;
						}
						break;
					}
						case 5:
					{
						arr[5]=key_scan();//4为正向，8-
						if(arr[5]){
//							printf("input:%d\r\n",arr[5]);
							k=1;
						}
						break;
					}
					
	         }
}
u8 Return_Data()
	{
		Return_Num();
		if(arr[0] && arr[1] && arr[2] && arr[3] && arr[4] && arr[5])
		{
			Data = arr[0]*100+arr[1]*10+arr[2];

			return Data;
	     }
	 }
int Return_Angle()
	 {
		Return_Num();
		if(arr[0] && arr[1] && arr[2] && arr[3] && arr[4] && arr[5])
		{

				H_A = arr[3]*10+arr[4];
			if(arr[5]==1000)
			{
				H_A = -H_A;
			}
		
			return H_A;
	     } 
	 }
/*************************************************本程序特点**********************************************************/
/*    1.连按与非连按：定义静态变量使得连按标志仅在本程序内有效。工作原理：初次进入键盘
        扫描函数，将连按标志置一，即初次按下；当有键按下的时候，会进入扫描函数，在扫描函数内
		将标志位挂起，即按键已按下；当程序执行完此次扫描，下次进入的时候，首先判断连按标志位
		与键盘是否按下，如果按下了，但连按标志位是挂起的，那不进入此函数。接下来判断键盘是否
		处于释放状态，如果键盘是释放的，则将标志位放下。否则，仍将标志位挂起。
	  2.端口的初始化，端口首先需要两种端口，一种是推完输出，另一种是上拉输入（没有信号时电平
		为高），首先将输出置低，如果有键按下，会得到相应的列的位置，近而分别置低相应的行，从
		而得到按下的按键所在的行。
	  3.本程序略显麻烦，但经过验证，完全可用。在写此程序时，网上有另一种方法，即不断改变端口
		的模式，判断列时如此程序，接下来将两种端口的模式换过来，将相应的列置低作为输出，判断
		相应行的位置，由是得到位置坐标，通过公式换算即可，如对程序实时性要求较高，可尝试此方
		法。
*/

/*************************************************心得体会**************************************************************/
/*	  1.使用if语句时一定要注意语句间的联系，如同本程序，键盘扫描需要依次将各个行线置低，并不
		是分别将行线置低。
	  2.熟悉输入输出方式，对不必要的端口置位复位进行取消，省略，以简化程序。
	  3.switch 语句在使用时，一定要注意break的使用，所以在写程序时，尤其像此类程序，可以套用
		复制粘贴的，首先确保最初的程序一定要没有基本错误。
	  4.有空的时候将变量标准化，利用define使代码简化易读易改
*/
