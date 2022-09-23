#include "stm32f10x.h"
#include "misc.h"
#include "delay.h"

//RCC_Configuration(), NVIC_Configuration(), GPIO_Config() ������ǰҪ����һ�¡�
void RCC_Configuration(void); //ϵͳʱ������
void NVIC_Configuration(void); //�ж�����
void GPIO_Config(void); //ͨ����������˿�����

int main(void)
{
	RCC_Configuration(); //ʱ�ӳ�ʼ��
	GPIO_Config(); //�˿ڳ�ʼ��
	NVIC_Configuration();  //�жϳ�ʼ��
	
	while(1)
	{
		
		Delay_ms(1000);
		GPIO_SetBits(GPIOA,GPIO_Pin_15);   //��PC15��1
		Delay_ms(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_15);  //��PC15��0
		
	}
	
}

/*ϵͳʱ�����ú���*/
void RCC_Configuration(void)
{
	
//        SystemInit();//Դ��system_stm32f10x.c�ļ�,ֻ��Ҫ���ô˺���,������RCC��Ĭ������.�����뿴2_RCC
	
				//���ǻ����Լ������ð�
	      RCC_DeInit();

				RCC_HSEConfig(RCC_HSE_OFF);  //��ֹ�ⲿʱ��

        RCC_HSICmd(ENABLE);          //���ڲ�ʱ��
        
        while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)        
        {        
        }

//        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

//        FLASH_SetLatency(FLASH_Latency_2);
				
        /* HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        //APB2
        RCC_PCLK2Config(RCC_HCLK_Div1);
        //APB1
        RCC_PCLK1Config(RCC_HCLK_Div2);
        //PLL ��Ƶ
        RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16);        //�ڲ�ʱ�ӱ�Ƶ*16���ڲ�����8MHz������2����PLL����Ƶ16����PLL���64MHz
        RCC_PLLCmd(ENABLE);                        										//ʹ�ܱ�Ƶ
                                                                                                         
				//�ȴ�ָ���� RCC ��־λ���óɹ� �ȴ�PLL��ʼ���ɹ�
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
        }

        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);        //��PLL�����Ϊϵͳʱ�ӡ�

        /**************************************************
        ��ȡRCC����Ϣ,������
        ��ο�RCC_ClocksTypeDef�ṹ�������,��ʱ��������ɺ�,
        ���������ֵ��ֱ�ӷ�ӳ�������������ֵ�����Ƶ��
        ***************************************************/
                
        while(RCC_GetSYSCLKSource() != 0x08){}		//����0x08˵��ʹ��PLL��Ϊϵͳʱ�ӳɹ�
					
}

/*�ж����ú���*/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;  //NVIC�ж������ṹ��
	RCC_ClocksTypeDef RCC_Clocks;  //RCCʱ�ӽṹ��
  /* Configure the NVIC Preemption Priority Bits */  
  /* Configure one bit for preemption priority */
  /* ���ȼ��� ˵������ռ���ȼ����õ�λ�����������ȼ����õ�λ����������2��2*/    
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		   
  

	  /* Enable the RTC Interrupt ʹ��ʵʱʱ���ж�*/
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;					//�����ⲿ�ж�Դ�����жϣ� 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
	
	/*ʹ�ܶ�ʱ�ж�*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;												//ָ���ж�Դ
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;							
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;										//ָ����Ӧ���ȼ���
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure); 
	
	//�������ʱ���ж�
	RCC_GetClocksFreq(&RCC_Clocks);		//��ȡϵͳʱ��
	if (SysTick_Config(RCC_Clocks.SYSCLK_Frequency/100000))		   //ʱ�ӽ����ж�ʱ10usһ��  ���ڶ�ʱ�� ����ʱ��Ƶ��48MHz��/480����10usһ��
  { 
    /* Capture error */ 
    while (1);
  } 
}

/*�˿����ú���*/
void GPIO_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//ʹ��GPIOA/GPIOC�����ߣ�����˿ڲ��ܹ����������������˿ڣ����Բ���ʹ�ܡ�
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);	

	//����PA15ΪLED3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				     
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���߷�ת�ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	
	//����PC12��PC11��PC10ΪLED0��LED1��LED2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;				 //PC10��PC11��PC12	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���߷�ת�ٶ�Ϊ50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
}
