#include "main.h"


/*Init the LCD Module*/
void LCD_INIT(void)
{

}

/*
Reset the LCD
*/
void LCD_RESET(void)
{
     SPI2_RSTHigh();
	   Delay_ms(50);
	   SPI2_RSTLow();
	   Delay_ms(50);
	   SPI2_RSTHigh();
	   Delay_ms(50);
}
