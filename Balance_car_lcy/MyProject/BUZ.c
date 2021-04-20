#include "main.h"

/**
* @brief BUZZER port Config
*/
BUZ_STAT BUZ_INIT(void)
{
     GPIO_InitTypeDef  GPIO_InitStructure;
	
	   GPIO_InitStructure.GPIO_Pin   =  BUZ_PIN;
	   GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_Out_PP;
	
	   GPIO_Init(BUZ_PORT, &GPIO_InitStructure);
	
	   BUZ_OFF();
	   return BUZ_OFF;
}

/**
* @brief BUZZER SET
*/
BUZ_STAT BUZ_SET(BUZ_STAT newstat)
{
     if(newstat != BUZ_ON)
		 {
			  BUZ_OFF();
		 }
		 else
		 {
		    BUZ_ON();
		 }
		 
		 return newstat;
}

/**
* @brief BUZZER TOGGLE
*/
BUZ_STAT BUZ_TOGGLE(void)
{
	   if(GPIO_ReadOutputDataBit(BUZ_PORT, BUZ_PIN))
     {
			 BUZ_OFF();
			 return BUZ_OFF;
		 }
     else
		 {
			 BUZ_ON();
		   return BUZ_ON;
		 }
}

