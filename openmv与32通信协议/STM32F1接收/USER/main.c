
/***********************************************************
*OPENMV和STM32F103通信
*2019/7/20
*
*
*
***********************************************************/


/* Includes ------------------------------------------------------------------*/
#include "delay.h"
#include "sys.h"
#include "usart.h"	 
#include "OPENMV.h"

/* Macro definitions ---------------------------------------------------------*/

/* Struct or Class definitions -----------------------------------------------*/

/* Extern global variables ---------------------------------------------------*/

/* Global variables ----------------------------------------------------------*/

/* Function declarations -----------------------------------------------------*/


/**
* @brief  main.c
* @param  None
* @retval None
*/
 int main(void)
 {
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart3_init(115200);		//PB10 11 用来处理openmv数据 处理程序在串口中断里面
	
	 while(1)
	 {
		 delay_ms(1000);
	 printf("hello");
	 }
  }	

/***************************END OF FILE************************************/
  