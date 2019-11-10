#include "capture.h"
/**PA0,ͨ�����벶�񣬻�ȡ�����źŵ�������(�ߵ�ƽ����ʱ��)****/
void CAPTURE_Init(void)
{
 GPIO_InitTypeDef GPIO_IniStructure;
 TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
 TIM_ICInitTypeDef TIM_ICInitStructure;
 NVIC_InitTypeDef NVIC_InitStructure;
 
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
 
 GPIO_IniStructure.GPIO_Mode = GPIO_Mode_IPU;//PA0(ECHO�����ź������)
 GPIO_IniStructure.GPIO_Pin = GPIO_Pin_0;
 GPIO_Init(GPIOA,&GPIO_IniStructure);
 
 GPIO_IniStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 //pc3(Trig)���봥���źŽţ�������10us���ϸߵ�ƽ
 GPIO_IniStructure.GPIO_Pin= GPIO_Pin_3;
 GPIO_IniStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOC,&GPIO_IniStructure);
 
 TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
 TIM_TimeBaseInitStructure.TIM_Period = 65535;//�Զ���װ��ֵ
 TIM_TimeBaseInitStructure.TIM_Prescaler = 71;//Ԥ��Ƶֵ
 TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//T5,���ϼ���һ��1us���ܵļ������ʱ��65536us
 
 TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//����ͨ��ѡ��
 TIM_ICInitStructure.TIM_ICFilter = 0;//�̶�����Ƶ�ʲ���һ��,���������Ӳ�������
 TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//ͨ�������ز���
 TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//CC1ͨ��������Ϊ���룬 IC1ӳ����TI1��
 TIM_ICInitStructure.TIM_ICPrescaler= TIM_ICPSC_DIV1;//һ�������أ��½��أ�����������
 TIM_ICInit(TIM2,&TIM_ICInitStructure);
 
 TIM_ITConfig(TIM2,TIM_IT_CC1|TIM_IT_Update,ENABLE);//�д������ͣ����£������������/�Ƚ�
 NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
 NVIC_Init(&NVIC_InitStructure);//���жϣ������жϴ�������
 
 TIM_Cmd(TIM2,ENABLE);//ʹ�ܶ�ʱ������ʼ����

}
//2��ȫ�ֱ���
u8  TIM2CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM2CH1_CAPTURE_VAL;	//���벶��ֵ
 
//��ʱ��5�жϷ������
/***********************************************************************
ICͨ����ʼ������Ϊ�����ش����������ò���ֵΪ0�����ü�����ֵҲΪ0 ��ICͨ������ѡ��Ϊ�½���
��һ���½��ش������񣬽���������ֵ��������ֵ��
��Ҫע��һ�����⣺���θߵ�ƽ����ʱ����ܳ���һ�����ʱ�䣬����Ҫ���Ƕ�ʱ�������������
�жϺ������ã�ģ��һ�����8λ�Ĵ�������6λ�洢���������
  bit7         bit6                 bit5-0
  �����־     ����ߵ�ƽ��־       ����ߵ�ƽ��ʱ���������
************************************************************************/	 
//��ʱ��5�жϷ������	 
void TIM2_IRQHandler(void)
{ 

 	if((TIM2CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{ //��������Χ4m��ӦEcho����23.53ms�ĸߵ�ƽ,����TIM�����Ҫ65.536ms 
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM2CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM2CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM2CH1_CAPTURE_STA|=0X80;//ǿ�Ʊ�ǳɹ�������һ��
					TIM2CH1_CAPTURE_VAL=0XFFFF;
				}else TIM2CH1_CAPTURE_STA++;
			}	 
		} 
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			if(TIM2CH1_CAPTURE_STA&0X40)//ǰһ�β����������أ��˴β���һ���½��� 		
			{	  			
				TIM2CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ��������
				TIM2CH1_CAPTURE_VAL=TIM_GetCapture1(TIM2);
		   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
			TIM2CH1_CAPTURE_STA=0;			//���
			TIM2CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);//��ʱ����0��ʼ���¼���
			TIM2CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
 
}
