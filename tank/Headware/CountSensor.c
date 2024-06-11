#include "stm32f10x.h"                  // Device header

void CountSensor_Init(void) //中断配置
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //打开goiob时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //打开AFIO时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;  //配置GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9); //配置AFIO
	
	EXTI_InitTypeDef EXTI_InitStructure; //配置外部中断
	EXTI_InitStructure.EXTI_Line = EXTI_Line9; //外部中断线（pin口和外部中断线一一对应）
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; //使能或失能
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //中断模式或者事件模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //触发方式（上升 下降 都）
	
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//NVIC分组配置，一个芯片只能有一种分组，如果其他模块再用就不能分别的组了
  NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //指定通道（根据中断线）
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能或失能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //响应优先级
	
	NVIC_Init(&NVIC_InitStructure);
	
//外部中断配置顺序：GPIO->AFIO->EXTI->NVIC
}

void EXTI9_5_IRQHandler(void) //中断函数
{
	if (EXTI_GetITStatus(EXTI_Line9) == SET) //判断EXTI14的中断标志位，返回（set或者reset）  
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		EXTI_ClearITPendingBit(EXTI_Line9); //清除中断标志位		
	}
}