/* Includes ------------------------------------------------------------------*/
#include "Lcd_Driver.h"
#include "Picture.h"
#include "TFT_demo.h"
#include "GUI.h"
#include "Pid.h"
#include "key.h"
#include "Tim2.h"
#include "Rcc.h"
#include "Pwm.h"


extern struct Pid_Value  pid;
extern struct Flag_Time flag_time ;

typedef  unsigned int u16;
unsigned char Num[10]={0,1,2,3,4,5,6,7,8,9};

void Num_Test(void)
{
	u8 i=0;
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(16,20,RED,GRAY0,(uint8_t *)("Num Test") );
	Delay_Ms(1000);
	Lcd_Clear(GRAY0);

	for(i=0;i<10;i++)
	{
		//Gui_DrawFont_Num32((i%3)*40,32*(i/3)+5,RED,GRAY0,Num[i+1] );
		Delay_Ms(100);
	}
	
}

void Font_Test(void)
{
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(16,10,BLUE,GRAY0,   (uint8_t *)("�ػ�"));
	Delay_Ms(1000);
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(8,8,BLACK,GRAY0  ,  (uint8_t *)("֧��") );
	Gui_DrawFont_GBK16(16,28,GREEN,GRAY0,  (uint8_t *)("֧��") );
	Gui_DrawFont_GBK16(16,48,RED,GRAY0,    (uint8_t *)("֧��") );
	Gui_DrawFont_GBK16(0,68,BLUE,GRAY0,    (uint8_t *)(" Tel:1234567890") );
	Gui_DrawFont_GBK16(0,88,RED,GRAY0,     (uint8_t *)(" mcudev.taobao") );	
	Delay_Ms(1800);	
}
void Color_Test(void)
{
	u8 i=1;
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(20,10,BLUE,GRAY0,(uint8_t *)("Color Test") );
	Delay_Ms(500);
	while(i--)
	{
		Lcd_Clear(WHITE);
		Delay_Ms(500);
		Lcd_Clear(BLACK);
		Delay_Ms(500);
		Lcd_Clear(RED);
		Delay_Ms(500);
	    Lcd_Clear(GREEN);
		Delay_Ms(500);
	    Lcd_Clear(BLUE);
		Delay_Ms(500);
	}		
}

//ȡģ��ʽ ˮƽɨ�� ������ ��λ��ǰ
void showimage(const unsigned char *p) //��ʾ40*40 QQͼƬ
{
  	int i,j,k; 
	unsigned char picH,picL;
	Lcd_Clear(WHITE); //���� 
	
	for(k=0;k<1;k++)
	{
	   	for(j=1;j<2;j++)
		{	
			Lcd_SetRegion(40*j,40*k,40*j+39,40*k+39);		//��������
		    for(i=0;i<40*40;i++)
			 {	
			 	picL=*(p+i*2);	//���ݵ�λ��ǰ
				picH=*(p+i*2+1);				
				LCD_WriteData_16Bit(picH<<8|picL);  						
			 }	
		 }
	}		
}

//ȡģ��ʽ ˮƽɨ�� ������ ��λ��ǰ
void Fullscreen_showimage(const unsigned char *p) //��ʾ128*128 ͼƬ
{
  int i;
  //int	j,k;
	unsigned char picH,picL;
	Lcd_Clear(WHITE); //����  
		Lcd_SetRegion(0,0,127,127);		//��������:ɨ����㵽�յ�0��127���պ�128����
		for(i=0;i<128*128;i++)
		{	
			picL=*(p+i*2);	//���ݵ�λ��ǰ
			picH=*(p+i*2+1);				
			LCD_WriteData_16Bit(picH<<8|picL);  						
		}	
}
/********************************************************
* ��    ��:TFT�˵��ϵ���ʾ�˵�                                   
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
void Test_Demo(void)
{	
	First_Menu();
}
/********************************************************
* ��    ��:TFT��ʼ��                                   
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
void Init_Tft(void)
{
	Lcd_Init();
	Lcd_Clear(GRAY0);
}
/********************************************************
* ��    ��:PIDһ���˵�����                                   
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
extern uint8_t key_meun;
struct Meun meun = 
{
	.Frist_meun  = 0,
	.Second_meun = 0,
	.Thired_meun = 0,
};
void First_Menu(void)
{
	meun.Frist_meun  = 1;
    meun.Second_meun = 0;
    meun.Thired_meun = 0;

	//�ر�PWM���
    HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_1);

	Lcd_Clear(GRAY0);
	showimage(gImage_qq);
	if(key_meun == 2)
	{
		Gui_DrawFont_GBK16(10, 65, BLUE,  WHITE, (uint8_t *)("��"));
	}else
	if(key_meun == 3)
	{
		Gui_DrawFont_GBK16(10, 85, BLUE,  WHITE, (uint8_t *)("��"));
	}
	Gui_DrawFont_GBK16(25, 65, RED,   WHITE, (uint8_t *)("��������ҳ��"));
	Gui_DrawFont_GBK16(25, 85, RED,   WHITE, (uint8_t *)("������ʾҳ��"));
}
/********************************************************
* ��    ��:PID�����˵�����                                   
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
void Second_Menu(void)
{
    meun.Frist_meun  = 0;
    meun.Second_meun = 1;
    meun.Thired_meun = 0;	
	//�ر�PWM���
    HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_1);
	Lcd_Clear(GRAY0);
	DisplayButtonUp(4, 3, 40 , 22);
	Gui_DrawFont_GBK16(7 , 5,BLUE, GRAY0, (uint8_t *)("ѡ��"));
	
	Gui_DrawFont_GBK16(87, 5,BLUE, GRAY0, (uint8_t *)("����"));
	DisplayButtonUp(84, 3, 120, 22);

	Gui_DrawFont_GBK16(47, 5,  RED,  GRAY0, (uint8_t *)("���"));
	Gui_DrawFont_GBK16(10, 25, BLUE, GREEN, (uint8_t *)("T :"));
	Gui_DrawFont_GBK16(10, 45, BLUE, GREEN, (uint8_t *)("Te:"));
	Gui_DrawFont_GBK16(10, 65, BLUE, GREEN, (uint8_t *)("Kp:"));
	Gui_DrawFont_GBK16(10, 85, BLUE, GREEN, (uint8_t *)("Ti:"));
	Gui_DrawFont_GBK16(10, 105,BLUE, GREEN, (uint8_t *)("Td:"));

	Num_Char((char *)key.Buff_SetPoint, pid.Set_Point, 4, 1);
	Num_Char((char *)key.Buff_T,  pid.T,  4, 1);
	Num_Char((char *)key.Buff_Kp, pid.Kp, 4, 1);
    Num_Char((char *)key.Buff_Ti, pid.Ti, 7, 1);
    Num_Char((char *)key.Buff_Td, pid.Td, 4, 1);
	Gui_DrawFont_GBK16(35, 25 , BLUE, GRAY0, (uint8_t *)key.Buff_T);
	Gui_DrawFont_GBK16(35, 45 , BLUE, GRAY0, (uint8_t *)key.Buff_SetPoint);
    Gui_DrawFont_GBK16(35, 65 , BLUE, GRAY0, (uint8_t *)key.Buff_Kp);
    Gui_DrawFont_GBK16(35, 85 , BLUE, GRAY0, (uint8_t *)key.Buff_Ti);
    Gui_DrawFont_GBK16(35, 105, BLUE, GRAY0, (uint8_t *)key.Buff_Td);

	
	Gui_DrawFont_GBK16(87, 43,BLUE, GRAY0, (uint8_t *)("����"));
	DisplayButtonUp(84, 41, 120, 60);//82-63 = 19 2
		
	Gui_DrawFont_GBK16(87, 63,BLUE, GRAY0, (uint8_t *)("��С"));
	DisplayButtonUp(84, 61, 120, 80); 
		
	Gui_DrawFont_GBK16(87, 105,BLUE, GRAY0, (uint8_t *)("ȷ��"));
	DisplayButtonUp(84, 103, 120, 121); 

}
/********************************************************
* ��    ��:PID�����˵�����                                   
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
void Thired_Meun(void)
{
	meun.Frist_meun  = 0;
    meun.Second_meun = 0;
    meun.Thired_meun = 1;
	//����PWM���
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);

	Lcd_Clear(GRAY0);
	DisplayButtonUp(84, 3, 120, 22);
	Gui_DrawFont_GBK16(87, 5,  BLUE, GRAY0, (uint8_t *)("����"));
	Gui_DrawFont_GBK16(47, 5,  RED,  GRAY0, (uint8_t *)("���")  );
	Gui_DrawFont_GBK16(30, 25, RED,  GRAY0, (uint8_t *)("�¿� PID"));

	Gui_DrawFont_GBK16(10, 45, BLUE, GRAY0, (uint8_t *)("Sout:"));
	DisplayButtonUp(7, 45, 48, 61); 

	Gui_DrawFont_GBK16(10, 65, BLUE, GRAY0, (uint8_t *)("Pout:"));
	DisplayButtonUp(7, 65, 48, 81); 

	Gui_DrawFont_GBK16(10, 85, BLUE, GRAY0, (uint8_t *)("Iout:"));
	DisplayButtonUp(7, 85, 48, 101); 	

	Gui_DrawFont_GBK16(10, 105, BLUE, GRAY0, (uint8_t *)("Dout:"));	
	DisplayButtonUp(7, 105, 48, 121); 
}


