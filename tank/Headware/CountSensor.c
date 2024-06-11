#include "stm32f10x.h"                  // Device header

void CountSensor_Init(void) //�ж�����
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //��goiobʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //��AFIOʱ��
	
	GPIO_InitTypeDef GPIO_InitStructure;  //����GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9); //����AFIO
	
	EXTI_InitTypeDef EXTI_InitStructure; //�����ⲿ�ж�
	EXTI_InitStructure.EXTI_Line = EXTI_Line9; //�ⲿ�ж��ߣ�pin�ں��ⲿ�ж���һһ��Ӧ��
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; //ʹ�ܻ�ʧ��
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //�ж�ģʽ�����¼�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //������ʽ������ �½� ����
	
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//NVIC�������ã�һ��оƬֻ����һ�ַ��飬�������ģ�����þͲ��ֱܷ������
  NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //ָ��ͨ���������ж��ߣ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ�ܻ�ʧ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //��Ӧ���ȼ�
	
	NVIC_Init(&NVIC_InitStructure);
	
//�ⲿ�ж�����˳��GPIO->AFIO->EXTI->NVIC
}

void EXTI9_5_IRQHandler(void) //�жϺ���
{
	if (EXTI_GetITStatus(EXTI_Line9) == SET) //�ж�EXTI14���жϱ�־λ�����أ�set����reset��  
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		EXTI_ClearITPendingBit(EXTI_Line9); //����жϱ�־λ		
	}
}