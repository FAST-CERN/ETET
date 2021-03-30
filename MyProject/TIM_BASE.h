#ifndef _TIM_BASE_H_
#define _TIM_BASE_H_


#include "HAL_device.h"
#include "HAL_conf.h"

void SYSTICK_INIT(void);
void Delay_ms(uint32_t);
void Decre_Delay_ms(void);

//void delay_ms(uint32_t);
//void delay_us(uint32_t);
#endif
