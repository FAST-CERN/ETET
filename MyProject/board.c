#include "main.h"

/*
  RCC Module Initialization
*/
void RCC_INIT(void)
{
     RCC_DeInit();	
	
	   //HSE Config
	   RCC_HSEConfig(RCC_HSE_ON);      //HSE:8MHz
	   RCC_WaitForHSEStartUp();
	
	   //PLL Config
	   RCC_PLLCmd(DISABLE);
     while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != RESET);
	   
	   RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_12);
	   
	   RCC_PLLCmd(ENABLE);		 
     while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET); 
		 
		 //SYSCLK Configuration
		 RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	   while(RCC_GetSYSCLKSource() != 0x08);         //Source:PLL  Freq:96MHz
		 	
	   //AHB Config
	   RCC_HCLKConfig(RCC_SYSCLK_Div1);//8*12/1=96MHz
	
	   //APB1 Config
	   RCC_PCLK1Config(RCC_HCLK_Div1); //96/1=96MHz
	
	   //APB2 Config
	   RCC_PCLK2Config(RCC_HCLK_Div1); //96/1=96MHz
	   
		 //MCO Config
		 RCC_MCOConfig(RCC_MCO_PLLCLK_Div2);  //96/2=48MHz
		 
}


/*
  GPIO Module Initialization
*/
void GPIO_INIT(void)
{
     /*GPIO Clock Enable*/
	   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOD, ENABLE);	
	   /*SYSCGF Clock Enable*/
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);  //external interrupt for GPIO
}

