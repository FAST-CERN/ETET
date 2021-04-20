#include "main.h"

/*Private Variables*/
KEY_BASE  KEY_STAT;
//LED_STAT  LED1_STAT;
//uint8_t   TSKH_FLAG = 0;

/*External Variables*/
extern uint8_t CAM_Finish_Flag;
extern uint8_t CAM_IMGbuf[IMG_H][IMG_W];
extern float angle_result;
extern int16_t  ENCODER_CNT_L;
extern uint16_t  M_DUTY_L;
extern int16_t Balance_PWM;
extern int16_t ICM_GYR_Y;

int main (void)
{ 
	  /*System Initialization*/	//系统初始化
    RCC_INIT();
	  
	  /*Peripherals Initialization*/ 	//固件初始化
	  GPIO_INIT();
	  LED_INIT();
	  BUZ_INIT();
	  KEY_Config();
	  UART1_INIT();
	  UART2_INIT();
	  SPI1_INIT();
	  SPI2_INIT();
	  
	  /*Timers Initialization*/		//定时器初始化
  	SYSTICK_INIT();
	  TIM1_INIT();
	  TIM2_INIT();
	  TIM8_INIT();
	  
	  /*External Modules Init*/		//外部模块初始化
	  ICM_INIT();
	  LCD_INIT();
		CAM_INIT();
		ENCODER_INIT();
	  MOTOR_OUT_INIT();
	   
	  while(1)
		{
					if(CAM_Finish_Flag)
					{
					   LCD_DISP_CAMIMG(CAM_IMGbuf,IMG_H,IMG_W);
						 CAM_Finish_Flag = 0;
					}	
/*************************************************/
ICM_GETDATA_ACC();
ICM_GETDATA_GYR();
ICM_ANGLE();
LCD_DISP_FLOAT(120,100,angle_result,4,0);
LCD_DISP_FLOAT(120,180,Balance_PWM,4,0);
LCD_DISP_FLOAT(120,160,M_DUTY_L,4,0);
LCD_DISP_FLOAT(120,140,ICM_GYR_Y,4,0);
/****************************************************/					
		}
		
}
