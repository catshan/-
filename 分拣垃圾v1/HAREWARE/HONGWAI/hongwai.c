#include "hongwai.h"
#include "sys.h"
void hongwai_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //∏°ø’ ‰»Î
    GPIO_Init(GPIOF, &GPIO_InitStructure);//≥ı ºªØGPIO
}
