#ifndef __PID_H__
#define __PID_H__
#include "Rcc.h"
void Pid_Cacl(void);
void Pid_Display(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle);
void Tim2Pwm_Init(void);

struct Pid_Value  pid;

struct Pid_Value
{
    float       Set_Point;  //�趨Ŀ��
    float       Now_Point;  //��ǰ��ֵ
    float       Sum_Error;  //�����ۼ�
    float       Now_Error;  //����ƫ��
    float       Pre_Error;  //�ϴ�ƫ��
    float       Kp;         //��������
    float       Ti;         //���ֳ���
    float       Td;         //΢�ֳ���
    float       Pout;
    float       Iout;
    float       Dout;
    float       Out;
    float       Out0;
    
    uint8_t     Pid_Start;
    float       T;          //PID��������
    uint16_t    Pwm_Cycle;  //Pwm������
    uint8_t     Meun_Flag;
       
};

#endif