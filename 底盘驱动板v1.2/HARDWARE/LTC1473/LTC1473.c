/*************************************************************************************
can.c
@author : ICECOFFCE
@action : LTC1473的切换
@data : 2018.12.14
@founction : 
		初始化以及切换电源
***************************************************************************************/
#include "LTC1473.h"
#include "stdio.h"

void LTC1473_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//gpio
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	LTC1473_DIODE = 0;
	//LTC1473_Cmd(ENABLE);
}	

void LTC1473_Cmd(FunctionalState cmd)
{
	if(IS_FUNCTIONAL_STATE(cmd))
	{
		LTC1473_DIODE = ~cmd;		
	}
	
}
void LTC1473_Change(LTC1473_MODE mode)
{
	if(mode == LTC1473_MODE_POWER)
	{
		LTC1473_IN1 = 0;
		LTC1473_IN2 = 0;			
	}
	else if(mode == LTC1473_MODE_CAP) 
	{
		LTC1473_IN1 = 1;
		LTC1473_IN2 = 1;
	}
}
