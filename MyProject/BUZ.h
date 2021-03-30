#ifndef _BUZ_H_
#define _BUZ_H_

#include "HAL_device.h"

/*variables*/
typedef enum
{
    BUZ_OFF = 0,
	  BUZ_ON  = 1
}BUZ_STAT;

/*macros*/
#define BUZ_PORT GPIOA
#define BUZ_PIN  GPIO_Pin_15

/*directions*/
#define BUZ_ON()  GPIOA->BRR  = GPIO_Pin_15
#define BUZ_OFF() GPIOA->BSRR = GPIO_Pin_15

/*functions*/
BUZ_STAT BUZ_INIT(void);
BUZ_STAT BUZ_SET(BUZ_STAT);
BUZ_STAT BUZ_TOGGLE(void);

#endif

