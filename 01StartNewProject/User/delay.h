#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f10x.h"
void TimingDelay_Decrement(void);
void Delay_10us(__IO uint32_t nTime);//��ʱ����λ��10΢��
void Delay_ms(__IO uint32_t nTime);//��ʱ����λ������
#endif
