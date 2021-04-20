#ifndef _LCD_H_
#define _LCD_H_

#include "HAL_Device.h"

/***************Macro Group*********************/
#define LCD_RST_LOW()    GPIOC->BRR  = GPIO_Pin_13
#define LCD_RST_HIGH()   GPIOC->BSRR = GPIO_Pin_13
#define LCD_DC_LOW()     GPIOC->BRR  = GPIO_Pin_14
#define LCD_DC_HIGH()    GPIOC->BSRR = GPIO_Pin_14
#define LCD_CS_LOW()     GPIOC->BRR  = GPIO_Pin_15
#define LCD_CS_HIGH()    GPIOC->BSRR = GPIO_Pin_15

#define LCD_COM_NOP()    LCD_WR_COMMAND(0x00)
/*Colour Group*/
#define RED					0xF800													
#define BLUE				0x001F													
#define YELLOW		  0xFFE0													
#define GREEN				0x07E0													
#define WHITE				0xFFFF													
#define BLACK				0x0000													
#define GRAY				0X8430													
#define BROWN				0XBC40													
#define PURPLE			0XF81F												
#define PINK				0XFE19

#define LCD_Hight   135
#define LCD_Width   240

#define LCD_BGC     WHITE
#define LCD_TXC     BLACK

/*Function Group*/
void LCD_INIT(void);
void LCD_RESET(void);
void LCD_FILL(uint16_t);
void LCD_SET_REGION(uint16_t,uint16_t,uint16_t,uint16_t);
void LCD_DISP_DOT(uint16_t,uint16_t,uint16_t);
void LCD_DISP_CHAR(uint16_t,uint16_t,char);
void LCD_DISP_STR(uint16_t,uint16_t,const char []);
void LCD_DISP_UINT8(uint16_t,uint16_t,uint8_t);
void LCD_DISP_INT8(uint16_t,uint16_t,int8_t);
void LCD_DISP_UINT16(uint16_t,uint16_t,uint16_t);
void LCD_DISP_INT16(uint16_t,uint16_t,int16_t);
void LCD_DISP_INT32(uint16_t,uint16_t,int32_t);
void LCD_DISP_FLOAT(uint16_t,uint16_t,double,uint8_t,uint8_t);
void LCD_DISP_CAMIMG(uint8_t [50][188],uint16_t,uint16_t);
void LCD_DISP_RGBIMG(unsigned char*,uint16_t,uint16_t,uint16_t,uint16_t);

void LCD_WR_COMMAND(uint8_t);
void LCD_WR_DATA(uint8_t);
void LCD_WR_DATA_16b(uint16_t);




#endif
