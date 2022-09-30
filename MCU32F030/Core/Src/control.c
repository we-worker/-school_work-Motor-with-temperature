#include "control.h"
#include "main.h"





PID speed_pid={3.8,0,1.2,   0,0,0   ,0  ,0.2,0};

//通用pid
int Fan_pid(PID *s_PID, int speed)
{
	int iError, output = 0;
	iError = s_PID->target - speed; //误差值计算
	s_PID->error_acc += iError;		   //积分

	output = s_PID->kp * iError + s_PID->ki * s_PID->error_acc * 0.5f + s_PID->kd * iError - s_PID->lastError;
	output = s_PID->filter * output + (1 - s_PID->filter) * s_PID->lastFilter; //滤波操作

	s_PID->lastFilter = output; //滤波值存储
	s_PID->lastError = iError;	// error值存储
	
	if(output>pwm_LIMIT)
		output=pwm_LIMIT;
	return (output);
}

void Set_fan_speed(unsigned int val){
	//if(val>pwm_LIMIT)
	//	val=pwm_LIMIT;
	
	//TIM1->CCR2=val;
	speed_pid.target=val;
	
}

/* USER CODE END 1 */

