#ifndef _CAM_H_
#define _CAM_H_

#include "HAL_device.h"

/*Variable Group*/
//Camera Commands
typedef enum
{
				INIT = 0,													// Camera INIT
				AUTO_EXP,													// Auto Exposure
				EXP_TIME,													// Exposure time
				FPS,															// Frame rate
				SET_COL,													// Image Column
				SET_ROW,													// Image Row
				LR_OFFSET,												// Image offset-Left/Right
				UD_OFFSET,												// Image offset-Up/Dowm
				GAIN,															// Image offset
				CONFIG_FINISH,										// Nop
				COLOR_GET_WHO_AM_I = 0xEF,        // Who am I? 
				SET_EXP_TIME = 0XF0,							// (ID)Set Exposure time 
				GET_STATUS,												// Get Config Info
				GET_VERSION,											// Firmware Version
				SET_ADDR = 0XFE,									// Register Address
				SET_DATA													// Register Data
}CAM_CMD;


/*Macro Group*/
#define IMG_H  50
#define IMG_W  188


/*Function Group*/
void CAM_INIT(void);
void CAM_DMA1_GPIO_INIT(void);
void CAM_PLCK_GPIO_INIT(void);
void CAM_VSYNC_GPIO_INIT(void);
void CAM_VSYNC_ITCallback(void);
void CAM_GET_CfgInfo(int16_t [CONFIG_FINISH-1][2]);
void CAM_SET_Cfg(int16_t [CONFIG_FINISH-1][2]);

uint16_t CAM_GET_FWVersion(void);
uint16_t CAM_SET_ExpTIM(uint16_t);
uint16_t CAM_WR_REG(uint16_t,uint16_t);

#endif
