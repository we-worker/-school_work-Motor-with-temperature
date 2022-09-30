#ifndef __control_H
#define __control_H

#define pwm_LIMIT 1000


typedef struct PID
{
	float kp;
	float ki;
	float kd;

	float error_acc;
	float lastError;
	float prevError;

	float target;

	float filter;
	float lastFilter;
} PID;


int Fan_pid(PID *s_PID, int speed);	  //输入参数：pid结构，当前位置 返回：直线pid控制值

void Set_fan_speed(unsigned int val);


#endif
