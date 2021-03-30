#include "main.h"

/**
* @brief  Intialize LED port
* @param  NULL
* @retval 
*/
LED_STAT LED_INIT(void)
{
     GPIO_InitTypeDef  GPIO_InitStructure;
	   
	   GPIO_InitStructure.GPIO_Pin   = LED1_Pin;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ; 
	   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP ;
	   
	   GPIO_Init(LED1_Port, &GPIO_InitStructure);     //LED1 Config
	
	   LED1_ON();
	   return LED_ON;
}

/**
* @brief 
*/
LED_STAT LED1_Toggle(void)
{
    if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4))
		{
		   GPIOA -> BSRR = GPIO_Pin_4;
			 return LED_OFF;
		}
		else
		{
		   GPIOA -> BRR = GPIO_Pin_4;
		   return LED_ON;
		}    
}

/**
* @brief 
*/
LED_STAT LED1_SET(LED_STAT newstat)
{
	  if(newstat != LED_ON)
		{
		   GPIOA->BSRR  = GPIO_Pin_4;
		}			
		else
		{
		   GPIOA->BRR = GPIO_Pin_4;
		}
    
    return newstat;
}
