#include"led.h"
#include"stm32f10x.h"
void LED_Init(void)
{
   GPIO_InitTypeDef   GPIO_InitStructure;                  //����ṹ�����
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);    //ʱ��ʹ��
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;                 //�ĸ��˿ڣ�
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;          //�������
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;         //�ٶ�
   GPIO_Init(GPIOC, &GPIO_InitStructure);                  //��ʼ��
   GPIO_SetBits(GPIOC,GPIO_Pin_0);                         //��λ ����
 
}
