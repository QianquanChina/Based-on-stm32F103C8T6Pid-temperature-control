#include "Rcc.h"
#include "stdio.h"
#include "string.h"

/********************************************************
* ��    ��:ϵͳʱ�ӳ�ʼ��                                  
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  /** Initializes the CPU, AHB and APB busses clocks 
  */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler("HAL_RCC_OscConfig");
    }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler("HAL_RCC_ClockConfig");
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler("HAL_RCCEx_PeriphCLKConfig");
    }

}
/********************************************************
* ��    ��:��ʼ��������                                 
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
void Error_Handler(const char *errorbuff)
{
    while (1)
    {  
        printf("%s:��ʼ��ʧ���������\n",errorbuff);
        Delay_Ms(1000);
    }
}
/********************************************************
* ��    ��:�δ��жϺ���                                 
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
void SysTick_Handler(void)
{
    HAL_IncTick();
}
/********************************************************
* ��    ��:������ת�����ַ���                                  
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
static char table[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
void Num_Char(char *str, double number, uint8_t g, uint8_t l)
{
    uint8_t i;
    int temp = number/1;
    double t2 = 0.0;
    for (i = 1; i<=g; i++)
    {
        if (temp==0)
            str[g-i] = table[0];
        else
            str[g-i] = table[temp%10];
        temp = temp/10;
    }
    *(str+g) = '.';
    temp = 0;
    t2 = number;
    for(i=1; i<=l; i++)
    {
        temp = t2*10;
        str[g+i] = table[temp%10];
        t2 = t2*10;
    }
    *(str+g+l+1) = '\0';
}

/********************************************************
* ��    ��:��׼������ʱ                                  
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
void Delay_Ms(uint32_t i)
{
	uint32_t temp;
    SysTick->LOAD=9000*i;      
    SysTick->CTRL=0X01;        
    SysTick->VAL=0;            
    do
    {
        temp=SysTick->CTRL;       
    }
    while((temp&0x01)&&(!(temp&(1<<16))));    
    SysTick->CTRL=0;    
    SysTick->VAL=0;        
}
/********************************************************
* ��    ��:��׼΢����ʱ                                  
* ��    ��:��                                            
* ��    ֵ:��
* ˵    ��:��
*********************************************************/
void Delay_Us(uint32_t i)
{
    uint32_t temp;
    SysTick->LOAD=9*i;         
    SysTick->CTRL=0X01;         
    SysTick->VAL=0;                
    do
    {
        temp=SysTick->CTRL;           
    }
    while((temp&0x01)&&(!(temp&(1<<16))));     
    SysTick->CTRL=0;    
    SysTick->VAL=0;        
}
