#include "key.h"
#include "delay.h"
#include "sys.h"

int Data=0,H_A=0,dir=0,k=0,l=0;	  
u16 arr[6]={0,0,0,0,0,0};
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
	int key_num=0;
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
	{												//��û�м����º󣬽�������־��λ
		key_up=1;
	}
	return key_num;	
}


void Return_Num()
{
	if(k==1)
		{
			l++; //ѭ����־λ
			k=0;//��¼��������
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
						arr[5]=key_scan();//4Ϊ����8-
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
/*************************************************�������ص�**********************************************************/
/*    1.����������������徲̬����ʹ��������־���ڱ���������Ч������ԭ�����ν������
        ɨ�躯������������־��һ�������ΰ��£����м����µ�ʱ�򣬻����ɨ�躯������ɨ�躯����
		����־λ���𣬼������Ѱ��£�������ִ����˴�ɨ�裬�´ν����ʱ�������ж�������־λ
		������Ƿ��£���������ˣ���������־λ�ǹ���ģ��ǲ�����˺������������жϼ����Ƿ�
		�����ͷ�״̬������������ͷŵģ��򽫱�־λ���¡������Խ���־λ����
	  2.�˿ڵĳ�ʼ�����˿�������Ҫ���ֶ˿ڣ�һ���������������һ�����������루û���ź�ʱ��ƽ
		Ϊ�ߣ������Ƚ�����õͣ�����м����£���õ���Ӧ���е�λ�ã������ֱ��õ���Ӧ���У���
		���õ����µİ������ڵ��С�
	  3.�����������鷳����������֤����ȫ���á���д�˳���ʱ����������һ�ַ����������ϸı�˿�
		��ģʽ���ж���ʱ��˳��򣬽����������ֶ˿ڵ�ģʽ������������Ӧ�����õ���Ϊ������ж�
		��Ӧ�е�λ�ã����ǵõ�λ�����꣬ͨ����ʽ���㼴�ɣ���Գ���ʵʱ��Ҫ��ϸߣ��ɳ��Դ˷�
		����
*/

/*************************************************�ĵ����**************************************************************/
/*	  1.ʹ��if���ʱһ��Ҫע���������ϵ����ͬ�����򣬼���ɨ����Ҫ���ν����������õͣ�����
		�Ƿֱ������õ͡�
	  2.��Ϥ���������ʽ���Բ���Ҫ�Ķ˿���λ��λ����ȡ����ʡ�ԣ��Լ򻯳���
	  3.switch �����ʹ��ʱ��һ��Ҫע��break��ʹ�ã�������д����ʱ�������������򣬿�������
		����ճ���ģ�����ȷ������ĳ���һ��Ҫû�л�������
	  4.�пյ�ʱ�򽫱�����׼��������defineʹ������׶��׸�
*/
