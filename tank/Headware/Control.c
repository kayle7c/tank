#include "stm32f10x.h"                  // Device header
#include "Control.h"

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

void Data_Parse(char* Data)
{
		//printf("%d,%d\r\n",Data[1],Data[2]);
		float X_Speed=(Data[1]-100)/100.0;
		float Y_Speed=(Data[2]-100)/100.0;
		char Fire=Data[3];
		control_run(X_Speed,Y_Speed);
	//	printf("%f,%f,%c\r\n",X_Speed,Y_Speed,Fire);	
		//nverse_Kinematics_Analytic(X_Speed,Y_Speed);
	
}

void control_run(float x,float y)
{
	float x_speed=(x+y);
	float y_speed=(x-y)*-1;
	//printf("%f,%f\r\n",x_speed,y_speed);
	if(x_speed>=0)
	{
		Set_Left_Polarity(0);
		Set_Left_ccr(x_speed*1000);
	}
	else if(x_speed<0)
	{
		Set_Left_Polarity(1);
		Set_Left_ccr(x_speed*-1000);
	}
	if(y_speed>=0)
	{
		Set_Right_Polarity(0);
		Set_Right_ccr(y_speed*1000);
	}
	else if(y_speed<0)
	{
		Set_Right_Polarity(1);
		Set_Right_ccr(y_speed*-1000);
	}
}

void Inverse_Kinematics_Analytic(float Vx,float Vz)
{
			float Target_Left=Vx-Vz*L/2.0f;
			float Target_Right=Vx+Vz*L/2.0f;
		
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