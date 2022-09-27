#include "control.h"
#include "main.h"

void Set_fan_speed(unsigned int val){
	if(val>pwm_LIMIT)
		val=pwm_LIMIT;
	
	TIM1->CCR2=val;
	
	
}

/* USER CODE END 1 */

