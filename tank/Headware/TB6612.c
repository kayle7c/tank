#include "stm32f10x.h"                  // Device header

void tb6612_Init(void)
{

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
	GPIO_InitTypeDef GPIO_InitStructure;//�������pwm��GPIO
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//���������������Ϊ��ʱ����Ƭ�����裨TIM2��ch1ͨ��������������ݼĴ���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	
	
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2); //ѡ��ʱ�ӣ��ڲ���
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//����ʱ����Ԫ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; //Ԥ��Ƶϵ����1��2��4��
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInitStruct.TIM_Period = 1000-1;      //ARR���Զ���װ��ֵ��0~65535
	TIM_TimeBaseInitStruct.TIM_Prescaler = 1440-1;    //PSC��Ԥ��Ƶֵ��    0~65535
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	//��������Ƚ�ͨ��
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure); //��ʼ���ṹ�����
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;      //����Ƚ�ģʽ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //ѡ���ԣ�high����ת��low��ת��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //���״̬
	TIM_OCInitStructure.TIM_Pulse = 0;                   //CCR
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	
	TIM_OCStructInit(&TIM_OCInitStructure); //��ʼ���ṹ�����
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;      //����Ƚ�ģʽ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //ѡ���ԣ�high����ת��low��ת��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //���״̬
	TIM_OCInitStructure.TIM_Pulse = 0;                   //CCR
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	//PWMƵ��=72M/��PSC+1��/��ARR+1��             
	//PWMռ�ձ�=CCR/��ARR+1��
	//PWM�ֱ���=1/��ARR+1��  
	//1M=1000000Hz
	TIM_Cmd(TIM2, ENABLE); //ʹ�ܶ�ʱ��
//**************************************************************************************************************
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
