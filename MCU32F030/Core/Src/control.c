#include "control.h"
#include "main.h"





PID speed_pid={80,1,100,   0,0,0   ,0  ,0.2,0};

//ͨ��pid
int Fan_pid(PID *s_PID, int speed)
{
	int iError, output = 0;
	iError = s_PID->target - speed; //���ֵ����
	s_PID->error_acc += iError;		   //����
	//�ܻ������Ʒ���
	if(s_PID->error_acc>25)
		s_PID->error_acc=25;
	if(s_PID->error_acc<-20)
		s_PID->error_acc=-20;
	

	output = s_PID->kp * iError + s_PID->ki * s_PID->error_acc * 0.5f + s_PID->kd * iError - s_PID->lastError;
	output = s_PID->filter * output + (1 - s_PID->filter) * s_PID->lastFilter; //�˲�����

	s_PID->lastFilter = output; //�˲�ֵ�洢
	s_PID->lastError = iError;	// errorֵ�洢
	
	return (output);
}

void Set_fan_speed(unsigned int val){
	
	if(val<=5){
		speed_pid.kp=20;
		speed_pid.ki=0.5;
		speed_pid.kd=20;
	}
	else if(val>7){
		speed_pid.kp=80;
		speed_pid.ki=1;
		speed_pid.kd=100;
	}
	
	speed_pid.target=val;
}

/* USER CODE END 1 */

