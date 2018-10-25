#ifndef __MYIIC2_H
#define __MYIIC2_H
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//IIC2 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/6
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
   	   		   
//IO方向设置
#define SDA2_IN()  {GPIOE->MODER&=~(3<<(5*2));GPIOE->MODER|=0<<(5*2);}	//PE5输入模式
#define SDA2_OUT() {GPIOE->MODER&=~(3<<(5*2));GPIOE->MODER|=1<<(5*2);} //PE5输出模式
//IO操作函数	 
#define IIC2_SCL    PEout(6) //SCL
#define IIC2_SDA    PEout(5) //SDA	 
#define READ_SDA2   PEin(5)  //输入SDA 

//IIC2所有操作函数
void IIC2_Init(void);                //初始化IIC2的IO口				 
void IIC2_Start(void);				//发送IIC2开始信号
void IIC2_Stop(void);	  			//发送IIC2停止信号
void IIC2_Send_Byte(u8 txd);			//IIC2发送一个字节
u8 IIC2_Read_Byte(unsigned char ack);//IIC2读取一个字节
u8 IIC2_Wait_Ack(void); 				//IIC2等待ACK信号
void IIC2_Ack(void);					//IIC2发送ACK信号
void IIC2_NAck(void);				//IIC2不发送ACK信号 
#endif
















