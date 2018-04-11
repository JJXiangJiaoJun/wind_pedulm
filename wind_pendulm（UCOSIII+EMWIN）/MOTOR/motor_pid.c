#include "motor_pid.h"


/*-----------------------------------------
				 ��  ��  ��  ��   
------------------------------------------*/ 

PIDTypeDef  PID_M1;      
PIDTypeDef  PID_M2;
PitchSetPIDByUpTypeDef PitchSetPIDtemp;
RollSetPIDByUpTypeDef RollSetPIDtemp;


/*------------------------------------------
 ��������:�����ʼ��
 ����˵��:		
------------------------------------------*/
void 	PID_M1_Init(void)
{
   PID_M1.SetPoint=0.0f;
	 PID_M1.SumError=0.0f;
	
	 PID_M1.Kp=0.0f;
	 PID_M1.Ki=0.0f;
	 PID_M1.Kd=0.0f;
    	
   PID_M1.LastError=0.0f;
	 PID_M1.PreError=0.0f;
}



void 	PID_M2_Init(void)
{
   PID_M2.SetPoint=0.0f;
	 PID_M2.SumError=0.0f;
	
	 PID_M2.Kp=0.0f;
	 PID_M2.Ki=0.0f;
	 PID_M2.Kd=0.0f;
    	
   PID_M2.LastError=0.0f;
	 PID_M2.PreError=0.0f;

}


void PitchSetPID_Init(void)
{
   PitchSetPIDtemp.kp_temp=1800.0f;
	 
	 PitchSetPIDtemp.ki_temp=1.5f;
	 
	 PitchSetPIDtemp.kd_temp=47000.0f;
	
}



void RollSetPID_Init(void)
{
   RollSetPIDtemp.kp_temp=1.0f;
	 RollSetPIDtemp.ki_temp=0.3f;
	 RollSetPIDtemp.kd_temp=2000.0f;
   
}
/*------------------------------------------
 ��������:���1�����趨
 ����˵��:		
------------------------------------------*/

void  PID_M1_SetPoint(float setpoint)
{

   PID_M1.SetPoint=setpoint;

}



void 	PID_M1_SetKp(float kp)
{

    PID_M1.Kp=kp;
  
}


void  PID_M1_SetKi(float ki)
{

		PID_M1.Ki=ki;
	
}


void 	PID_M1_SetKd(float kd)
{
	
		PID_M1.Kd=kd;
	
}

/*------------------------------------------
 ��������:���2�����趨
 ����˵��:		
------------------------------------------*/

void  PID_M2_SetPoint(float setpoint)
{

   PID_M2.SetPoint=setpoint;

}



void 	PID_M2_SetKp(float kp)
{

    PID_M2.Kp=kp;
  
}


void  PID_M2_SetKi(float ki)
{

		PID_M2.Ki=ki;
	
}


void 	PID_M2_SetKd(float kd)
{
	
		PID_M2.Kd=kd;
	
}

/*------------------------------------------
 ��������:���1λ��ʽPID����
 ����˵��:		
------------------------------------------*/

int32_t   PID_M1_PosLocCalc(float NextPoint)
{
    float Derivative;                                   //΢����
        
		PID_M1.LastError = PID_M1.SetPoint - NextPoint;     //��ǰ���
	  PID_M1.SumError = PID_M1.SumError+PID_M1.LastError; //������
	  
	  if(PID_M1.SumError>IntergralMax)
			PID_M1.SumError = IntergralMax;
		else if(PID_M1.SumError<IntergralMin)
			PID_M1.SumError = IntergralMin;
		Derivative = PID_M1.LastError - PID_M1.PreError;
		PID_M1.PreError = PID_M1.LastError;
		
		
		return (int32_t)(PID_M1.Kp*PID_M1.LastError+
			           PID_M1.Ki*PID_M1.SumError +
		             PID_M1.Kd*Derivative);	 
}



/*------------------------------------------
 ��������:���2λ��ʽPID����
 ����˵��:		
------------------------------------------*/
int32_t   PID_M2_PosLocCalc(float NextPoint)
{
    float Derivative;                                   //΢����
        
		PID_M2.LastError = PID_M2.SetPoint - NextPoint;     //��ǰ���
	  PID_M2.SumError = PID_M2.SumError+PID_M2.LastError; //������
	  
	  if(PID_M2.SumError>IntergralMax)
			PID_M2.SumError = IntergralMax;
		else if(PID_M2.SumError<IntergralMin)
			PID_M2.SumError = IntergralMin;
		Derivative = PID_M2.LastError - PID_M2.PreError;
		PID_M2.PreError = PID_M2.LastError;
		
		
		return (int32_t)(PID_M2.Kp*PID_M2.LastError+
			           PID_M2.Ki*PID_M2.SumError +
		             PID_M2.Kd*Derivative);	 
}
