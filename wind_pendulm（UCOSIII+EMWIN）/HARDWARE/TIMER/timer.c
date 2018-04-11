#include "timer.h"
#include "includes.h"
#include "totaltask.h"
#include "inv_mpu.h"

//���ŷ���

/****************************

��·PWM���

TIM3_CH1------->PC6
TIM3_CH2------->PC7
TIM3_CH3------->PC8
TIM3_CH4------->PC9


****************************/

/***********��������*****************/
TIM_HandleTypeDef TIM3_Handler;           //��ʱ�����
TIM_HandleTypeDef TIM2_Handler;
TIM_OC_InitTypeDef TIM3_OCHandler;        //��ʱ��3ͨ�����������PWM�����
TIM_ClockConfigTypeDef TIM2_Clock;
TIM_HandleTypeDef TIM5_Handler;           //��ʱ��5�������ʱ5ms�������㣩
/***********��������*****************/




/***********************************�ⲿ����****************************************/
//TIM3 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u16 arr,u16 psc)
{ 
    TIM3_Handler.Instance=TIM3;            //��ʱ��3
    TIM3_Handler.Init.Prescaler=psc;       //��ʱ����Ƶ
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//���ϼ���ģʽ
    TIM3_Handler.Init.Period=arr;          //�Զ���װ��ֵ
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM3_Handler);       //��ʼ��PWM
    
    TIM3_OCHandler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
    TIM3_OCHandler.Pulse=arr;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�
                                            //Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
    
	  TIM3_OCHandler.OCPolarity=TIM_OCPOLARITY_HIGH; //����Ƚϼ���Ϊ�ߣ���ֵԽ��ռ�ձ�Խ�� 
    
	  HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_OCHandler,TIM_CHANNEL_1);//����TIM3ͨ��1
    
	  TIM3_OCHandler.Pulse=0;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձ�
		HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_OCHandler,TIM_CHANNEL_2);//����TIM3ͨ��2
	
		TIM3_OCHandler.Pulse=0;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձ�
		HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_OCHandler,TIM_CHANNEL_3);//����TIM3ͨ��3
	
		TIM3_OCHandler.Pulse=0;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձ�
		HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_OCHandler,TIM_CHANNEL_4);//����TIM3ͨ��4
	  
	  HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_1);//����PWMͨ��4
		HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_2);//����PWMͨ��4
		HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_3);//����PWMͨ��4
		HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_4);//����PWMͨ��4
}
/***********************************�ⲿ����****************************************/

//��ʱ���ײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_TIM_PWM_Init()����
//htim:��ʱ�����
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
		__HAL_RCC_TIM3_CLK_ENABLE();			//ʹ�ܶ�ʱ��3
    __HAL_RCC_GPIOC_CLK_ENABLE();			//����GPIOBʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_6;           	//PC6
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
		GPIO_Initure.Alternate=GPIO_AF2_TIM3;	//PB1����ΪTIM3_CH4
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	
	
	  GPIO_Initure.Pin=GPIO_PIN_7;           	//PC7
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	  
	  	
	  GPIO_Initure.Pin=GPIO_PIN_8;           	//PC8
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	  
		GPIO_Initure.Pin=GPIO_PIN_9;           	//PC9
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);
}


/***********************************�ⲿ����****************************************/
//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!(��ʱ��3����APB1�ϣ�ʱ��ΪHCLK/2)
void TIM3_Init(u16 arr,u16 psc)
{  
		TIM3_Handler.Instance=TIM3;                          //ͨ�ö�ʱ��3
    TIM3_Handler.Init.Prescaler=psc;                     //��Ƶ
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM3_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM3_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM3_Handler); //ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�����жϣ�TIM_IT_UPDATE 
    
}



void TIM2_Init(u32 arr,u16 psc)
{  
	TIM2_Handler.Instance=TIM2;                          //ͨ�ö�ʱ��3
    TIM2_Handler.Init.Prescaler=psc;                     //��Ƶ
    TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM2_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM2_Handler);
	//����TIM2ʱ��Ϊ�ⲿ����ʱ��
	TIM2_Clock.ClockFilter=0x0;
	TIM2_Clock.ClockPolarity=TIM_CLOCKPOLARITY_RISING;
	TIM2_Clock.ClockPrescaler=TIM_CLOCKPRESCALER_DIV1;
	TIM2_Clock.ClockSource=TIM_CLOCKSOURCE_ETRMODE2;
	HAL_TIM_ConfigClockSource(&TIM2_Handler, &TIM2_Clock);
    
    HAL_TIM_Base_Start_IT(&TIM2_Handler); //ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�����жϣ�TIM_IT_UPDATE 
    	
}
/***********************************�ⲿ����****************************************/

//��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
//�˺����ᱻHAL_TIM_Base_Init()��������
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();            //ʹ��TIM3ʱ��
		HAL_NVIC_SetPriority(TIM3_IRQn,2,3);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM3_IRQn);          //����ITM3�ж�   
	}
    else if(htim->Instance==TIM2)
	{
		GPIO_InitTypeDef GPIO_Initure;
		__HAL_RCC_TIM2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE(); 
		GPIO_Initure.Pin=GPIO_PIN_15;            //PA15
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;      //�����������
		GPIO_Initure.Pull=GPIO_PULLDOWN;        //����
		GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
		GPIO_Initure.Alternate=GPIO_AF1_TIM2;   //PA15����ΪTIM2_ETR
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);		
	}
   else if(htim->Instance==TIM5)
   {
   		__HAL_RCC_TIM5_CLK_ENABLE();
			HAL_NVIC_SetPriority(TIM5_IRQn,3,3);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
			HAL_NVIC_EnableIRQ(TIM5_IRQn);          //����TIM5�ж�
   
   }	   
}



//ͨ�ö�ʱ��5�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��5!(��ʱ��5����APB1�ϣ�ʱ��ΪHCLK/2)
void TIM5_Init(u32 arr,u16 psc)
{  
		TIM5_Handler.Instance=TIM5;                          //ͨ�ö�ʱ��5
    TIM5_Handler.Init.Prescaler=psc;                     //��Ƶ
    TIM5_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM5_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM5_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM5_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM5_Handler); //ʹ�ܶ�ʱ��5�Ͷ�ʱ��5�����жϣ�TIM_IT_UPDATE 
    
}



//��ʱ��5�жϷ�����
void TIM5_IRQHandler(void)
{

	OSIntEnter();

	HAL_TIM_IRQHandler(&TIM5_Handler);//��ʱ�����ô�����
	
	
	OSIntExit();
}
 



//��ʱ�����벶���жϴ���ص��������ú�����HAL_TIM_IRQHandler�лᱻ����
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//�����жϷ���ʱִ��
{
	
}



//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM3_Handler);
}


void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM2_Handler);
}


/*-----------------------------------------
				��  ��  ��  ��  �� ��
------------------------------------------*/ 
//��ʱ�������жϣ�����������жϴ���ص������� �ú�����HAL_TIM_IRQHandler�лᱻ����
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	OS_ERR err;

/*------------------------------------------------
   ˵����TIM5����жϣ������ź���ͬ����ת��ANGLETASK
	       �д�������������ŷ����
	 �ж�Ƶ�ʣ�200Hz
--------------------------------------------------*/ 
	if(htim->Instance==TIM5)
	{
		
		
			OSTaskSemPost ( &ANGLETastTCB,
										  OS_OPT_POST_NONE,
										  &err);
		 
		}
}
