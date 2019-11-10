#include "mytim.h"
#include "main.h"


void MY_TIM2_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBase;
	NVIC_InitTypeDef NVIC_Initure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBase.TIM_Period=arr;
	TIM_TimeBase.TIM_Prescaler=psc;
    TIM_TimeBase.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBase.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBase);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_Initure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_Initure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Initure.NVIC_IRQChannelSubPriority=2;
	NVIC_Initure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initure);
	
	TIM_Cmd(TIM2,ENABLE);		//	Ê¹ÄÜTIM2
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		
		Mark++;

	}

}
