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
                                       //����IO���Ա�SD��ռ��
 IIC_SCL  --------------->  PH4
 IIC_SDA  --------------->  PH5 
 
 
 
 
 
 ע�⣡��������������ʵʱ����ϵͳ�У�ʹ��EMWIN���벻Ҫ���ⲿ����ͼ��ķ������ٶȻطǳ��ǳ�������������ϵͳ̱��
 
 
  
-------------------------------------------------------------------------------------------*/   


#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "tftlcd.h"
#include "sdram.h"
#include "malloc.h"
#include "timer.h"
#include "touch.h"
#include "mpu.h"
#include "includes.h"

#include "sdmmc_sdcard.h"
#include "ff.h"
#include "ftl.h" 
#include "exfuns.h"


/*-----------------------------------------
				 �� �� ͷ �� �� �� ��
------------------------------------------*/ 
#include "mpu6050.h"
#include "inv_mpu.h"
#include "GUI.h"
#include "WM.h"
#include "fontupd.h"


//������ͷ�ļ�����

//************************************************
#include "totaltask.h"
//************************************************


/*-----------------------------------------
				 ��  ʼ  ��  ��
------------------------------------------*/ 


//�������ȼ�
#define START_TASK_PRIO 5
//�����ջ��С
#define START_STK_SIZE 256
//������ƿ�
OS_TCB  StartTaskTCB;
//�����ջ
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);



/*-----------------------------------------
				��     ��    ��
------------------------------------------*/  

//ע�⣡������MPU6050�Ķ�ȡ����Ҫ�Ͳ������ʱ���һ�£���Ȼ���׳�������


int main(void)
{
      OS_ERR err;
	    u8 res;
	    CPU_SR_ALLOC();
	
      Write_Through();
      MPU_Memory_Protection();        //������ش洢����	
			Cache_Enable();                 //��L1-Cache
			HAL_Init();				      			  //��ʼ��HAL��
			Stm32_Clock_Init(432,25,2,9);   //����ʱ��,216Mhz 
			delay_init(216);                //��ʱ��ʼ��
			
	   /*---------------�����ʼ��----------------------*/
	    uart_init(500000);		       	//���ڳ�ʼ��
			LED_Init();                   //��ʼ��LED
			KEY_Init();                   //��ʼ������
			SDRAM_Init();                 //��ʼ��SDRAM
			TFTLCD_Init();                   //��ʼ��LCD
			TP_Init();
			my_mem_init(SRAMIN);		   	 	//��ʼ���ڲ��ڴ��
			my_mem_init(SRAMEX);		    	//��ʼ���ⲿ�ڴ��
			my_mem_init(SRAMDTCM);		    //��ʼ��DTCM�ڴ��
	    LCD_ShowString(40,50,100,100,16,"System_Init...");
			
		  exfuns_init();			        //Ϊfatfs��ر��������ڴ�				 
  	  f_mount(fs[0],"0:",1); 		    //����SD�� 
      f_mount(fs[1],"1:",1); 	        //����FLASH.	
      f_mount(fs[2],"2:",1); 		    //����NAND FLASH.

		while(SD_Init())	//���SD��
		{
			LCD_ShowString(30,90,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(30,90,200+30,70+16,WHITE);
			delay_ms(200);		    
		}
		font_init();
			/*-----------------------------------------
				��        ʼ       ��      MPU6050
			------------------------------------------*/  
			
//			while(MPU_Init())
//			{
//				 delay_ms(10);
//				 LCD_ShowString(40,150,100,100,16,"MPU_ERROR");
//			
//			}
			delay_ms(10);
			LCD_ShowString(40,50,100,100,16,"MPU_SUCCESS...");
			
			LCD_ShowString(40,200,100,100,16,"MPU_DMP_Init...");

//			while(mpu_dmp_init())
//			{
//					
//			   delay_ms(200);
//				 res=mpu_dmp_init();
//				 LCD_ShowString(20,250,100,100,16,"MPU_DMP_ERROR");
//			   LCD_ShowNum(20,150,res,16,16);
//				 delay_ms(200);
//			}
			LCD_ShowString(20,200,100,100,16,"MPU_DMP_SUCCESS");
			delay_ms(200);
			LCD_Clear(WHITE);
				
			//TIM3_PWM_Init(5400-1,1-1);    //TIM3ʵ��4·PWM���
			TIM5_Init(5000-1,108-1);      //5ms�ж�һ�Σ�����ͬ������
			
			
			/*----------------UCOSIII��ʼ��------------------*/ 
			/*----------------������ʼ����------------------*/ 
      OSInit(&err);
	    OS_CRITICAL_ENTER();
	    
			OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
				 (CPU_CHAR	* )"start task", 		//��������
                 (OS_TASK_PTR )start_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP, //����ѡ��,Ϊ�˱���������������񶼱��渡��Ĵ�����ֵ
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
				
		OS_CRITICAL_EXIT();
    OSStart(&err); 								 
		/*----------------UCOSIII��ʼ��------------------*/ 
		while(1)
		{		       
		}
}

void start_task(void *p_arg)
{
		OS_ERR err;
		CPU_SR_ALLOC();
		p_arg=p_arg;
	 
	  CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	  //ʹ��ʱ��Ƭ��ת���ȹ���,����Ĭ�ϵ�ʱ��Ƭ����
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif	
	OS_CRITICAL_ENTER();
	/*-----------------------------------------
			��  ��  ��  ��  ʼ  ��
	------------------------------------------*/ 
 	__HAL_RCC_CRC_CLK_ENABLE();		//ʹ��CRCʱ��
	GUI_Init();  			//STemWin��ʼ��
	WM_MULTIBUF_Enable(1);  //����STemWin�໺��,RGB�����ܻ��õ�
	
	led_task_init(&err);
	//lcd_task_init(&err);
	enwin_task_init(&err);
	touch_task_init(&err);
	angle_task_init(&err);
  //fontupdata_task_init(&err);
	OS_CRITICAL_EXIT();
  OSTaskDel((OS_TCB*)0,&err);								 

}



