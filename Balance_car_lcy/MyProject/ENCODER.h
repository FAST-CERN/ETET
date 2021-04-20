#ifndef _ENCODER_H_
#define _ENCODER_H_


#include "HAL_device.h"

void ENCODER_INIT(void);

int16_t ENCODER_GET_CNT_L(void);
int16_t ENCODER_GET_CNT_R(void);
 
#endif


