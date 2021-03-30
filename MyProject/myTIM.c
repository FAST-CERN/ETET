#include "main.h"

void TIM1_INIT(void)
{
     /*Output GPIO Port config*/
	   GPIO_InitTypeDef GPIO_InitStructure;
     
     //AF Config
     GPIO_PinAFConfig(GPIOA, GPIO_PinSource8 , GPIO_AF_2);	
	   GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_2);
	   	   
	   //GPIO Init Struct Def
	   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
	   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	   GPIO_Init(GPIOA, &GPIO_InitStructure);	   
	   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13;
	   GPIO_Init(GPIOB, &GPIO_InitStructure);
	   
	   /*Primary Settings*/ 
	   TIM_TimeBaseInitTypeDef TIM_StructInit;
     TIM_OCInitTypeDef  TIM_OCInitStructure;
	  
	   //Clock Source
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	   //BASE Struct Def
		 TIM_TimeBaseStructInit(&TIM_StructInit);
     TIM_StructInit.TIM_Period    = 9600-1;      
     TIM_StructInit.TIM_Prescaler = 0x0000;
     TIM_StructInit.TIM_ClockDivision = TIM_CKD_DIV1;
     TIM_StructInit.TIM_CounterMode   = TIM_CounterMode_Up;
     TIM_StructInit.TIM_RepetitionCounter = 0;
     TIM_TimeBaseInit(TIM1, &TIM_StructInit);
	
	   /*Output Config*/
	   //OC Struct Def
		 TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;
		 TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;
		 TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		 TIM_OCInitStructure.TIM_Pulse        = 1000;
		 TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;
		 TIM_OCInitStructure.TIM_OCNPolarity  = TIM_OCNPolarity_High;
		 TIM_OCInitStructure.TIM_OCIdleState  = TIM_OCIdleState_Set;
		 TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
		 TIM_OC1Init(TIM1, &TIM_OCInitStructure);
		 TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
		 
	   //ARR Preload Register
		 TIM_ARRPreloadConfig(TIM1, ENABLE);
		 
	   //PWM Out Enable
     TIM_CtrlPWMOutputs(TIM1, ENABLE);		 

	   /*Interrput Config*/		 
	   //CC1 IRQ EN
		 TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE); 
			 
	   //NVIC Config
		 NVIC_InitTypeDef NVIC_InitStructure;
     NVIC_InitStructure.NVIC_IRQChannel         = TIM1_CC_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
	   
	   /*TIM1 Enable*/
		 TIM_Cmd(TIM1, ENABLE);
}

