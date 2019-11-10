/*************************************************************************************
can.c
@author : ICECOFFCE
@action : DAC������
@data : 2018.12.14
@founction : 
		��������ѹ�����λ3.3v
***************************************************************************************/
#include "dac.h"
#include "delay.h"
#include "stm32f10x_tim.h"
#include "usart.h"
#include "misc.h"
#include "myiic.h"



void write1()
{
	IIC_SDA1 = 1;
	delay_us(4);
	IIC_SCL1 = 1;
	delay_us(4);
	IIC_SCL1 = 0;
	delay_us(4);
}
void write0()
{
	IIC_SDA1 = 0;
	delay_us(4);
	IIC_SCL1 = 1;
	delay_us(4);
	IIC_SCL1 = 0;
	delay_us(4);
}
/*****************************************************************
��iic���߷���һ���ֽ�����
data�Ƿ��͵����� �޷���ֵ
******************************************************************/
void WriteOneByte(u8 data)    //д�ֽ�
{
	unsigned char i;
	for(i=8;i>0;i--)
	{
		if(data&0x80)
		{
			write1();
		}
		else
		{
			write0();
		}
		data <<= 1;
	}
}
u8 DAC5571_WriteData(u8 data)    //dacд����
{
	u8 res = 0;
	IIC1_Start();
	IIC1_Send_Byte(0x98);//1001 1000
  res = IIC1_Wait_Ack();
	if(!res)
	{
		IIC1_Send_Byte(data>>4);
	}
	else
	{
		printf("debug 1:%d\r\n",res);
		return 0xff;
	}
  res = IIC1_Wait_Ack();	
	if(!res)
	{
		//f:1111
		IIC1_Send_Byte(data&0x0f);
	}
	else
	{
		printf("debug:2\r\n");
		return 0xff;
	}	
	IIC1_Wait_Ack();
	IIC1_Stop();
	
	return 0;
}

//0~3.3

u8 VOUT(float val)     //��ѹֵ
{
	u8 data;
	if(val>5)
	{
		return 0x00;
	}	
	data = val/3.3*256;
	if(DAC5571_WriteData(data))
	{
		return 0x00;
	}
	return data;
}



//��ʼ��5571
void DAC5571_Init()
{
	//IIC
	IIC1_Init();
}














