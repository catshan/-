#include "capture.h"
/**PA0,通过输入捕获，获取输入信号的脉冲宽度(高电平持续时间)****/
void CAPTURE_Init(void)
{
 GPIO_InitTypeDef GPIO_IniStructure;
 TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
 TIM_ICInitTypeDef TIM_ICInitStructure;
 NVIC_InitTypeDef NVIC_InitStructure;
 
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
 
 GPIO_IniStructure.GPIO_Mode = GPIO_Mode_IPU;//PA0(ECHO回响信号输入脚)
 GPIO_IniStructure.GPIO_Pin = GPIO_Pin_0;
 GPIO_Init(GPIOA,&GPIO_IniStructure);
 
 GPIO_IniStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 //pc3(Trig)输入触发信号脚，持续给10us以上高电平
 GPIO_IniStructure.GPIO_Pin= GPIO_Pin_3;
 GPIO_IniStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOC,&GPIO_IniStructure);
 
 TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
 TIM_TimeBaseInitStructure.TIM_Period = 65535;//自动重装载值
 TIM_TimeBaseInitStructure.TIM_Prescaler = 71;//预分频值
 TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//T5,向上计数一次1us，总的计数溢出时间65536us
 
 TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//输入通道选择
 TIM_ICInitStructure.TIM_ICFilter = 0;//固定采样频率采样一次,不起到消除杂波的作用
 TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//通道上升沿捕获
 TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//CC1通道被配置为输入， IC1映射在TI1上
 TIM_ICInitStructure.TIM_ICPrescaler= TIM_ICPSC_DIV1;//一次上升沿（下降沿）即触发捕获
 TIM_ICInit(TIM2,&TIM_ICInitStructure);
 
 TIM_ITConfig(TIM2,TIM_IT_CC1|TIM_IT_Update,ENABLE);//中触发类型：更新（溢出）、捕获/比较
 NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
 NVIC_Init(&NVIC_InitStructure);//开中断，设置中断触发类型
 
 TIM_Cmd(TIM2,ENABLE);//使能定时器，开始工作

}
//2个全局变量
u8  TIM2CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM2CH1_CAPTURE_VAL;	//输入捕获值
 
//定时器5中断服务程序
/***********************************************************************
IC通道初始化设置为上升沿触发捕获，设置捕获值为0，设置计数器值也为0 ，IC通道极性选择为下降沿
下一次下降沿触发捕获，将计数器的值赋给捕获值。
但要注意一个问题：单次高电平持续时间可能超过一次溢出时间，所以要考虑定时器溢出次数！！
中断函数作用：模拟一个软件8位寄存器，低6位存储溢出次数。
  bit7         bit6                 bit5-0
  捕获标志     捕获高电平标志       捕获高电平后定时器溢出次数
************************************************************************/	 
//定时器5中断服务程序	 
void TIM2_IRQHandler(void)
{ 

 	if((TIM2CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{ //最大测量范围4m对应Echo输入23.53ms的高电平,单次TIM溢出需要65.536ms 
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM2CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM2CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM2CH1_CAPTURE_STA|=0X80;//强制标记成功捕获了一次
					TIM2CH1_CAPTURE_VAL=0XFFFF;
				}else TIM2CH1_CAPTURE_STA++;
			}	 
		} 
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM2CH1_CAPTURE_STA&0X40)//前一次捕获了上升沿，此次捕获到一个下降沿 		
			{	  			
				TIM2CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次上升沿
				TIM2CH1_CAPTURE_VAL=TIM_GetCapture1(TIM2);
		   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
			TIM2CH1_CAPTURE_STA=0;			//清空
			TIM2CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);//定时器从0开始重新计数
			TIM2CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
 
}
