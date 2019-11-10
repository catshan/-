#include"led.h"
#include"stm32f10x.h"
void LED_Init(void)
{
   GPIO_InitTypeDef   GPIO_InitStructure;                  //定义结构体变量
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);    //时钟使能
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;                 //哪个端口？
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;          //推挽输出
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;         //速度
   GPIO_Init(GPIOC, &GPIO_InitStructure);                  //初始化
   GPIO_SetBits(GPIOC,GPIO_Pin_0);                         //置位 点亮
 
}
