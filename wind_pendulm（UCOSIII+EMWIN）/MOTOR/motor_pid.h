#ifndef __MOTOR_PID_H
#define __MOTOR_PID_H

/*-----------------------------------------
				 ͷ  ��  ��  ��  ��
------------------------------------------*/ 
#include "sys.h"
#include "delay.h"


/*-----------------------------------------
				 ��   ��   ��
-----------------------------------------*/ 
#define IntergralMax   3500    //��������
#define IntergralMin  -3500     //��������

/*-----------------------------------------
				 ��  ��  ��  ��   
------------------------------------------*/ 
typedef struct
{
	
	float  SetPoint;              //�趨ֵ
	double SumError;              //�ۼ����
   
  float   Kp;                   //����ϵ��Kp
  float   Ki;                   //����ϵ��Ki
  float   Kd;	                  //΢��ϵ��Kd
	
	
	float  LastError;             //E[-1]
	float  PreError;              //E[-2]
	
}PIDTypeDef;


typedef struct
{
   
   float kp_temp;
	 float ki_temp;
	 float kd_temp;
 

}PitchSetPIDByUpTypeDef,RollSetPIDByUpTypeDef;


extern PitchSetPIDByUpTypeDef PitchSetPIDtemp;
extern RollSetPIDByUpTypeDef 	 RollSetPIDtemp;

/*-----------------------------------------
				 ��  ��  ��  ��
------------------------------------------*/ 

int32_t   PID_M1_PosLocCalc(float NextPoint);         


void 	PID_M1_Init(void);
void  PID_M1_SetPoint(float setpoint);
void 	PID_M1_SetKp(float kp);
void  PID_M1_SetKi(float ki);
void 	PID_M1_SetKd(float kd);


int32_t   PID_M2_PosLocCalc(float NextPoint);         

void 	PID_M2_Init(void);
void  PID_M2_SetPoint(float setpoint);
void 	PID_M2_SetKp(float kp);
void  PID_M2_SetKi(float ki);
void 	PID_M2_SetKd(float kd);

void PitchSetPID_Init(void);
void RollSetPID_Init(void);

#endif


