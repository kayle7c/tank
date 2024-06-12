#include "stm32f10x.h"                  // Device header

void tb6612_Init(void)
{

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
	GPIO_InitTypeDef GPIO_InitStructure;//配置输出pwm的GPIO
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出是因为此时是由片上外设（TIM2的ch1通道）而非输出数据寄存器
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	
	
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2); //选择时钟（内部）
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//配置时基单元
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; //预分频系数（1，2，4）
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInitStruct.TIM_Period = 1000-1;      //ARR（自动重装载值）0~65535
	TIM_TimeBaseInitStruct.TIM_Prescaler = 1440-1;    //PSC（预分频值）    0~65535
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	//配置输出比较通道
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure); //初始化结构体变量
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;      //输出比较模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //选择极性（high不翻转，low翻转）
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //输出状态
	TIM_OCInitStructure.TIM_Pulse = 0;                   //CCR
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	
	TIM_OCStructInit(&TIM_OCInitStructure); //初始化结构体变量
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;      //输出比较模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //选择极性（high不翻转，low翻转）
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //输出状态
	TIM_OCInitStructure.TIM_Pulse = 0;                   //CCR
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	//PWM频率=72M/（PSC+1）/（ARR+1）             
	//PWM占空比=CCR/（ARR+1）
	//PWM分辨率=1/（ARR+1）  
	//1M=1000000Hz
	TIM_Cmd(TIM2, ENABLE); //使能定时器
//**************************************************************************************************************
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
