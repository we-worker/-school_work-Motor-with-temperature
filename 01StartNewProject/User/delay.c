#include "delay.h"
__IO uint32_t TimingDelay; //SysTick计数变量

/*全局变量TimingDelay减一函数，直到0为止*/
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

/*延时nTime*10微秒*/
void Delay_10us(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;
  while(TimingDelay != 0);   //一直等到TimingDelay减到0为止
}
/*延时nTime毫秒*/
void Delay_ms(__IO uint32_t nTime)
{ 
	uint32_t i;
	i=nTime;
	while(i--)            //一直等到i减到0为止，i每Delay_10us(100)即1毫秒减一
		Delay_10us(100);
}
