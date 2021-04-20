#include "main.h"


uint16_t  M_DUTY_L = 4800;												//4400
uint16_t  M_DUTY_R = 4800;												//4400

/**
* @brief Initialize Motor Control Signal Output
*/
void MOTOR_OUT_INIT(void)
{
     /*GPIO Config*/
	   GPIO_InitTypeDef  GPIO_InitStructure;
	
	   //AF Config
	   GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_4);
	   GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_4);	 
	   GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_2);
	   GPIO_PinAFConfig(GPIOC, GPIO_PinSource9,  GPIO_AF_5);

	   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11 | 
	                                   GPIO_Pin_12 ;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	
	   GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	
	   GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		 GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	
	   GPIO_Init(GPIOC, &GPIO_InitStructure);
}



/**
*  @brief  set the duty of 2 motors
*/
void MOTOR_SET_DUTY(uint16_t left, uint16_t right)
{
     TIM2 -> CCR1 = left;
	   TIM2 -> CCR2 = left;
	
     TIM2 -> CCR3 = right;
	   TIM2 -> CCR4 = right;
}

