#ifndef __Control_H
#define __Control_H

#define v_max 1.1
#define w_max 4.78
#define L     0.23

void Set_Right_ccr(int ccr);
void Set_Left_ccr(int ccr);
void Set_Left_Polarity(short polarity);
void Set_Right_Polarity(short polarity);
void control_run(float x,float y);
void run(char command);
void Data_Parse(char* Data);
void Inverse_Kinematics_Analytic(float Vx,float Vz);

#endif