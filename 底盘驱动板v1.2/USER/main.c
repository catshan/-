/*************************************************************************************
can.c
@author : ICE COFFCE
@action : ������
@data : 2018.12.14
@founction :
		��ʼ����can�����Լ�����
***************************************************************************************/



#include "myiic.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "can.h"
#include "INA226.h"

#include "dac.h"
#include "oled.h"
#include "LTC1473.h"
#include "ADC.h"

    u8 CANBUF_RX[8];
    u16 CANBUF_TX[8];
	u8 res;
	float temp,tmp;
	

void TIM2_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM2�ж�,��������ж�
    
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����
		
						 
}
//dac    gonglvqiehuan
void TIM4_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx����
							 
}
//��ʱ��2�жϷ������
void TIM2_IRQHandler(void)   //TIM2�ж�
{

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		CAN_WakeUp(CAN1);
		CANBUF_TX[0]=0;
		CANBUF_TX[1]=1;
		CANBUF_TX[2]=INIA226_GetCurrent()*10;
		tmp=INIA226_GetCurrent();
		tmp *= 1000;
		CANBUF_TX[3]=(int)tmp%100;
		CANBUF_TX[4]=INA226_GetBusVoltage();
		tmp = INA226_GetBusVoltage();
		tmp *= 100;
		CANBUF_TX[5]=(int)tmp%100;
		CANBUF_TX[6]=INA226_GetPower()*100;
		tmp  = INA226_GetPower();
		tmp  *=10000;
	    res=Can_Send_Msg(CANBUF_TX,8);
		CAN_Sleep(CAN1);
		printf("res:%d\r\n",res);
		//����8���ֽ�0 cmd ��������λ ����С��λ ��ѹ����λ ��ѹС��λ ��������λ ����С��λ
		}
}


void TIM4_IRQHandler(void)   //TIM4�ж�
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );			//���TIMx���жϴ�����λ:TIM �ж�Դ 
			
        Can_Receive_Msg(CANBUF_RX);
		}
}







int main(void)    //������     **************************************************************
{

    //CAN����ģʽ;CAN_Mode_Normal(0)����ͨģʽ��CAN_Mode_LoopBack(1)������ģʽ
    u8 key,i;
	u16 adcx,adcy,adcz;
	SystemInit();
    delay_init();	   	 //��ʱ������ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
//	DAC5571_Init();
//	OLED_Init();
    LTC1473_Init();
	LTC1473_Change(LTC1473_MODE_POWER);
	Adc_Init();
	INA226_Init();
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_3tq,3,CAN_Mode_Normal);

      TIM2_Int_Init(9,7199);  //һ�뷢��һ�ٴ� 10ms����һ�� 
//    TIM2_Int_Init(999,7199); //һ�����ʮ�� 100ms����һ�� 	
    while(1)
    { 

/******************************************************************************************OLED��ʾ������ѹ����
*******************************************************************************************
		float i = INIA226_GetCurrent();
		i *= 1000;


		OLED_ShowNum(75,0,i/1000,2,16);
		OLED_ShowString(100,0,".",16);
		OLED_ShowNum(103,0,(int)i%1000,2,16);


	  i = INA226_GetBusVoltage();
		i *= 100;

			OLED_ShowNum(70,3,i/100,2,16);
			OLED_ShowString(90,3,".",16);
			OLED_ShowNum(93,3,(int)i/10%10,2,16);
		OLED_ShowNum(110,3,(int)i%100,2,16);


		i = INA226_GetPower();
		i *= 100;

			OLED_ShowNum(75,6,i/100,2,16);
				OLED_ShowString(100,6,".",16);
		OLED_ShowNum(103,6,(int)i%100,2,16);





//		OLED_Clear();
      OLED_ShowString(0,0,"I:",16);
		  OLED_ShowString(0,3,"U:",16);
		  OLED_ShowString(0,6,"P:",16);
        //		delay_ms(1000)��


		printf("����:%.2fA\r\n",INIA226_GetCurrent());
		printf("���ߵ�ѹ:%.2fV\r\n",INA226_GetBusVoltage());
		printf("����:%.2fW\r\n",INA226_GetPower());
****************************************************************************************
***************************************************************************************/
//		printf("DAC���յ�data=0x%02x\r\n",VOUT(3));//0011 0110


        if(Can_Receive_Msg(CANBUF_RX))//���յ�������
        {
		    if((CANBUF_RX[0]=0)&&(CANBUF_RX[1]=2)&&(CANBUF_RX[2]=0)&&(CANBUF_RX[3]=0)&&(CANBUF_RX[4]=0)&&(CANBUF_RX[5]=0)&&(CANBUF_RX[6]=0)&&(CANBUF_RX[7]=1))
			{
				LTC1473_Change(LTC1473_MODE_POWER);    //���յ�ָ��ֵ�л�Ϊ��ع���
			}
			if((CANBUF_RX[0]=0)&&(CANBUF_RX[1]=2)&&(CANBUF_RX[2]=0)&&(CANBUF_RX[3]=0)&&(CANBUF_RX[4]=0)&&(CANBUF_RX[5]=0)&&(CANBUF_RX[6]=0)&&(CANBUF_RX[7]=2))
			{
				LTC1473_Change(LTC1473_MODE_CAP);       //���յ�ָ���ֽ��л�Ϊ���ݹ���
			}
        }
//	else
//	{
//		printf("�ղ�����\r\n");
//		delay_ms(1000);
//	}

	
//	    CANBUF_TX[0] = INIA226_GetCurrent();
//		CANBUF_TX[1] = INA226_GetBusVoltage();
//		CANBUF_TX[2] = INA226_GetPower();
///////////////////////////////////////////////////////////////adc���Դ��ѹ���ݵ�ѹ�Լ������ѹ
// 	    adcx =Get_Adc_Average(ADC_Channel_0,10);
//        adcy =Get_Adc_Average(ADC_Channel_1,10);
//        adcz =Get_Adc_Average(ADC_Channel_4,10);
//        temp =(float)adcx *(3.3/4096);
//        printf("CAP��ѹΪ%f\r\n",temp*11);//��Դ�����ѹ
//        temp =(float)adcy *(3.3/4096);
//        printf("VIN��ѹΪ%f\r\n",temp*11+0.232);//���ݹ����ѹ
//        temp =(float)adcz *(3.3/4096);
//        printf("OUT��ѹΪ%f\r\n",temp*11+0.268);//�����ѹ  
//        printf("\r\n");

//		printf("Hello,Good morning!\r\n");
//        delay_ms(1000);

   }
} 

