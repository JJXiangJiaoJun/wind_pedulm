#ifndef _MYIIC_H
#define _MYIIC_H
#include "sys.h"



////IO��������
//#define SDA_IN()  {GPIOH->MODER&=~(3<<(5*2));GPIOH->MODER|=0<<5*2;}	//PH5����ģʽ
//#define SDA_OUT() {GPIOH->MODER&=~(3<<(5*2));GPIOH->MODER|=1<<5*2;} //PH5���ģʽ
////IO����
//#define IIC_SCL(n)  (n?HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_RESET)) //SCL
//#define IIC_SDA(n)  (n?HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_RESET)) //SDA
//#define READ_SDA    HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_5)  //����SDA




////IO��������
//#define SDA_IN()  {GPIOC->MODER&=~(3<<(5*2));GPIOC->MODER|=0<<5*2;}	//PC5����ģʽ
//#define SDA_OUT() {GPIOC->MODER&=~(3<<(5*2));GPIOC->MODER|=1<<5*2;} //PC5���ģʽ
////IO����
//#define IIC_SCL(n)  (n?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_RESET)) //SCL
//#define IIC_SDA(n)  (n?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_RESET)) //SDA
//#define READ_SDA    HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5)  //����SDA




//IO��������
#define SDA_IN()  {GPIOB->MODER&=~(3<<(11*2));GPIOB->MODER|=0<<11*2;}	//PC5����ģʽ
#define SDA_OUT() {GPIOB->MODER&=~(3<<(11*2));GPIOB->MODER|=1<<11*2;} //PC5���ģʽ
//IO����
#define IIC_SCL(n)  (n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET)) //SCL
#define IIC_SDA(n)  (n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET)) //SDA
#define READ_SDA    HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)  //����SDA

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	 
#endif

