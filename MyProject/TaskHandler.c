#include "main.h"

uint8_t TSKH_1ms_LOOP   = 0x00;
uint8_t TSKH_5ms_LOOP   = 0x00;
uint8_t TSKH_10ms_LOOP  = 0x00;
uint8_t TSKH_20ms_LOOP  = 0x00;
uint8_t TSKH_50ms_LOOP  = 0x00;
uint8_t TSKH_100ms_LOOP = 0x00;
uint8_t TSKH_500ms_LOOP = 0x00;

uint8_t TSKH_1ms_FLAG   = 0x00;
uint8_t TSKH_5ms_FLAG   = 0x00;
uint8_t TSKH_10ms_FLAG  = 0x00;
uint8_t TSKH_20ms_FLAG  = 0x00;
uint8_t TSKH_50ms_FLAG  = 0x00;
uint8_t TSKH_100ms_FLAG = 0x00;
uint8_t TSKH_500ms_FLAG = 0x00;

/*
The Function which Handles Primary Tasks
*/
void TaskHandler(void)
{
	   TSKH_1ms_LOOP++;
	
	   if(TSKH_1ms_LOOP == 1)
		 {
		    TSKH_1ms_LOOP = 0x00;
			  TSKH_5ms_LOOP ++;
			  TSKH_1ms_FLAG = 0x01;
			 
			  TSKH_1ms_Serv();
			  
			  TSKH_1ms_FLAG = 0x00;
		 }
	   
		 if(TSKH_5ms_LOOP == 5)
		 {
		 		TSKH_5ms_LOOP = 0x00;
			  TSKH_10ms_LOOP ++;
			  TSKH_5ms_FLAG = 0x01;
			 
			  TSKH_5ms_Serv();
			  
			  TSKH_5ms_FLAG = 0x00;
		 }
		 
		 if(TSKH_10ms_LOOP == 2)
		 {
		 		TSKH_10ms_LOOP = 0x00;
			  TSKH_20ms_LOOP ++;
			  TSKH_50ms_LOOP ++;
			  TSKH_10ms_FLAG = 0x01;
			 
			  TSKH_10ms_Serv();
			  
			  TSKH_10ms_FLAG = 0x00;
		 }
		 
		 if(TSKH_20ms_LOOP == 2)
		 {
		 		TSKH_20ms_LOOP = 0x00;
			  TSKH_20ms_FLAG = 0x01;
			 
			  TSKH_20ms_Serv();
			  
			  TSKH_20ms_FLAG = 0x00;
		 }
		 
		 if(TSKH_50ms_LOOP == 5)
		 {
		 		TSKH_50ms_LOOP = 0x00;
			  TSKH_100ms_LOOP ++;
			  TSKH_50ms_FLAG = 0x01;
			 
			  TSKH_50ms_Serv();
			  
			  TSKH_50ms_FLAG = 0x00;
		 }
		 
		 if(TSKH_100ms_LOOP == 2)
		 {
		 		TSKH_100ms_LOOP = 0x00;
			  TSKH_500ms_LOOP ++;
			  TSKH_100ms_FLAG = 0x01;
			 
			  TSKH_100ms_Serv();
			  
			  TSKH_100ms_FLAG = 0x00;
		 }
		 
		 if(TSKH_500ms_LOOP == 5)
		 {
		 		TSKH_500ms_LOOP = 0x00;
			  TSKH_500ms_FLAG = 0x01;
			 
			  TSKH_500ms_Serv();
			  
			  TSKH_500ms_FLAG = 0x00;
		 }		 
}

/*
The Function which Handles 1ms Tasks
*/
void TSKH_1ms_Serv(void)
{

}

/*
The Function which Handles 5ms Tasks
*/
void TSKH_5ms_Serv(void)
{
     
}

/*
The Function which Handles 10ms Tasks
*/
void TSKH_10ms_Serv(void)
{
     KEY_SCAN();
	   KEY_Reader();
}

/*
The Function which Handles 20ms Tasks
*/
void TSKH_20ms_Serv(void)
{
     
}

/*
The Function which Handles 50ms Tasks
*/
void TSKH_50ms_Serv(void)
{
     
}

/*
The Function which Handles 100ms Tasks
*/
void TSKH_100ms_Serv(void)
{
     
}

/*
The Function which Handles 500ms Tasks
*/
void TSKH_500ms_Serv(void)
{
     
}
