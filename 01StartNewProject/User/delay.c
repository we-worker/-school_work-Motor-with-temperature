#include "delay.h"
__IO uint32_t TimingDelay; //SysTick��������

/*ȫ�ֱ���TimingDelay��һ������ֱ��0Ϊֹ*/
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

/*��ʱnTime*10΢��*/
void Delay_10us(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;
  while(TimingDelay != 0);   //һֱ�ȵ�TimingDelay����0Ϊֹ
}
/*��ʱnTime����*/
void Delay_ms(__IO uint32_t nTime)
{ 
	uint32_t i;
	i=nTime;
	while(i--)            //һֱ�ȵ�i����0Ϊֹ��iÿDelay_10us(100)��1�����һ
		Delay_10us(100);
}
