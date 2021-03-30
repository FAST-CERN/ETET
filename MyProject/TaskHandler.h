#ifndef _TASKHANDLER_H_
#define _TASKHANDLER_H_


#include "HAL_device.h"

void TaskHandler(void);

void TSKH_1ms_Serv(void);
void TSKH_5ms_Serv(void);
void TSKH_10ms_Serv(void);
void TSKH_20ms_Serv(void);
void TSKH_50ms_Serv(void);
void TSKH_100ms_Serv(void);
void TSKH_500ms_Serv(void);

#endif
