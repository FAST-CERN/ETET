#include "main.h"


/**
* @brief Initialize TIM1
*/
void TIM1_INIT(void)
{ 
	   /*Primary Settings*/ 
	   TIM_TimeBaseInitTypeDef  TIM_StructInit;
	  
	   //Clock Source
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	   //BASE Struct Def
		 TIM_TimeBaseStructInit(&TIM_StructInit);
     TIM_StructInit.TIM_Period    = 0xFFFF;              
     TIM_StructInit.TIM_Prescaler = 0x0000;
     TIM_StructInit.TIM_ClockDivision = TIM_CKD_DIV1;    
     TIM_StructInit.TIM_CounterMode   = TIM_CounterMode_Up;
     TIM_StructInit.TIM_RepetitionCounter = 0;
     TIM_TimeBaseInit(TIM1, &TIM_StructInit);
			 
		 /*Encoder Mode Config*/
	   TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI1, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	   TIM_SetCounter(TIM1, 0);  
	
	   /*TIM1 Enable*/
		 TIM_Cmd(TIM1, ENABLE);
}


/**
* @brief Initialize TIM2
*/
void TIM2_INIT(void)
{	 
	   /*Primary Settings*/ 
	   TIM_TimeBaseInitTypeDef  TIM_StructInit;
     TIM_OCInitTypeDef        TIM_OCInitStructure;
	  
	   //Clock Source
	   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	   //BASE Struct Def
		 TIM_TimeBaseStructInit(&TIM_StructInit);
     TIM_StructInit.TIM_Period    = 9600-1;               //96M/9600 = 10kHz
     TIM_StructInit.TIM_Prescaler = 0x0000;
     TIM_StructInit.TIM_ClockDivision = TIM_CKD_DIV1;     //96MHz
     TIM_StructInit.TIM_CounterMode   = TIM_CounterMode_Up;
     TIM_StructInit.TIM_RepetitionCounter = 0;
     TIM_TimeBaseInit(TIM2, &TIM_StructInit);
	
	   /*BDTR Config :Brake & Deadtime */
	   TIM_BDTRInitTypeDef TIM_BDTRInitStruct;
	 
	   TIM_BDTRInitStruct.TIM_OSSRState = TIM_OSSRState_Enable;
		 TIM_BDTRInitStruct.TIM_OSSIState = TIM_OSSIState_Enable;
		 TIM_BDTRInitStruct.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
		 TIM_BDTRInitStruct.TIM_DeadTime  = 0x5;
		 TIM_BDTRInitStruct.TIM_Break = TIM_Break_Disable;  
		 TIM_BDTRInitStruct.TIM_BreakPolarity = TIM_BreakPolarity_High;
		 TIM_BDTRInitStruct.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
		 TIM_BDTRConfig(TIM2, &TIM_BDTRInitStruct);
	
	   /*Output Config*/
	   //OC Struct Def
		 TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;
		 TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;
		 TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
		 TIM_OCInitStructure.TIM_Pulse        = 1000;                        //duty
		 TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;
		 TIM_OCInitStructure.TIM_OCNPolarity  = TIM_OCNPolarity_High;
		 TIM_OCInitStructure.TIM_OCIdleState  = TIM_OCIdleState_Set;
		 TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
		 TIM_OC1Init(TIM2, &TIM_OCInitStructure);
		 TIM_OC3Init(TIM2, &TIM_OCInitStructure);
		 
		 TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_Low;
		 TIM_OC2Init(TIM2, &TIM_OCInitStructure);
		 TIM_OC4Init(TIM2, &TIM_OCInitStructure);
		 
		 //Preload Enable
		 TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
		 TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
		 TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
		 TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
		 
	   //ARR Preload Register
		 TIM_ARRPreloadConfig(TIM2, ENABLE);
		 
	   //PWM Out Enable
     TIM_CtrlPWMOutputs(TIM2, ENABLE);		 

	   /*Interrput Config*/		 
	   //CC3\4 IRQ EN
		 TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE); 
		 TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
		 TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE); 
		 TIM_ITConfig(TIM2, TIM_IT_CC4, ENABLE);
			 
	   //NVIC Config
		 NVIC_InitTypeDef NVIC_InitStructure;
     NVIC_InitStructure.NVIC_IRQChannel         = TIM2_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
	   
	   /*TIM2 Enable*/
		 TIM_Cmd(TIM2, ENABLE);
}	
	

/**
* @brief Initialize TIM3
*/
void TIM3_INIT(void)
{	   
	   /*GPIO Config*/
	   CAM_PLCK_GPIO_INIT();

     /*Primary Settings*/ 
	   TIM_TimeBaseInitTypeDef TIM_StructInit;
	  
	   //Clock Source
	   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	   //BASE Struct Def
     TIM_StructInit.TIM_Period            = 0xFFFF;      
     TIM_StructInit.TIM_Prescaler         = 0x0000;
     TIM_StructInit.TIM_ClockDivision     = TIM_CKD_DIV1;
     TIM_StructInit.TIM_CounterMode       = TIM_CounterMode_Up;
     TIM_StructInit.TIM_RepetitionCounter = 0;
     TIM_TimeBaseInit(TIM3, &TIM_StructInit);
  
//	   /*Encoder Mode Config*/
//	   TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI1, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
//	 
	   /*ETR Config*/
		 TIM_ETRClockMode1Config(TIM3, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_Inverted, 0x00);
		 TIM_SelectInputTrigger(TIM3, TIM_TS_ETRF);
		 TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Disable);
	  
	   /*TIM3 & it's DMA Enable*/
		 TIM_Cmd(TIM3, ENABLE);
		 TIM_SetCounter(TIM3, 0);
		 TIM_DMACmd(TIM3, TIM_DMA_Trigger, ENABLE);
}

/**
* @brief Initialize TIM8
*/
void TIM8_INIT(void)
{	  
	   //Clock Source
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
	   /*Primary Settings*/ 
	   TIM_TimeBaseInitTypeDef TIM_StructInit;
	
	   //BASE Struct Def
     TIM_StructInit.TIM_Period            = 0xFFFF;      
     TIM_StructInit.TIM_Prescaler         = 0x0000;
     TIM_StructInit.TIM_ClockDivision     = TIM_CKD_DIV1;
     TIM_StructInit.TIM_CounterMode       = TIM_CounterMode_Up;
     TIM_StructInit.TIM_RepetitionCounter = 0;
     TIM_TimeBaseInit(TIM8, &TIM_StructInit);
	
	   /*Encoder Mode Config*/
	   TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI1, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	   TIM_SetCounter(TIM8, 0);  
	
	   TIM_Cmd(TIM8, ENABLE);
}


