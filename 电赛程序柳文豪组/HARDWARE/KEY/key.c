#include "key.h"
#include "delay.h"
#include "sys.h"
  
//������ʼ������ 
//PA15��PC5 ���ó�����
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTAʱ��
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//PA 0 1 2 3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //���ó��������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//PA 4 5 6 7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA
	
} 
//����������



int key_scan(void)
{
	static u8 key_up=1;
	int key_num=15;
	u8 temp=0;								//�ж��е����ݻ�����
	u8 temp1=0;								//�ж��е����ݻ�����
	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);			//��������
	delay_us(10);
	temp=GPIO_ReadInputData(GPIOA)&0xff;				//����A�����ݼĴ�����ֵ
	delay_us(1);
	if (key_up&&(temp != 0xf0))							//�жϼ��Ƿ������Ƿ�����
	{
		delay_ms(10);						//����
		key_up=0;							//���м�����ʱ����������־λ����
		temp = GPIO_ReadInputData(GPIOA)&0xff;			//���������µõ�A��ֵ
		if(temp != 0xf0)
		{			
			switch(temp)								//������̰��µ���Ӧ����
			{
				case 0xe0:
				{
					
					GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);		//���δӵ�һ�����͵������У�����A�����ݣ��Ӷ��ж�
					GPIO_ResetBits(GPIOA,GPIO_Pin_0);										//����һ�еļ��̰��£��Ӷ�������Ӧ�ļ�ֵ
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
								key_num=0;//0
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
				default :return 14;
			}		
		}
	}
	else if(temp == 0xf0)
	{												//��û�м����º󣬽�������־��λ
		key_up=1;
	}
	return key_num;	
}
