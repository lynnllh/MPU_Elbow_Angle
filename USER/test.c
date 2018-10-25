#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "usmart.h" 
#include "mpu6050.h"
#include "inv_mpu.h"
#include "math.h"
#include "quatcal.h"
#include "inv_mpu_dmp_motion_driver.h" 
//ALIENTEK 探索者STM32F407开发板 实验32
//MPU6050六轴传感器 实验 
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司


int main(void)
{       
	u8 t=0,flag=0;			//默认开启上报
	u8 key;
	float q1[4]={1.0f,0.0f,0.0f,0.0f},q2[4]={1.0f,0.0f,0.0f,0.0f},ang=0.0f;
	float q2_Inv[4]={1,0,0,0},gesture[4]={1,0,0,0};
	float pitch1,roll1,yaw1,pitch2,roll2,yaw2; 		//欧拉角
	//short aacx,aacy,aacz;		//加速度传感器原始数据
	//short gyrox,gyroy,gyroz;	//陀螺仪原始数据
	short temp;					//温度
	Stm32_Clock_Init(336,8,2,7);//设置时钟,168Mhz 
	delay_init(168);			//延时初始化  
	uart_init(84,115200);		//初始化串口波特率为500000
	usmart_dev.init(84);		//初始化USMART
	LED_Init();					//初始化LED 
	KEY_Init();					//初始化按键
 	LCD_Init();					//LCD初始化
	MPU_Init(1);					//初始化MPU6050
	MPU_Init(2);					//初始化MPU6050
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"MPU6050 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/9");
	while(mpu_dmp_init(2)|| mpu_dmp_init(1))
	{
		LCD_ShowString(30,130,200,16,16,"MPU6050 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
		//printf("%d\n",flag);
	}
	LCD_ShowString(30,130,200,16,16,"MPU6050 OK");
	LCD_ShowString(30,150,200,16,16,"KEY0:UPLOAD ON/OFF");
	POINT_COLOR=BLUE;//设置字体为蓝色 
 	LCD_ShowString(30,170,200,16,16,"UPLOAD ON ");	 
	LCD_ShowString(30,200,200,16,16,"MPU1 ");		LCD_ShowString(30+88+100,200,200,16,16,"MPU2 ");	
 	LCD_ShowString(30,220,200,16,16," Temp:    . C");		
 	LCD_ShowString(30,240,200,16,16,"Pitch:    . C");	LCD_ShowString(30+88+100,240,200,16,16,"Pitch:    . C");	
 	LCD_ShowString(30,260,200,16,16," Roll:    . C");	LCD_ShowString(30+88+100,260,200,16,16," Roll:    . C");	
 	LCD_ShowString(30,280,200,16,16," Yaw :    . C");	LCD_ShowString(30+88+100,280,200,16,16," Yaw :    . C");	 
 	while(1)
	{
		key=KEY_Scan(0);
			
		if(mpu_dmp_get_data(&pitch1,&roll1,&yaw1,q1,1)==0 && mpu_dmp_get_data(&pitch2,&roll2,&yaw2,q2,2)==0)
		{ 
				
			temp=MPU_Get_Temperature(1);	//得到温度值
			//MPU_Get_Accelerometer(&aacx,&aacy,&aacz,2);	//得到加速度传感器数据
			//MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz,2);	//得到陀螺仪数据
			Quat_Inv(q2,q2_Inv);
			Quat_Product(q2_Inv,q1,gesture);
			Quat_Cal_Angle(gesture,&ang);
			if((t%10)==0)
			{ 
				if(temp<0)
				{
					LCD_ShowChar(30+48,200,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(30+48,200,' ',16,0);		//去掉负号 
				LCD_ShowNum(30+48+8,220,temp/100,3,16);		//显示整数部分	    
				LCD_ShowNum(30+48+40,220,temp%10,1,16);		//显示小数部分 
				
				temp=pitch1*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48,240,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(30+48,240,' ',16,0);		//去掉负号 
				LCD_ShowNum(30+48+8,240,temp/10,3,16);		//显示整数部分	    
				LCD_ShowNum(30+48+40,240,temp%10,1,16);		//显示小数部分 
					temp=pitch2*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48+188,240,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(30+48+188,240,' ',16,0);		//去掉负号 
				LCD_ShowNum(30+48+8+188,240,temp/10,3,16);		//显示整数部分	    
				LCD_ShowNum(30+48+40+188,240,temp%10,1,16);		//显示小数部分 
				
				
				temp=roll1*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48,260,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(30+48,260,' ',16,0);		//去掉负号 
				LCD_ShowNum(30+48+8,260,temp/10,3,16);		//显示整数部分	    
				LCD_ShowNum(30+48+40,260,temp%10,1,16);		//显示小数部分 
				temp=roll2*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48+188,260,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(30+48+188,260,' ',16,0);		//去掉负号 
				LCD_ShowNum(30+48+8+188,260,temp/10,3,16);		//显示整数部分	    
				LCD_ShowNum(30+48+40+188,260,temp%10,1,16);		//显示小数部分 
				
				
				temp=yaw1*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48,280,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(30+48,280,' ',16,0);		//去掉负号 
				LCD_ShowNum(30+48+8,280,temp/10,3,16);		//显示整数部分	    
				LCD_ShowNum(30+48+40,280,temp%10,1,16);		//显示小数部分 
				temp=yaw2*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48+188,280,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(30+48+188,280,' ',16,0);		//去掉负号 
				LCD_ShowNum(30+48+8+188,280,temp/10,3,16);		//显示整数部分	    
				LCD_ShowNum(30+48+40+188,280,temp%10,1,16);		//显示小数部分
				
				t=0;
				
				temp=ang*10;
				LCD_ShowNum(30,300,temp/10,3,16);	
				LCD_ShowNum(30+32,300,temp%10,1,16);	
				//printf("%0.2f\n",ang);
				LED0=!LED0;//LED闪烁
			}
		}
		t++; 
		temp=ang*10;
		printf("%d\n",temp/10);
	} 	
}
















