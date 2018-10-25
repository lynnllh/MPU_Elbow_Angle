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
//ALIENTEK ̽����STM32F407������ ʵ��32
//MPU6050���ᴫ���� ʵ�� 
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾


int main(void)
{       
	u8 t=0,flag=0;			//Ĭ�Ͽ����ϱ�
	u8 key;
	float q1[4]={1.0f,0.0f,0.0f,0.0f},q2[4]={1.0f,0.0f,0.0f,0.0f},ang=0.0f;
	float q2_Inv[4]={1,0,0,0},gesture[4]={1,0,0,0};
	float pitch1,roll1,yaw1,pitch2,roll2,yaw2; 		//ŷ����
	//short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	//short gyrox,gyroy,gyroz;	//������ԭʼ����
	short temp;					//�¶�
	Stm32_Clock_Init(336,8,2,7);//����ʱ��,168Mhz 
	delay_init(168);			//��ʱ��ʼ��  
	uart_init(84,115200);		//��ʼ�����ڲ�����Ϊ500000
	usmart_dev.init(84);		//��ʼ��USMART
	LED_Init();					//��ʼ��LED 
	KEY_Init();					//��ʼ������
 	LCD_Init();					//LCD��ʼ��
	MPU_Init(1);					//��ʼ��MPU6050
	MPU_Init(2);					//��ʼ��MPU6050
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
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
	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
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
				
			temp=MPU_Get_Temperature(1);	//�õ��¶�ֵ
			//MPU_Get_Accelerometer(&aacx,&aacy,&aacz,2);	//�õ����ٶȴ���������
			//MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz,2);	//�õ�����������
			Quat_Inv(q2,q2_Inv);
			Quat_Product(q2_Inv,q1,gesture);
			Quat_Cal_Angle(gesture,&ang);
			if((t%10)==0)
			{ 
				if(temp<0)
				{
					LCD_ShowChar(30+48,200,'-',16,0);		//��ʾ����
					temp=-temp;		//תΪ����
				}else LCD_ShowChar(30+48,200,' ',16,0);		//ȥ������ 
				LCD_ShowNum(30+48+8,220,temp/100,3,16);		//��ʾ��������	    
				LCD_ShowNum(30+48+40,220,temp%10,1,16);		//��ʾС������ 
				
				temp=pitch1*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48,240,'-',16,0);		//��ʾ����
					temp=-temp;		//תΪ����
				}else LCD_ShowChar(30+48,240,' ',16,0);		//ȥ������ 
				LCD_ShowNum(30+48+8,240,temp/10,3,16);		//��ʾ��������	    
				LCD_ShowNum(30+48+40,240,temp%10,1,16);		//��ʾС������ 
					temp=pitch2*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48+188,240,'-',16,0);		//��ʾ����
					temp=-temp;		//תΪ����
				}else LCD_ShowChar(30+48+188,240,' ',16,0);		//ȥ������ 
				LCD_ShowNum(30+48+8+188,240,temp/10,3,16);		//��ʾ��������	    
				LCD_ShowNum(30+48+40+188,240,temp%10,1,16);		//��ʾС������ 
				
				
				temp=roll1*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48,260,'-',16,0);		//��ʾ����
					temp=-temp;		//תΪ����
				}else LCD_ShowChar(30+48,260,' ',16,0);		//ȥ������ 
				LCD_ShowNum(30+48+8,260,temp/10,3,16);		//��ʾ��������	    
				LCD_ShowNum(30+48+40,260,temp%10,1,16);		//��ʾС������ 
				temp=roll2*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48+188,260,'-',16,0);		//��ʾ����
					temp=-temp;		//תΪ����
				}else LCD_ShowChar(30+48+188,260,' ',16,0);		//ȥ������ 
				LCD_ShowNum(30+48+8+188,260,temp/10,3,16);		//��ʾ��������	    
				LCD_ShowNum(30+48+40+188,260,temp%10,1,16);		//��ʾС������ 
				
				
				temp=yaw1*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48,280,'-',16,0);		//��ʾ����
					temp=-temp;		//תΪ����
				}else LCD_ShowChar(30+48,280,' ',16,0);		//ȥ������ 
				LCD_ShowNum(30+48+8,280,temp/10,3,16);		//��ʾ��������	    
				LCD_ShowNum(30+48+40,280,temp%10,1,16);		//��ʾС������ 
				temp=yaw2*10;
				if(temp<0)
				{
					LCD_ShowChar(30+48+188,280,'-',16,0);		//��ʾ����
					temp=-temp;		//תΪ����
				}else LCD_ShowChar(30+48+188,280,' ',16,0);		//ȥ������ 
				LCD_ShowNum(30+48+8+188,280,temp/10,3,16);		//��ʾ��������	    
				LCD_ShowNum(30+48+40+188,280,temp%10,1,16);		//��ʾС������
				
				t=0;
				
				temp=ang*10;
				LCD_ShowNum(30,300,temp/10,3,16);	
				LCD_ShowNum(30+32,300,temp%10,1,16);	
				//printf("%0.2f\n",ang);
				LED0=!LED0;//LED��˸
			}
		}
		t++; 
		temp=ang*10;
		printf("%d\n",temp/10);
	} 	
}
















