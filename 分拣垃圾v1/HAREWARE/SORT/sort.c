#include "sort.h"
#include "timer.h"
#include "sys.h"
#include "delay.h"
u8 i;

void Sort_Init()
{
	TIM4->CCR1 = 10;
	TIM3->CCR2 = 1000;
	TIM3->CCR3 = 5000;
	TIM4->CCR2 = 5000;
//	delay_ms(1000);
}
void Motor1_go()
{
	Motor1_In1 = 0;
	Motor1_In2 = 1;
}

void Motor1_towards()
{
	Motor1_In1 = 1;
	Motor1_In2 = 0;
}

void Motor1_stop()
{
	Motor1_In1 = 0;
	Motor1_In2 = 0;
}

void Motor2_stop()
{

	Motor2_In1 = 0;
	Motor2_In2 = 0;
}

void Motor2_Down()
{
	Motor2_In1 = 0;
	Motor2_In2 = 1;
}

void Motor2_Up()
{
	Motor2_In1 = 1;
	Motor2_In2 = 0;
}
void Motor3_Up()
{
	Motor3_In1 = 1;
	Motor3_In2 = 0;
}
void Motor3_Down()
{
	Motor3_In1 = 0;
	Motor3_In2 = 1;
}
void Motor3_Stop()
{
	Motor3_In1 = 0;
	Motor3_In2 = 0;
}
void Put_In()
{
	TIM3->CCR1 = 4000;
	delay_ms(1000);
	TIM3->CCR1 = 1000;
	for(i=0;i<3;i++)
	{
	delay_ms(1000);
	}
	Motor3_Down();
	for(i=0;i<2;i++)
	{
	delay_ms(3000);
	}
	Motor3_Up();
	for(i=0;i<2;i++)
	{
	delay_ms(3000);
	}
	Motor3_Stop();
	TIM3->CCR1 = 4000;
}
void Transport()
{
	Motor2_Down();
	for(i=0;i<5;i++)
	{
	delay_ms(4950);
	}
	Motor2_stop();
	delay_ms(1000);
	TIM3->CCR4 = 2800;
	delay_ms(1000);
	TIM3->CCR4 = 4000;
	delay_ms(1000);
	Motor2_Up();
	for(i=0;i<5;i++)
	{
	delay_ms(4970);
	}
	Motor2_stop();
	delay_ms(100);
	Motor1_towards();
	for(i = 0;i<14;i++)
	{
	delay_ms(1000);
	}
	Motor1_stop();
	delay_ms(1000);
	TIM3->CCR4 = 2800;
	delay_ms(1000);
	Motor1_go();
	for(i = 0;i<14;i++)
	{
	delay_ms(1000);
	}
	Motor1_stop();
	delay_ms(100);

	
}
void Red_Recycle()
{
	TIM3->CCR2 = 1000;
	TIM4->CCR1 = 10;
	TIM3->CCR3 = 3000;
	TIM4->CCR2 = 3000;
	for(i=0;i<15;i++)
	{delay_ms(1000);}
	Sort_Init();
}
void Blue_Recycle()
{
	TIM3->CCR3 = 3000;
	TIM4->CCR2 = 5000;
	TIM4->CCR1 = 10;
	TIM3->CCR2 = 1000;
	for(i=0;i<10;i++)
	{delay_ms(1000);}
	Sort_Init();
}
void Orange_Recycle()
{
	TIM3->CCR2 = 3400;
	TIM4->CCR1 = 3000;
	TIM3->CCR3 = 5000;
	TIM4->CCR2 = 5000;
	for(i=0;i<10;i++)
	{delay_ms(1000);}
	Sort_Init();
}


