#ifndef ENCODER_H
#define ENCODER_H

#define ENCODER_TIM_PERIOD (u16)(65535)   //���ɴ���65535 ��ΪF103�Ķ�ʱ����16λ�ġ�

void Encoder_Init_TIM3(void);
void Encoder_Init_TIM4(void);
	
float Read_EncoderA(void);
float Read_EncoderB(void);


#endif
