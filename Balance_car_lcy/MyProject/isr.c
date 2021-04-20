#include "main.h"
 
//extern uint8_t TSKH_FLAG;
 
void SysTick_Handler(void)
{
     Decre_Delay_ms();
  //   TSKH_FLAG = 1;
	   TaskHandler();
}

void TIM1_CC_IRQHandler(void)
{
     /*Clear The Capture & Compare Flag*/
}
 
void TIM2_IRQHandler(void)
{
     /*Clear The Capture & Compare Flag*/
     if(TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
     {
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
     }
		 
		 if(TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
     {
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
     }
     if(TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)
     {
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
     }
		 
		 if(TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET)
     {
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);
     }
}

void TIM3_IRQHandler(void)
{
     /*Clear The Capture & Compare Flag*/
}

void UART1_IRQHandler(void)
{
     UART1_IT_ReceiveDATA();
}


void UART2_IRQHandler(void)
{
     UART2_IT_ReceiveDATA();
}

void DMA1_Channel4_5_IRQHandler(void)
{
     DMA1_CH14_IT_CallBack();
}

void EXTI4_15_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line7))												
	{
		 EXTI_ClearFlag(EXTI_Line7);
		 
		 CAM_VSYNC_ITCallback();
	}
}


