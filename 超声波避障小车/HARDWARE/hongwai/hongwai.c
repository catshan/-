#include"hongwai.h"
#include"sys.h"
#include "timer.h"
void HongWaiL_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	 EXTI_InitTypeDef  EXTI_InitStructure;
	 NVIC_InitTypeDef  NVIC_InitStructure;
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF | RCC_APB2Periph_AFIO,ENABLE);
	 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//下拉输入
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	 GPIO_Init(GPIOF,&GPIO_InitStructure);//PF6,外部中断的输入IO口
	 
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource6);//映射PF6到EXTI中断线上
	 EXTI_InitStructure.EXTI_Line  =EXTI_Line6;
	 EXTI_InitStructure.EXTI_LineCmd =ENABLE;
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//上升沿触发外部中断
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	 EXTI_Init(&EXTI_InitStructure);//初始化中断线EXTI6上的中断模式
	 
	 NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//配置EXTI
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
	 NVIC_Init(&NVIC_InitStructure);

}

void HongWaiR_Init(void)//Ra--PF7
{
     GPIO_InitTypeDef  GPIO_InitStructure;
	 EXTI_InitTypeDef  EXTI_InitStructure;
	 NVIC_InitTypeDef  NVIC_InitStructure;
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF | RCC_APB2Periph_AFIO,ENABLE);
	 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//下拉输入
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	 GPIO_Init(GPIOF,&GPIO_InitStructure);//PF7,外部中断的输入IO口
	 
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource7);//映射PF7到EXTI中断线上
	 EXTI_InitStructure.EXTI_Line  =EXTI_Line7;
	 EXTI_InitStructure.EXTI_LineCmd =ENABLE;
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//上升沿触发外部中断
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	 EXTI_Init(&EXTI_InitStructure);//初始化中断线EXTI7上的中断模式
	 
	 NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//配置EXTI
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
	 NVIC_Init(&NVIC_InitStructure);


}



void EXTI9_5_IRQHandler (void)
{

  if(EXTI_GetFlagStatus(EXTI_Line6) != RESET)//车发生左偏
  {
			dianji1IN1=1;
			dianji1IN2=0;
			TIM_SetCompare2(TIM3,800); //左轮
			
			dianji2IN1=1;
			dianji2IN2=0;
			TIM_SetCompare3(TIM3,1999);//1100
   EXTI_ClearFlag(EXTI_Line6);
  }
  else if(EXTI_GetFlagStatus(EXTI_Line7)!=RESET)//车发生右偏
  {
			dianji1IN1=1;
			dianji1IN2=0;
			TIM_SetCompare3(TIM3,800); //左轮
			
			dianji2IN1=1;
			dianji2IN2=0;
			TIM_SetCompare2(TIM3,1999);//1100
	EXTI_ClearFlag(EXTI_Line7);

  }

}
