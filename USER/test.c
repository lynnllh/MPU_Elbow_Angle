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
	u8 t=0,report=1,flag=0;			//默认开启上报
	u8 key;
	float q[4]={1.0f,0.0f,0.0f,0.0f},ang=0.0f,tempp[4]={1.0f,0.0f,0.0f,0.0f};
	float mpu2_q_t[4]={1,0,0,0},mpu2_q_t_I[4]={1,0,0,0};
	float pitch,roll,yaw; 		//欧拉角
	short aacx,aacy,aacz;		//加速度传感器原始数据
	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
	short temp;					//温度
	Stm32_Clock_Init(336,8,2,7);//设置时钟,168Mhz 
	delay_init(168);			//延时初始化  
	uart_init(84,115200);		//初始化串口波特率为500000
	usmart_dev.init(84);		//初始化USMART
	LED_Init();					//初始化LED 
	KEY_Init();					//初始化按键
 	LCD_Init();					//LCD初始化
	MPU_Init();					//初始化MPU6050
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"MPU6050 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/9");
	while(mpu_dmp_init())
	{
		LCD_ShowString(30,130,200,16,16,"MPU6050 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}
	LCD_ShowString(30,130,200,16,16,"MPU6050 OK");
	LCD_ShowString(30,150,200,16,16,"KEY0:UPLOAD ON/OFF");
	POINT_COLOR=BLUE;//设置字体为蓝色 
 	LCD_ShowString(30,170,200,16,16,"UPLOAD ON ");	 
 	LCD_ShowString(30,200,200,16,16," Temp:    . C");	
 	LCD_ShowString(30,220,200,16,16,"Pitch:    . C");	
 	LCD_ShowString(30,240,200,16,16," Roll:    . C");	 
 	LCD_ShowString(30,260,200,16,16," Yaw :    . C");	 
 	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY0_PRES)
		{
			report=!report;
			if(report)LCD_ShowString(30,170,200,16,16,"UPLOAD ON ");
			else LCD_ShowString(30,170,200,16,16,"UPLOAD OFF");
		}
	
		if((flag=mpu_dmp_get_data(&pitch,&roll,&yaw,q))==0)
		{ 
				if (WKUP_PRES==key)
				{
					LED0=~LED0;	
					mpu2_q_t[0]=q[0];mpu2_q_t[1]=q[1];mpu2_q_t[2]=q[2];mpu2_q_t[3]=q[3];
					Quat_Inv(mpu2_q_t,mpu2_q_t_I);			
				}
			temp=MPU_Get_Temperature();	//得到温度值
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
			
			if((t%10)==0)
			{ 
				if(temp<0)
				{
					LCD_ShowChar(30+48,200,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(30+48,200,' ',16,0);		//去掉负号 
				LCD_ShowNum(30+48+8,200,temp/100,3,16);		//显示整数部分	    
				LCD_ShowNum(30+48+40,200,temp%10,1,16);		//显示小数部分 
				temp=pitch*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48,220,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(30+48,220,' ',16,0);		//去掉负号 
				LCD_ShowNum(30+48+8,220,temp/10,3,16);		//显示整数部分	    
				LCD_ShowNum(30+48+40,220,temp%10,1,16);		//显示小数部分 
				temp=roll*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48,240,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(30+48,240,' ',16,0);		//去掉负号 
				LCD_ShowNum(30+48+8,240,temp/10,3,16);		//显示整数部分	    
				LCD_ShowNum(30+48+40,240,temp%10,1,16);		//显示小数部分 
				temp=yaw*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48,260,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(30+48,260,' ',16,0);		//去掉负号 
				LCD_ShowNum(30+48+8,260,temp/10,3,16);		//显示整数部分	    
				LCD_ShowNum(30+48+40,260,temp%10,1,16);		//显示小数部分  
				t=0;
				Quat_Product(q,mpu2_q_t_I,tempp);
				ang=2.0f*acos(tempp[0]);
				ang=ang*57.29578049f;
				temp=ang*10;
				LCD_ShowNum(30,280,temp/10,3,16);	
				LCD_ShowNum(30+32,280,temp%10,1,16);	
				//printf("%0.2f\n",ang);
				LED0=!LED0;//LED闪烁
			}
		}
		t++; 
		printf("%d/n ", flag);
	} 	
}
















