#ifndef _UART_H_
#define _UART_H_

#include "HAL_device.h"

void UART1_INIT(void);

void UART1_Send_Byte(uint8_t);
void UART1_Send_String(char*);
void UART1_IT_ReceiveDATA(void);

#endif
