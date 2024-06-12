#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "usart2.h"
#include "GPS.h"
#include "TB6612.h"
#include "Encoder.h"
#include "mpu6050.h"  
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "Control.h"
#include "stdlib.h"
#include "string.h"


//******************************************************************************
//usart1 							gps      					PA9->TX  						PA10->RX
//usart2 							���ͨ   					PA2->TX  						PA3->RX
//usart3 							����     					PC10->TX 						PC11->RX
//TIM2_CH1/CH2  			TB6612 PWM				PA0->CH1(Left)			PA1->CH2(Right)
//GPIO								TB6612����  			PC0/1(Left)					PC2/3(Right)
//TIM3_CH1/CH2				�����̲���(Left)  PA6->CH1 						PA7->CH2
//TIM4_CH1/CH2				�����̲���(Right) PB6->CH1 						PB7->CH2
//���IIC							MPU6050						PA4->SCL						PA5->SDA
//GPIO								��								PB5
//usart4 				 ��ݮ��                                                               


//ƽ��ʱ�����ֱ�������50
//*******************************************************************************
float a = 0, b=0;                       //���ֺ����ֵ�ת��
char command;                           //�յ���ָ��
extern u8  USART2_RX_BUF[200];          //���ڻ�����
extern u16 USART2_RX_STA;               //���ڱ�־λ
char STA_Flag=0;                        //���ڽ��յ��������ݵĴ���


void Receive_Data()
{
	if(((USART2_RX_STA&0x8000)>>15)==1)
	{
		if(STA_Flag==0) STA_Flag=1;
		else if(STA_Flag==1) STA_Flag=0;
		if(STA_Flag==0)
		{
			printf("%d\r\n",USART2_RX_BUF[15]);
			command=USART2_RX_BUF[15];
			run(command);
		}
		memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
		USART2_RX_STA=0;
	}
}

void Get_Speed()
{
	a = (Read_EncoderA()/1560)*(3.1415*4.4)/100;
	b = (Read_EncoderB()/1560)*(3.1415*4.4)/100;
}

void Gps_Handle()
{
	parseGpsBuffer();
	printGpsBuffer();
}

int main(void)
{	
	delay_init();
	uart_init(9600);
	uart2_init(9600);
	tb6612_Init();
	Encoder_Init_TIM3();
	Encoder_Init_TIM4();
	MPU_Init();
	clrStruct();
	while(1)
	{
		Receive_Data();
		Get_Speed();
		Gps_Handle();
	}	

}
