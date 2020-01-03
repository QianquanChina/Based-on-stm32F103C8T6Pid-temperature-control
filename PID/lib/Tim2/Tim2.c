#include "Tim2.h"
#include "Pid.h"
#include "key.h"
#include "GUI.h"
#include "Lcd_Driver.h"
extern struct Pid_Value  pid_value;
struct Key_Tim Timer;
extern struct Key_Pid key;
extern uint8_t exit_flag;
/********************************************************
* ��    ��:Tim2�ĳ�ʼ��                                  
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
TIM_HandleTypeDef htim2;
void Tim2_Init(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 72-1;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 20000-1;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        Error_Handler("HAL_TIM_Base_Init");
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler("HAL_TIM_ConfigClockSource");
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
    {
        Error_Handler("HAL_TIMEx_MasterConfigSynchronization");
    }
    /*�򿪶�ʱ��2 */
    if(HAL_TIM_Base_Start_IT(&htim2) != HAL_OK)
    {
        Error_Handler("HAL_TIM_Base_Start_IT");
    }
}
/********************************************************
* ��    ��:Tim2�Ļص�����ʼ��                                  
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{
    if(htim_base->Instance==TIM2)
    {
        __HAL_RCC_TIM2_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(TIM2_IRQn);
    } 
}
/********************************************************
* ��    ��:Tim2�Ļص���ʼ��                                  
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
    if(htim_base->Instance==TIM2)
    {
        __HAL_RCC_TIM2_CLK_ENABLE();
    }
    
}
/********************************************************
* ��    ��:Tim2��NVIC��ʼ��                                  
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
void Tim2_Nvic(void)
{
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);   
}
/********************************************************
* ��    ��:Tim2�жϺ���                                  
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim2);
}
/********************************************************
* ��    ��:Tim2�ص�����                                  
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
struct Flag_Time flag_time = 
{
    .Pid_Flag = 0,
    .Key_Flag = 0,
    .San_Flag = 0,
    .KeyT_Flag = 0,
};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim == &htim2)
    {
        if(exit_flag == 1)
        {
            if( ++flag_time.KeyT_Flag > 50 )
            {
                flag_time.KeyT_Flag = 0;
                Timer.Keyt_Flag = 1;
            //  printf("Timer.Keyt_Flag = %d\n",Timer.Keyt_Flag);
            }
        }
        //��������û�е�
        if(++flag_time.Pid_Flag >= pid.T)
        {
           //pid��ʼִ�� ִ��ʱ��Ϊ60msһ��
           pid.Pid_Start = 1;
        }
        //��˸����
        if(key.select_flag > 0)
        {  
            if(++flag_time.Key_Flag > 50)
            {     
                
                flag_time.Key_Flag = 0;
                if(++flag_time.San_Flag >= 3)
                {
                    flag_time.San_Flag = 1;
                }
            }
            if(flag_time.San_Flag == 1)
            { 
                switch(key.select_flag)
                {
                case 1:
                    Gui_DrawFont_GBK16(10, 25, BLUE, GRAY0, (uint8_t *)("T :"));   
                    break;
                case 2:
                    Gui_DrawFont_GBK16(10, 45, BLUE, GRAY0, (uint8_t *)("Te:"));   
                    break;
                case 3:
                    Gui_DrawFont_GBK16(10, 65, BLUE, GRAY0, (uint8_t *)("Kp:"));
                    break;
                case 4:
                    Gui_DrawFont_GBK16(10, 85, BLUE, GRAY0, (uint8_t *)("Ti:"));
                    break;
                case 5:
                    Gui_DrawFont_GBK16(10, 105,BLUE, GRAY0, (uint8_t *)("Td:"));
                    break;                                  
                default:
                    break;
                        
                }
            }else
            if(flag_time.San_Flag == 2)
            {
                switch (key.select_flag)
                {
                case 1:
                    Gui_DrawFont_GBK16(10, 25, BLUE, GREEN, (uint8_t *)("T :"));   
                    break;                    
                case 2:
                    Gui_DrawFont_GBK16(10, 45, BLUE, GREEN, (uint8_t *)("Te:"));
                    Gui_DrawFont_GBK16(10, 25, BLUE, GREEN, (uint8_t *)("T :")); 
                    break;
                case 3:
                    Gui_DrawFont_GBK16(10, 65, BLUE, GREEN, (uint8_t *)("Kp:"));
                    Gui_DrawFont_GBK16(10, 45, BLUE, GREEN, (uint8_t *)("Te:"));
                    break;
                case 4:
                    Gui_DrawFont_GBK16(10, 65, BLUE, GREEN, (uint8_t *)("Kp:"));
                    Gui_DrawFont_GBK16(10, 85, BLUE, GREEN, (uint8_t *)("Ti:"));
                    break;
                case 5:
                    Gui_DrawFont_GBK16(10, 85, BLUE, GREEN, (uint8_t *)("Ti:"));
                    Gui_DrawFont_GBK16(10, 105,BLUE, GREEN, (uint8_t *)("Td:"));
                    break;                                  
                default:
                    break;
                }
            }   
        }
    }
}
