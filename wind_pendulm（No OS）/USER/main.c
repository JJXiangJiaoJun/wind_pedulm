/*-------------------------------------------------------------------------------------------
        		   			�����ڿ���ϵͳ(2017-8-19)

 Ӳ��ƽ̨:
 			������: STM32F767 
			������: L298N
		    ��Դ: DC +12V

 ���ƽ̨:
 			��������: RealView MDK-ARM uVision5.20
			C������ : ARMCC
			ASM������:ARMASM
			������:   STLINK
			�ײ�����: ����������������       
 
 ʱ��: 2017��8��19��       
 
 ����: �㽶��
-------------------------------------------------------------------------------------------*/   

/*-------------------------------------------------------------------------------------------
 �������ã�
 
 ���1PWM --------------->  PC6
 ���2PWM --------------->  PC7
 ���3PWM --------------->  PC8
 ���4PWM --------------->  PC9
 
 IIC_SCL  --------------->  PH4
 IIC_SDA  --------------->  PH5 
 
 
  
-------------------------------------------------------------------------------------------*/   


#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "sdram.h"
#include "malloc.h"
#include "timer.h"
#include "motor_pid.h"
#include "motor_control.h" 

/*-----------------------------------------
				 �� �� ͷ �� �� �� ��
------------------------------------------*/ 
#include "mpu6050.h"
#include "inv_mpu.h"
#include "niming.h"


//������ͷ�ļ�����

//************************************************
//************************************************


/*-----------------------------------------
				 ��  ʼ  ��  ��
------------------------------------------*/ 



/*-----------------------------------------
				��     ��    ��
------------------------------------------*/  

//ע�⣡������MPU6050�Ķ�ȡ����Ҫ�Ͳ������ʱ���һ�£���Ȼ���׳�������


int main(void)
{
	    u8 res;
	    u8 buf[30];
	
      Write_Through(); 
			Cache_Enable();                 //��L1-Cache
			HAL_Init();				      			  //��ʼ��HAL��
			Stm32_Clock_Init(432,25,2,9);   //����ʱ��,216Mhz 
			delay_init(216);                //��ʱ��ʼ��
			
	   /*---------------�����ʼ��----------------------*/
	    uart_init(500000);		       	//���ڳ�ʼ��
			LED_Init();                   //��ʼ��LED
			KEY_Init();                   //��ʼ������
			SDRAM_Init();                 //��ʼ��SDRAM
			LCD_Init();                   //��ʼ��LCDq
			my_mem_init(SRAMIN);		   	 	//��ʼ���ڲ��ڴ��
			my_mem_init(SRAMEX);		    	//��ʼ���ⲿ�ڴ��
			my_mem_init(SRAMDTCM);		    //��ʼ��DTCM�ڴ��
	    LCD_ShowString(40,50,100,100,16,"MPU_Init...");
	    
			while(MPU_Init())
			{
				 delay_ms(10);
				 LCD_ShowString(40,150,100,100,16,"MPU_ERROR");
			
			}
			delay_ms(10);
			LCD_ShowString(40,50,100,100,16,"MPU_SUCCESS...");
			
			LCD_ShowString(40,200,100,100,16,"MPU_DMP_Init...");

			while(mpu_dmp_init())
			{
					
			   delay_ms(200);
				 res=mpu_dmp_init();
				 LCD_ShowString(20,250,100,100,16,"MPU_DMP_ERROR");
			   LCD_ShowNum(20,150,res,16,16);
				 delay_ms(200);
			}
			LCD_ShowString(20,200,100,100,16,"MPU_DMP_SUCCESS");
			
			delay_ms(200);
			LCD_Clear(WHITE);
			
			POINT_COLOR=BLUE;//��������Ϊ��ɫ 
			LCD_ShowString(10,30,300,300,24,"HUN Wind pendulum");
			POINT_COLOR=RED;//��������Ϊ��ɫ 
			LCD_ShowString(90,80,300,300,16,"-----By xiang jiao jun");

      POINT_COLOR=YELLOW;//��������Ϊ��ɫ
      
			LCD_ShowString(30,170,200,24,24,"System Runing......");	 
			
			POINT_COLOR=MAGENTA;//��������Ϊ��ɫ
			
			LCD_ShowString(30,260,200,24,24,"Mode  : 1 ");	
			
			LCD_ShowString(30,290,200,24,24,"Radius: 25.0cm");	
			
			LCD_ShowString(30,320,200,24,24,"Angle : 90");	 
			
			LCD_ShowString(30,350,200,24,24,"RoundDir : 0");
			
			PitchSetPID_Init();
			RollSetPID_Init();
				
			TIM3_PWM_Init(5400-1,1-1);    //TIM3ʵ��4·PWM���
			TIM5_Init(5000-1,108-1);      //5ms�ж�һ�Σ�����ͬ������
			

							 
		while(1)
		{   
      //��λ���޸�PID����
			if(USART_RX_STA == 1)
			{
			   USART_RX_STA = 0;
				
				 LED0_Toggle;
				
				//��λ�����͵�PID���뻺����
				RollSetPIDtemp.kp_temp = (USART_RX_BUF[4]<<8)|USART_RX_BUF[5];
				//RollSetPIDtemp.ki_temp = (USART_RX_BUF[6]<<8)|USART_RX_BUF[7];
				RollSetPIDtemp.kd_temp = (USART_RX_BUF[8]<<8)|USART_RX_BUF[9];
				
				PitchSetPIDtemp.kp_temp = (USART_RX_BUF[10]<<8)|USART_RX_BUF[11];
				PitchSetPIDtemp.ki_temp = (USART_RX_BUF[12]<<8)|USART_RX_BUF[13];
				PitchSetPIDtemp.kd_temp = (USART_RX_BUF[14]<<8)|USART_RX_BUF[15];
				 
			  Mode       =   (u8) RollSetPIDtemp.kd_temp;                     //�ı�ģʽ
				Radius     =   (float)PitchSetPIDtemp.kp_temp;                  //�ı�뾶
				Angle      =   (float)PitchSetPIDtemp.ki_temp/57.2958f;         //�ı�Ƕ�
				RoundDir   =  (u8)PitchSetPIDtemp.kd_temp;                      //�ı���ת����
				
				
				sprintf((char *)buf,"Mode  : %d ",Mode);
				
				LCD_ShowString(30,260,200,24,24,buf);
				
				sprintf((char *)buf,"Radius: %.1fcm  ",Radius);
				
				LCD_ShowString(30,290,200,24,24,buf);
				
				sprintf((char *)buf,"Angle : %.0f    ",PitchSetPIDtemp.ki_temp);
				
				LCD_ShowString(30,320,200,24,24,buf);
				
				sprintf((char *)buf,"RoundDir : %d  ",RoundDir);
				
				LCD_ShowString(30,350,200,24,24,buf);
		
			}
          
			
		}
}