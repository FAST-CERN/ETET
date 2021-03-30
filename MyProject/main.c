#include "main.h"

/*Private Variables*/
KEY_BASE  KEY_STAT;
//LED_STAT  LED1_STAT;
char      UART1_RxDataBuff[100];
uint16_t  UART1_RxCounter = 0;

/*Private Pointers*/
char*     UART1_RxP = UART1_RxDataBuff;

int main (void)
{ 
	  /*System Initialization*/
    RCC_INIT();
	  
	  /*Peripherals Initialization*/ 
	  GPIO_INIT();
	  LED_INIT();
	  KEY_Config();
	  UART1_INIT();
	  SPI1_INIT();
	  
	  /*Timers Initialization*/
  	SYSTICK_INIT();
//	  TIM1_INIT();
	  
	  /*External Modules Init*/
//	  ICM_INIT();
//	  LCD_INIT();
	  
	  while(1)
		{

		}
		
}
