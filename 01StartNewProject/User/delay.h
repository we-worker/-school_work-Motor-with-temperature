#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f10x.h"
void TimingDelay_Decrement(void);
void Delay_10us(__IO uint32_t nTime);//延时，单位：10微秒
void Delay_ms(__IO uint32_t nTime);//延时，单位：毫秒
#endif
