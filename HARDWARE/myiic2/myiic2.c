#include "myiic2.h"
#include "delay.h"
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

//初始化IIC2
void IIC2_Init(void)
{					     
	RCC->AHB1ENR|=1<<4;    //使能PORTE时钟	   	  
	GPIO_Set(GPIOE,PIN5|PIN6,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PE5/PE6设置 
	IIC2_SCL=1;
	IIC2_SDA=1;
}
//产生IIC2起始信号
void IIC2_Start(void)
{
	SDA2_OUT();     //sda线输出
	IIC2_SDA=1;	  	  
	IIC2_SCL=1;
	delay_us(4);
 	IIC2_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC2_SCL=0;//钳住I2C总线，准备发送或接收数据 
	delay_us(4);
}	  
//产生IIC2停止信号
void IIC2_Stop(void)
{
	SDA2_OUT();//sda线输出
	IIC2_SCL=0;
	IIC2_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC2_SCL=1; 
	IIC2_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC2_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA2_IN();      //SDA设置为输入  
	IIC2_SDA=1;delay_us(1);	   
	IIC2_SCL=1;delay_us(1);	 
	while(READ_SDA2)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC2_Stop();
			return 1;
		}
	}
	IIC2_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC2_Ack(void)
{
	IIC2_SCL=0;
	SDA2_OUT();
	IIC2_SDA=0;
	delay_us(2);
	IIC2_SCL=1;
	delay_us(2);
	IIC2_SCL=0;
}
//不产生ACK应答		    
void IIC2_NAck(void)
{
	IIC2_SCL=0;
	SDA2_OUT();
	IIC2_SDA=1;
	delay_us(2);
	IIC2_SCL=1;
	delay_us(2);
	IIC2_SCL=0;
}					 				     
//IIC2发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC2_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA2_OUT(); 	    
    IIC2_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC2_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC2_SCL=1;
		delay_us(2); 
		IIC2_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC2_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA2_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC2_SCL=0; 
        delay_us(2);
		IIC2_SCL=1;
        receive<<=1;
        if(READ_SDA2)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC2_NAck();//发送nACK
    else
        IIC2_Ack(); //发送ACK   
    return receive;
}



























