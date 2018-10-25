#ifndef __MYIIC2_H
#define __MYIIC2_H
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//IIC2 ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
   	   		   
//IO��������
#define SDA2_IN()  {GPIOE->MODER&=~(3<<(5*2));GPIOE->MODER|=0<<(5*2);}	//PE5����ģʽ
#define SDA2_OUT() {GPIOE->MODER&=~(3<<(5*2));GPIOE->MODER|=1<<(5*2);} //PE5���ģʽ
//IO��������	 
#define IIC2_SCL    PEout(6) //SCL
#define IIC2_SDA    PEout(5) //SDA	 
#define READ_SDA2   PEin(5)  //����SDA 

//IIC2���в�������
void IIC2_Init(void);                //��ʼ��IIC2��IO��				 
void IIC2_Start(void);				//����IIC2��ʼ�ź�
void IIC2_Stop(void);	  			//����IIC2ֹͣ�ź�
void IIC2_Send_Byte(u8 txd);			//IIC2����һ���ֽ�
u8 IIC2_Read_Byte(unsigned char ack);//IIC2��ȡһ���ֽ�
u8 IIC2_Wait_Ack(void); 				//IIC2�ȴ�ACK�ź�
void IIC2_Ack(void);					//IIC2����ACK�ź�
void IIC2_NAck(void);				//IIC2������ACK�ź� 
#endif
















