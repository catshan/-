#ifndef _SORT_H
#define _SORT_H

#define Motor1_In1 PBout(10)//1的电机
#define Motor1_In2 PBout(11)
#define Motor2_In1 PEout(15)//2的电机
#define Motor2_In2 PEout(14)
#define Motor3_In1 PEout(1) //3的电机
#define Motor3_In2 PEout(0)
void Sort_Init(void);
void Motor1_go(void);
void Motor1_towards(void);
void Motor1_stop(void);
void Motor2_stop(void);
void Motor2_Down(void);
void Motor2_Up(void);
void Motor3_Down(void);
void Motor3_Up(void);
void Motor3_Stop(void);
void Put_In(void);
void Transport(void);
void Red_Recycle(void);
void Blue_Recycle(void);
void Orange_Recycle(void);
#endif
