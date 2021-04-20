#include "main.h"

extern float angle_result;
extern float ICM_GYR_Y;

float Angle_Set=31;
float KP_Balance=110;
float KD_Balance=5;
int16_t Balance_PWM=0;
float Angle_Bias=0;

void Balance_PD(void)
{
	Angle_Bias=angle_result-Angle_Set;
	Balance_PWM=KD_Balance*ICM_GYR_Y;		//KP_Balance*Angle_Bias+
}

//typedef struct
//{
//	float Angle_Set;
//	float KP_Balance;
//	float KD_Balance;
//}PID_Parameter;

//PID_Parameter PID_parm1;


////PID_parm1.Angle_Set=80;
////PID_parm1.KP_Balance=80;
////PID_parm1.KD_Balance=5;

////struct 
////{
////	float Angle_Set;
////	float KP_Balance;
////	float KD_Balance;
////}PID_Parameter;

//PID_parm1.Angle_Set=80;
//PID_parm1.KP_Balance=90;
//PID_parm1.KD_Balance=4;



