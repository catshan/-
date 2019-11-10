/*************************************************************************************
can.c
@author : ICE COFFCE
@action : 主函数
@data : 2018.12.14
@founction :
		初始化及can发送以及接收
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

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM2中断,允许更新中断
    
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设
		
						 
}
//dac    gonglvqiehuan
void TIM4_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM4, ENABLE);  //使能TIMx外设
							 
}
//定时器2中断服务程序
void TIM2_IRQHandler(void)   //TIM2中断
{

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
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
		//发送8个字节0 cmd 电流整数位 电流小数位 电压整数位 电压小数位 功率整数位 功率小数位
		}
}


void TIM4_IRQHandler(void)   //TIM4中断
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );			//清除TIMx的中断待处理位:TIM 中断源 
			
        Can_Receive_Msg(CANBUF_RX);
		}
}







int main(void)    //主函数     **************************************************************
{

    //CAN工作模式;CAN_Mode_Normal(0)：普通模式，CAN_Mode_LoopBack(1)：环回模式
    u8 key,i;
	u16 adcx,adcy,adcz;
	SystemInit();
    delay_init();	   	 //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
    uart_init(115200);	 	//串口初始化为115200
//	DAC5571_Init();
//	OLED_Init();
    LTC1473_Init();
	LTC1473_Change(LTC1473_MODE_POWER);
	Adc_Init();
	INA226_Init();
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_3tq,3,CAN_Mode_Normal);

      TIM2_Int_Init(9,7199);  //一秒发送一百次 10ms发送一次 
//    TIM2_Int_Init(999,7199); //一秒接收十次 100ms接收一次 	
    while(1)
    { 

/******************************************************************************************OLED显示电流电压功率
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
        //		delay_ms(1000)；


		printf("电流:%.2fA\r\n",INIA226_GetCurrent());
		printf("总线电压:%.2fV\r\n",INA226_GetBusVoltage());
		printf("功率:%.2fW\r\n",INA226_GetPower());
****************************************************************************************
***************************************************************************************/
//		printf("DAC接收的data=0x%02x\r\n",VOUT(3));//0011 0110


        if(Can_Receive_Msg(CANBUF_RX))//接收到有数据
        {
		    if((CANBUF_RX[0]=0)&&(CANBUF_RX[1]=2)&&(CANBUF_RX[2]=0)&&(CANBUF_RX[3]=0)&&(CANBUF_RX[4]=0)&&(CANBUF_RX[5]=0)&&(CANBUF_RX[6]=0)&&(CANBUF_RX[7]=1))
			{
				LTC1473_Change(LTC1473_MODE_POWER);    //接收到指定值切换为电池供电
			}
			if((CANBUF_RX[0]=0)&&(CANBUF_RX[1]=2)&&(CANBUF_RX[2]=0)&&(CANBUF_RX[3]=0)&&(CANBUF_RX[4]=0)&&(CANBUF_RX[5]=0)&&(CANBUF_RX[6]=0)&&(CANBUF_RX[7]=2))
			{
				LTC1473_Change(LTC1473_MODE_CAP);       //接收到指定字节切换为电容供电
			}
        }
//	else
//	{
//		printf("收不到啊\r\n");
//		delay_ms(1000);
//	}

	
//	    CANBUF_TX[0] = INIA226_GetCurrent();
//		CANBUF_TX[1] = INA226_GetBusVoltage();
//		CANBUF_TX[2] = INA226_GetPower();
///////////////////////////////////////////////////////////////adc测电源电压电容电压以及输出电压
// 	    adcx =Get_Adc_Average(ADC_Channel_0,10);
//        adcy =Get_Adc_Average(ADC_Channel_1,10);
//        adcz =Get_Adc_Average(ADC_Channel_4,10);
//        temp =(float)adcx *(3.3/4096);
//        printf("CAP电压为%f\r\n",temp*11);//电源供电电压
//        temp =(float)adcy *(3.3/4096);
//        printf("VIN电压为%f\r\n",temp*11+0.232);//电容供电电压
//        temp =(float)adcz *(3.3/4096);
//        printf("OUT电压为%f\r\n",temp*11+0.268);//输出电压  
//        printf("\r\n");

//		printf("Hello,Good morning!\r\n");
//        delay_ms(1000);

   }
} 

