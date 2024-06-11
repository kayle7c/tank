#ifndef ENCODER_H
#define ENCODER_H

#define ENCODER_TIM_PERIOD (u16)(65535)   //不可大于65535 因为F103的定时器是16位的。

void Encoder_Init_TIM3(void);
void Encoder_Init_TIM4(void);
	
float Read_EncoderA(void);
float Read_EncoderB(void);


#endif
