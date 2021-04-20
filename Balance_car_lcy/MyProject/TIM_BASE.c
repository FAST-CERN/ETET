#include "main.h"

uint16_t Delay_Qt_us = 0x0000;
uint32_t Delay_Qt_ms = 0x00000000;

/*
The Function which initializes system tick timer 

1ms IRQ
*/
void SYSTICK_INIT(void)
{
	   uint32_t pulse_ms ;
     uint32_t pulse_us ;
	
	   SysTick->CTRL &=  ~SysTick_CTRL_ENABLE_Msk ;
	  
	   SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);     //96MHz
 
	   pulse_us = SystemCoreClock /1000000;
     pulse_ms = (uint32_t)pulse_us *1000;

	   SysTick->VAL   =  pulse_ms - 1 ;
	   SysTick->LOAD  =  pulse_ms - 1 ;
	   SysTick->CTRL |=  SysTick_CTRL_TICKINT_Msk ;
	
	   SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk ;
	
	   NVIC_SetPriority(SysTick_IRQn, 0x0);
}

/*
Delay Function ms
*/ 
void Delay_ms(uint32_t quantity)
{
     Delay_Qt_ms = quantity;	
	   while(Delay_Qt_ms !=0);
}


/*
Decrement Function For Delay_ms
*/
void Decre_Delay_ms(void)
{
     if(Delay_Qt_ms != 0)
			  Delay_Qt_ms--;
}


//void delay_ms(uint32_t temp)
//{   
//	   uint32_t p;
//	   
//     if(temp>500)
//		 {
//			  delay_ms(temp-500);
//			  delay_ms(500);
//		 }
//		 else
//		 {
//				SysTick->VAL  = 0x00;
//				SysTick->LOAD = temp*pulse_ms - 1;
//			
//				SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
//				 
//				do
//				{
//						 p = SysTick->CTRL;
//				}
//				while((p & 0x01) && !(p & (1<<16)));
//			
//				SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

//				SysTick->VAL  = 0x00;

//		 }
//}

//void delay_us(uint32_t temp)
//{
//	   uint32_t p;
//	
//     SysTick->VAL  = 0x00;
//	   SysTick->LOAD = temp*pulse_us - 1;
//	
//	   SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
//	
//		 do
//		 {
//		     p = SysTick->CTRL;
//		 }
//	   while((p & 0x01) && !(p & (1<<16)));
//	
//	   SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

//     SysTick->VAL  = 0x00;
//}
