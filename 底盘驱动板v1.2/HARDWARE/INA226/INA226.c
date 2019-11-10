/*************************************************************************************
can.c
@author : ICECOFFCE
@action : INA226����ѹ��������
@data : 2018.12.14
@founction : 
		����ѹ��������
***************************************************************************************/
#include "INA226.h"
#include "delay.h"
#include "myiic.h"
#include "stm32f10x_tim.h"
#include "usart.h"
#include "misc.h"

INA226_INFO inaInfo;

void printInfoINA(void);

/*
��INA226���ж�����:
���ȸ���ָ�뵽addr
*/
u16 INA226_ReadData(u8 addr)
{
	u16 res = 0;
	//----1
	IIC_Start();
	IIC_Send_Byte(INA226_ADDR);
	res = IIC_Wait_Ack();
	if(res)
	{
		return 0xff;
	}
	IIC_Send_Byte(addr);
	res = IIC_Wait_Ack();
	if(res)
	{
		return 0xff;
	}	
	IIC_Stop();
	//---2
	IIC_Start();
	IIC_Send_Byte(INA226_ADDR|0x01);//������
	res = IIC_Wait_Ack();
	if(res)
	{
		return 0xff;
	}
	res = IIC_Read_Byte(1);
	res <<= 8;
	res |= IIC_Read_Byte(0);
	//printf("datah:0x%02x,datal:0x%02x\r\n",res,res);
	IIC_Stop();
	return res;
}

u8 INA226_WriteData(u8 addr,u16 data)
{
	u8 res;
	IIC_Start();
	IIC_Send_Byte(INA226_ADDR);
	res = IIC_Wait_Ack();
	if(res)
	{
		return 0xff;
	}
	IIC_Send_Byte(addr);
	res = IIC_Wait_Ack();
	if(res)
	{
		return 0xff;
	}
	IIC_Send_Byte(data>>8);
	res = IIC_Wait_Ack();
	if(res)
	{
		return 0xff;
	}
	IIC_Send_Byte(data&0x00ff);
	res = IIC_Wait_Ack();
	if(res)
	{
		return 0xff;
	}
	IIC_Stop();
	//printf("h:0x%02x,l:0x%02x\r\n",data>>8,data&0x00ff);
	return 0x66;
}

u8 INA226_Init(void)
{
	u8 tem = 0;
	TIM_TimeBaseInitTypeDef TIM_BaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	IIC_Init();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	while(INA226_ReadData(Addr_DieID) != Die_ID)
	{
		tem++;
		printf("Addr_DieID:%d\r\n",INA226_ReadData(Addr_DieID));
		delay_ms(100);
		if(tem>15)
		{
			return 0xff;
		}
	}
	INA226_WriteData(Addr_Config,0x43FF);
	INA226_WriteData(Addr_Calibration,0xA00/4.0449);//1mA/bit
	

	
	TIM_BaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_BaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_BaseInitStruct.TIM_Period = 1999;
	TIM_BaseInitStruct.TIM_Prescaler = 7199;
	TIM_TimeBaseInit(TIM3,&TIM_BaseInitStruct);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM3,ENABLE);
	return 0;
}

/**��ȡ���ߵ�ѹ 1.25mV/bit
	*��λ V
	*@return
**/
float INA226_GetBusVoltage()
{
	u16 data = INA226_ReadData(Addr_BusVoltage);
	return (data*1.25)/1000.0;
}
/**��ȡ���������ѹ 2.5uV/bit  (temp*125 + 50)/100
	*��λ mV
	*@return 
*/
float INA226_GetShuntVoltage()
{
	u16 data = INA226_ReadData(Addr_ShuntVoltage);
	if(data&0x8000)
	{
		data = ~(data-1);
	}
	return (data*2.5)/1000.0;
}
/**��ȡ���� 
	*��λ W
	*@return
*/
float INA226_GetPower()
{
	u16 data = INA226_ReadData(Addr_Power);
	return (data*2.5)/1000.0;
}
/**��ȡ���� 
	*��λ A
	*@return
*/
float INIA226_GetCurrent()
{
	u16 data = INA226_ReadData(Addr_Current)&0x7fff;
	return (data/10000.0); 
}

/**TIM6�жϺ���
	*�����ж�
	*@return
*/
void TIM3_IRQHandler(void)
{
	inaInfo.Current = INIA226_GetCurrent();
	inaInfo.Power = INA226_GetPower();
	inaInfo.BusVoltage = INA226_GetBusVoltage();
	//printInfoINA();
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}
/**��ӡ��·������Ϣ
	*���� ���ߵ�ѹ ����
	*@return
*/
void printInfoINA()
{
		printf("����:%.2fA\r\n",INIA226_GetCurrent());
		printf("���ߵ�ѹ:%.2fV\r\n",INA226_GetBusVoltage());
		printf("����:%.2fW\r\n",INA226_GetPower());
}
