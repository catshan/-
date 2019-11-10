#ifndef __PID_H
#define __PID_H

#include "sys.h"

typedef struct
{
	float SetSpeed; //�����趨ֵ
	float ActualSpeed; //����ʵ��ֵ
	float err; //����ƫ��ֵ
	float err_last; //������һ��ƫ��ֵ
	float Kp,Ki,Kd; //������������֡�΢��ϵ��
	float voltage; //�����ѹֵ������ִ�����ı�����
	float integral; //�������ֵ
}PID;

void PID_init(void);
float PID_realize(float speed);

#endif
