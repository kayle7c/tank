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
//usart2 							广和通   					PA2->TX  						PA3->RX
//usart3 							语音     					PC10->TX 						PC11->RX
//TIM2_CH1/CH2  			TB6612 PWM				PA0->CH1(Left)			PA1->CH2(Right)
//GPIO								TB6612极性  			PC0/1(Left)					PC2/3(Right)
//TIM3_CH1/CH2				编码盘测速(Left)  PA6->CH1 						PA7->CH2
//TIM4_CH1/CH2				编码盘测速(Right) PB6->CH1 						PB7->CH2
//软件IIC							MPU6050						PA4->SCL						PA5->SDA
//GPIO								灯								PB5
//usart4 				树莓派                                                               


//平衡时，左轮比右轮少50
//*******************************************************************************
float a = 0, b;
int x,y;
char command;
extern u8  USART2_RX_BUF[200];
extern u16 USART2_RX_STA;
char STA_Flag=0;

int hexCharToInt(char c) {
		//printf("%c\r\n",c);
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1;
}

void parseAndDecode(const char* input, char* output) {
    // 找到最后一个逗号，获取十六进制字符串
    const char* hexStr = strrchr(input, ',') + 1;

    // 遍历十六进制字符串，将每两个字符转换为一个字节
    while (*hexStr && *(hexStr + 1)) {
        char high = hexCharToInt(*hexStr++);
        char low = hexCharToInt(*hexStr++);
        *output++ = (high << 4) | low;
    }
    // 终止输出字符串
    *output = '\0';
}

int main(void)
{	
	delay_init();
	uart_init(9600);
	uart2_init(9600);
	tb6612_Init();
	tb6612hl_Init();
	Encoder_Init_TIM3();
	Encoder_Init_TIM4();
	MPU_Init();
	clrStruct();
	while(1)
	{
		if(((USART2_RX_STA&0x8000)>>15)==1)
		{
			if(STA_Flag==0) STA_Flag=1;
			else if(STA_Flag==1) STA_Flag=0;
			if(STA_Flag==0)
			{
				//printf("%s",USART2_RX_BUF);
				printf("%d\r\n",USART2_RX_BUF[15]);
				command=USART2_RX_BUF[15];
				run(command);
			}
			memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
//			printf("%s\r\n",decodedMessage);
//			run(command);
			USART2_RX_STA=0;
			
		}
		a = (Read_EncoderA()/1560)*(3.1415*4.4)/100;
		b = (Read_EncoderB()/1560)*(3.1415*4.4)/100;
		
		parseGpsBuffer();
		printGpsBuffer();
		
		//printf("%f,%f\n",a,b); 
	}

	
	return 0;
}
