#include "Main.h"
extern UART_HandleTypeDef UART_Initure;
extern UART_HandleTypeDef UART_TwoIniture;
extern TIM_HandleTypeDef htim4;
extern uint8_t ucDs18b20Id[8];
extern uint8_t rxbuff_one[9];
extern uint8_t rxbuff_two[9];
int main(void)
{ 
    /*************************************************/
    HAL_Init();
    SystemClock_Config();
    Led_Config();
    Usart1_Config();
    Usart2_Config();
    NVIC_Init();
    /*************************************************/
    /*���ڹ��ܲ��� */
    printf("���\n");
    HAL_UART_Receive_IT(&UART_Initure   , rxbuff_one, 1);
    HAL_UART_Receive_IT(&UART_TwoIniture, rxbuff_one, 1);
    //����pwm���
    Pwm_Init();
    Pwm_Gpio_Init();    
    //Oled
    Init_Tft();
    Test_Demo();
    //����
    Key_Init();
    //��Ϊ��ʱ��ʹ��
    Tim2_Init();
    Tim2_Nvic();    
    while(1)
    {
        Pid_Cacl();
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13, GPIO_PIN_RESET); 
        Delay_Ms(100);
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13, GPIO_PIN_SET); 
        Delay_Ms(100);
    }
}

/********************************************************
* @����: Led��ʼ��                                  
* @����: ��                                            
* @��ֵ: ��
* @˵��: ��
*********************************************************/
void Led_Config(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOC_CLK_ENABLE(); 
    GPIO_Initure.Pin   = GPIO_PIN_13; 
    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP; 
    GPIO_Initure.Pull  = GPIO_PULLUP; 
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; 
    HAL_GPIO_Init(GPIOC, &GPIO_Initure);
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13, GPIO_PIN_RESET); 
}




