#include "stm32f10x.h"                  // Device header

void Set_Left_ccr(int ccr)
{
	TIM_SetCompare1(TIM2, ccr);
}

void Set_Right_ccr(int ccr)
{
	TIM_SetCompare2(TIM2, ccr);
}

void Set_Left_Polarity(short polarity)
{
	if(polarity==0)//前进
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);//AIN1->0
		GPIO_SetBits(GPIOC,GPIO_Pin_1);//AIN2->1
	}
	if(polarity==1)//后退
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_0);//AIN1->1
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);//AIN2->0
	}
}

void Set_Right_Polarity(short polarity)
{
	if(polarity==0)//前进
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_2);//BIN1->0
		GPIO_SetBits(GPIOC,GPIO_Pin_3);//BIN2->1
	}
	if(polarity==1)//后退
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_2);//BIN1->1
		GPIO_ResetBits(GPIOC,GPIO_Pin_3);//BIN2->0
	}
}

void run(char command)
{
	if(command=='0')
	{
		Set_Left_Polarity(0);
		Set_Right_Polarity(0);
		Set_Left_ccr(350);
		Set_Right_ccr(400);
	}
	if(command=='1')
	{
		Set_Left_Polarity(1);
		Set_Right_Polarity(1);
		Set_Left_ccr(350);
		Set_Right_ccr(400);
	}
	if(command=='2')
	{
		Set_Left_Polarity(1);
		Set_Right_Polarity(0);
		Set_Left_ccr(350);
		Set_Right_ccr(400);
	}
	if(command=='3')
	{
		Set_Left_Polarity(0);
		Set_Right_Polarity(1);
		Set_Left_ccr(350);
		Set_Right_ccr(400);
	}
	if(command=='4')
	{
		Set_Left_Polarity(0);
		Set_Right_Polarity(1);
		Set_Left_ccr(0);
		Set_Right_ccr(0);
	}
	
}