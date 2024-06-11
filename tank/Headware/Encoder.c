#include "encoder.h"
#include "stm32f10x.h"

/**************************************************************************
�������ܣ���TIM3��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Encoder_Init_TIM3(void)
{
  	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  	TIM_ICInitTypeDef TIM_ICInitStructure;  
  	GPIO_InitTypeDef GPIO_InitStructure;
	
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ�ܶ�ʱ��3��ʱ��
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��PA�˿�ʱ��
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//�˿����� PA6 PA7
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  	GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA
  	
  	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
		TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //�趨�������Զ���װֵ
  	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ؼ���ģʽ 
  	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);  //��ʼ����ʱ��3
	
  	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3(TIM_ICPolarity_Rising����TIM_ICPolarity_FallingЧ����ͬ������4��Ƶ)
	
  	TIM_ICStructInit(&TIM_ICInitStructure); //��TIM_ICInitStruct �е�ÿһ��������ȱʡֵ����
  	TIM_ICInitStructure.TIM_ICFilter = 10;  //�����˲�������
  	TIM_ICInit(TIM4, &TIM_ICInitStructure);//���� TIM_ICInitStruct �Ĳ�����ʼ������	TIMx
 
  	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);//ʹ�ܶ�ʱ���ж�
  	TIM_SetCounter(TIM4,0);
  	TIM_Cmd(TIM4, ENABLE); //ʹ�ܶ�ʱ��
}

/**************************************************************************
�������ܣ���TIM4��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Encoder_Init_TIM4(void)
{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  	TIM_ICInitTypeDef TIM_ICInitStructure;  
  	GPIO_InitTypeDef GPIO_InitStructure;
	
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//ʹ�ܶ�ʱ��3��ʱ��
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PA�˿�ʱ��
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//�˿����� PA6 PA7
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  	GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA
  	
  	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
		TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //�趨�������Զ���װֵ
  	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ؼ���ģʽ 
  	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  //��ʼ����ʱ��3
	
  	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3(TIM_ICPolarity_Rising����TIM_ICPolarity_FallingЧ����ͬ������4��Ƶ)
	
  	TIM_ICStructInit(&TIM_ICInitStructure); //��TIM_ICInitStruct �е�ÿһ��������ȱʡֵ����
  	TIM_ICInitStructure.TIM_ICFilter = 10;  //�����˲�������
  	TIM_ICInit(TIM3, &TIM_ICInitStructure);//���� TIM_ICInitStruct �Ĳ�����ʼ������	TIMx
 
  	TIM_ClearFlag(TIM3, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//ʹ�ܶ�ʱ���ж�
  	TIM_SetCounter(TIM3,0);
  	TIM_Cmd(TIM3, ENABLE); //ʹ�ܶ�ʱ��
}

/**************************************************************************
�������ܣ���λʱ���ȡ������A����
��ڲ�������
����  ֵ������ֵ
**************************************************************************/
float Read_EncoderA(void)
{
	int Encoder_TIM = 0;  
	Encoder_TIM= (short)TIM3 -> CNT;   
	TIM3 -> CNT=0;
	return -Encoder_TIM;
}
/**************************************************************************
�������ܣ���λʱ���ȡ������B����
��ڲ�������
����  ֵ������ֵ
**************************************************************************/
float Read_EncoderB(void)
{
	int Encoder_TIM = 0;  
	Encoder_TIM= (short)TIM4 -> CNT;   
	TIM4 -> CNT=0;
	return Encoder_TIM;
}

/**************************************************************************
*  �������ܣ�TIM2�жϷ�����
*
*  ��ڲ�������
*
*  �� �� ֵ����
**************************************************************************/
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0);//����жϱ�־λ 	    
}


/**************************************************************************
*  �������ܣ�TIM3�жϷ�����
*
*  ��ڲ�������
*
*  �� �� ֵ����
**************************************************************************/
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}
