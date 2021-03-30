#include "main.h"
 
void SysTick_Handler(void)
{
     Decre_Delay_ms();
     TaskHandler();	
}

void TIM1_CC_IRQHandler(void)
{
     /*Clear The Capture & Compare Flag*/
     if(TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
     {
        TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
     }
}
 
void UART1_IRQHandler(void)
{
     UART1_IT_ReceiveDATA();
}

