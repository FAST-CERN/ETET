#ifndef _LED_H_
#define _LED_H_

#include "HAL_device.h"

typedef enum 
{
    LED_OFF =0,
	  LED_ON  =1
}LED_STAT;

//macros
#define LED1_Port   GPIOA
#define LED1_Pin    GPIO_Pin_4

#define LED1_ON()   GPIOA->BRR  = GPIO_Pin_4; 
#define LED1_OFF()  GPIOA->BSRR = GPIO_Pin_4;


//functions
LED_STAT LED_INIT(void);
LED_STAT LED1_SET(LED_STAT);
LED_STAT LED1_Toggle(void);

#endif

