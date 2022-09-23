#include "stm32f10x.h"
#include "misc.h"
#include "delay.h"

//RCC_Configuration(), NVIC_Configuration(), GPIO_Config() 在引用前要声明一下。
void RCC_Configuration(void); //系统时钟配置
void NVIC_Configuration(void); //中断配置
void GPIO_Config(void); //通用输入输出端口配置

int main(void)
{
	RCC_Configuration(); //时钟初始化
	GPIO_Config(); //端口初始化
	NVIC_Configuration();  //中断初始化
	
	while(1)
	{
		
		Delay_ms(1000);
		GPIO_SetBits(GPIOA,GPIO_Pin_15);   //把PC15置1
		Delay_ms(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_15);  //把PC15置0
		
	}
	
}

/*系统时钟配置函数*/
void RCC_Configuration(void)
{
	
//        SystemInit();//源自system_stm32f10x.c文件,只需要调用此函数,则可完成RCC的默认配置.具体请看2_RCC
	
				//我们还是自己来配置吧
	      RCC_DeInit();

				RCC_HSEConfig(RCC_HSE_OFF);  //禁止外部时钟

        RCC_HSICmd(ENABLE);          //打开内部时钟
        
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
        //PLL 倍频
        RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16);        //内部时钟倍频*16。内部晶振8MHz，除以2进入PLL，倍频16，则PLL输出64MHz
        RCC_PLLCmd(ENABLE);                        										//使能倍频
                                                                                                         
				//等待指定的 RCC 标志位设置成功 等待PLL初始化成功
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
        }

        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);        //以PLL输出作为系统时钟。

        /**************************************************
        获取RCC的信息,调试用
        请参考RCC_ClocksTypeDef结构体的内容,当时钟配置完成后,
        里面变量的值就直接反映了器件各个部分的运行频率
        ***************************************************/
                
        while(RCC_GetSYSCLKSource() != 0x08){}		//返回0x08说明使用PLL作为系统时钟成功
					
}

/*中断配置函数*/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;  //NVIC中断向量结构体
	RCC_ClocksTypeDef RCC_Clocks;  //RCC时钟结构体
  /* Configure the NVIC Preemption Priority Bits */  
  /* Configure one bit for preemption priority */
  /* 优先级组 说明了抢占优先级所用的位数，和子优先级所用的位数。这里是2，2*/    
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		   
  

	  /* Enable the RTC Interrupt 使能实时时钟中断*/
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;					//配置外部中断源（秒中断） 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
	
	/*使能定时中断*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;												//指定中断源
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;							
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;										//指定响应优先级别
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure); 
	
	//设置嘀嗒时钟中断
	RCC_GetClocksFreq(&RCC_Clocks);		//获取系统时钟
	if (SysTick_Config(RCC_Clocks.SYSCLK_Frequency/100000))		   //时钟节拍中断时10us一次  用于定时。 例如时钟频率48MHz，/480，则10us一次
  { 
    /* Capture error */ 
    while (1);
  } 
}

/*端口配置函数*/
void GPIO_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//使能GPIOA/GPIOC的总线，否则端口不能工作，如果不用这个端口，可以不用使能。
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);	

	//配置PA15为LED3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				     
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //口线翻转速度为50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	
	//配置PC12、PC11、PC10为LED0，LED1，LED2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;				 //PC10、PC11、PC12	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //口线翻转速度为50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
}
