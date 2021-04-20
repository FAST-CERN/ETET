#include "main.h"

/**
*  @Brief EXIT Module Init
*/
void EXTI_INIT(void)
{  	 
	    /*GPIO Config*/
	    CAM_VSYNC_GPIO_INIT();
	
	    /*EXTI Config*/
			EXTI_InitTypeDef EXTI_InitStructure;														

			SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource7);		
			EXTI_StructInit(&EXTI_InitStructure);														
			EXTI_InitStructure.EXTI_Line    = EXTI_Line7;			
			EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;										
			EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;													
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;											
			EXTI_Init(&EXTI_InitStructure);															
	  
	    /*NVIC Config*/
	    NVIC_InitTypeDef NVIC_InitStructure;
	
		  NVIC_InitStructure.NVIC_IRQChannel         = EXTI4_15_IRQn;										
			NVIC_InitStructure.NVIC_IRQChannelPriority = 2;							
			NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;									
			NVIC_Init(&NVIC_InitStructure);		
}
