#include "pid.h"
#include "usart.h"
#include "math.h"
#include "stdlib.h"
#include "delay.h"

PID pid;
extern u16 cy;
extern u16 cx;

void PID_init()
{
	pid.SetSpeed = 0.0;
	pid.ActualSpeed = 0.0;
	pid.err = 0.0;
	pid.err_last = 0.0;
	pid.integral = 0;
	pid.voltage = 0.0;
	pid.Kp = 1;
	pid.Ki = 0.15;
	pid.Kd = 0.1;
}

float PID_realize(float speed)
{
	if(cx <= 159 || cx >= 161)
	{
		pid.SetSpeed = speed;
	
		pid.ActualSpeed = cx;
		
		pid.err = pid.SetSpeed - pid.ActualSpeed;
		
		pid.integral += pid.Ki*pid.err; 
		if(abs(pid.integral) > 300)
		{
			pid.integral = 0;
		}
		pid.voltage = pid.Kp*pid.err + pid.Kd*(pid.err-pid.err_last) + pid.integral;
		
		pid.err_last=pid.err;
		
		pid.ActualSpeed=pid.voltage;
		
		u32 ActualSpeed_last = pid.ActualSpeed;
		
		return pid.ActualSpeed;
	}
	else{
		return pid.ActualSpeed;
	}
}

