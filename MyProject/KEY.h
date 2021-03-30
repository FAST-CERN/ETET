#ifndef _KEY_H_
#define _KEY_H_  

#include "HAL_device.h"

typedef struct 
{
				uint8_t   Key_Read_SHORT;    
				uint8_t   Key_Read_LONG;    
				uint8_t   Key_Value;
				uint8_t   Key_LOOP_H;
				uint32_t  Key_LOOP_L;
				uint8_t   Key_Scan_Temp;
				uint8_t   Pre_Key_Value;
				uint8_t   Key_Valid_VAL;
}KEY_BASE;

/*Macros*/
#define  KEY_INIVAL  0x00

#define KEY1_PORT    GPIOB
#define KEY2_PORT    GPIOB
#define KEY3_PORT    GPIOB
#define KEY4_PORT    GPIOB
#define KEY5_PORT    GPIOC
#define KEY6_PORT    GPIOA

#define KEY1_PIN     GPIO_Pin_10
#define KEY2_PIN     GPIO_Pin_13
#define KEY3_PIN     GPIO_Pin_14
#define KEY4_PIN     GPIO_Pin_15
#define KEY5_PIN     GPIO_Pin_6
#define KEY6_PIN     GPIO_Pin_8

/*Functions*/
void KEY_Config(void);
void KEY_SCAN(void);
void KEY_Reader(void);
void KEY1_Server(void);
void KEY2_Server(void);
void KEY3_Server(void);
void KEY4_Server(void);
void KEY5_Server(void);
void KEY6_Server(void);
void KEY_TEST(void);

#endif
