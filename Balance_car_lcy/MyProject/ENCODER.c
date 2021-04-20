#include "main.h"


/*Private Variables*/
int16_t  ENCODER_CNT_L = 0;
int16_t  ENCODER_CNT_R = 0;


/**
*  @brief initialize encoders
*/
void ENCODER_INIT(void)
{
     /*GPIO Config*/
	   GPIO_InitTypeDef  GPIO_InitStructure;
	
	   //AF Config
	   GPIO_PinAFConfig(GPIOC, GPIO_PinSource0, GPIO_AF_6);
	   GPIO_PinAFConfig(GPIOC, GPIO_PinSource1, GPIO_AF_6);
	   GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);
	   GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_3);
//	   GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_1);
//	   GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_1);
	
	   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 |
	                                   GPIO_Pin_1 ;
//		                                 GPIO_Pin_7 |
//	                                   GPIO_Pin_8;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	
	   GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
	   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 |
	                                   GPIO_Pin_8 ;
		 GPIO_Init(GPIOA, &GPIO_InitStructure);															 
}

int16_t ENCODER_GET_CNT_L(void)
{
     int16_t temp;
     
     temp	= TIM1 -> CNT;  
	   TIM_SetCounter(TIM1, 0);
  
	   return  temp;
}

int16_t ENCODER_GET_CNT_R(void)
{
     int16_t temp;
     
     temp	= TIM8 -> CNT;  
	   TIM_SetCounter(TIM8, 0);
  
	   return  temp;
}

