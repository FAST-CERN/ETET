#include "main.h"

/*-------------------Extern Variables---------------------------*/
extern uint8_t   UART2_RxCnt;
extern char      UART2_RxDataBuff[3];
extern char*     UART2_RxP;

/*-------------------Private Variables--------------------------*/
uint8_t CAM_IMGbuf[IMG_H][IMG_W];
uint8_t *CAM_BufADDR;

uint8_t CAM_RxFlag;
uint8_t CAM_Finish_Flag = 0;

//Camera Config Struct
int16_t CAM_CFG[CONFIG_FINISH][2]=
{
	{AUTO_EXP,			0},									// 自动曝光设置		范围1-63 0为关闭 如果自动曝光开启  EXP_TIME命令设置的数据将会变为最大曝光时间，也就是自动曝光时间的上限
																			// 一般情况是不需要开启这个功能，因为比赛场地光线一般都比较均匀，如果遇到光线非常不均匀的情况可以尝试设置该值，增加图像稳定性
	{EXP_TIME,			450},								// 曝光时间			摄像头收到后会自动计算出最大曝光时间，如果设置过大则设置为计算出来的最大曝光值
	{FPS,				    50},								// 图像帧率			摄像头收到后会自动计算出最大FPS，如果过大则设置为计算出来的最大FPS
	{SET_COL,			  IMG_W},						  // 图像列数量		范围1-752     
	{SET_ROW,			  IMG_H},						  // 图像行数量		范围1-480
	{LR_OFFSET,			0},									// 图像左右偏移量	正值 右偏移   负值 左偏移  列为188 376 752时无法设置偏移    摄像头收偏移数据后会自动计算最大偏移，如果超出则设置计算出来的最大偏移
	{UD_OFFSET,			0},									// 图像上下偏移量	正值 上偏移   负值 下偏移  行为120 240 480时无法设置偏移    摄像头收偏移数据后会自动计算最大偏移，如果超出则设置计算出来的最大偏移
	{GAIN,				  32},								// 图像增益			范围16-64     增益可以在曝光时间固定的情况下改变图像亮暗程度
	{INIT,				  0}									// 摄像头开始初始化
};

//Config Info of Camera Get form UART2
int16_t GET_CFG[CONFIG_FINISH-1][2]=
{
	{AUTO_EXP,			0},									// 自动曝光设置
	{EXP_TIME,			0},									// 曝光时间
	{FPS,				    0},									// 图像帧率
	{SET_COL,			  0},								  // 图像列数量
	{SET_ROW,			  0},									// 图像行数量
	{LR_OFFSET,			0},									// 图像左右偏移量
	{UD_OFFSET,			0},									// 图像上下偏移量
	{GAIN,				  0},									// 图像增益
};


/**
* @brief : Initialize the MT9V034 Camera 
*/
void CAM_INIT(void)
{
     CAM_BufADDR = CAM_IMGbuf[0];
	  
	   Delay_ms(300);
	
	   CAM_RxFlag = 0;
	   CAM_GET_CfgInfo(GET_CFG);        //Get Config Info
	   
	   CAM_RxFlag = 0;	   
	   CAM_SET_Cfg(CAM_CFG);            //Config
	
	   CAM_RxFlag = 0;
	   CAM_GET_CfgInfo(GET_CFG);        //Get Config Info
	 
	   DMA1_INIT();                     //DMA Init
	   TIM3_INIT();
	   EXTI_INIT();
}


/**
* @brief : get configuration information of MT9V034 Camera 
*/
void CAM_GET_CfgInfo(int16_t BUFF[CONFIG_FINISH-1][2])
{
     uint16_t  temp, i, j;
	   uint8_t   Tx_Buff[4];
		
	   for(i = 0; i<CONFIG_FINISH-1; i++)
		 {
		     Tx_Buff[0] = 0xA5;
			   Tx_Buff[1] = GET_STATUS;
			   temp = BUFF[i][0];
			   Tx_Buff[2] = temp>>8;
			   Tx_Buff[3] = (uint8_t)temp;
			 
			   for(j = 0; j<4; j++)  
         {			
				     UART2_Send_Byte(Tx_Buff[j]);
         }
				 
         while(!CAM_RxFlag);
				 CAM_RxFlag = 0;
				 
				 BUFF[i][1] = (UART2_RxDataBuff[1]<<8)|(UART2_RxDataBuff[2]);
		 }
}

/**
* @brief : set the config of MT9V034 Camera 
*/
void CAM_SET_Cfg(int16_t BUFF[CONFIG_FINISH-1][2])
{
     uint16_t temp, i, j;
	   uint8_t  Tx_Buff[4];

     CAM_RxFlag = 0;
	
	   for(i = 0; i<CONFIG_FINISH; i++)
     {
		     Tx_Buff[0] = 0xA5;
			   Tx_Buff[1] = BUFF[i][0];
			 
			   temp = BUFF[i][1];
			 
			   Tx_Buff[2] = temp>>8;
			   Tx_Buff[3] = (uint8_t)temp;
			 
			   for(j = 0; j<4; j++)
			   {
				     UART2_Send_Byte(Tx_Buff[j]);
				 }
				 Delay_ms(2);
		 }
	
		 while(!CAM_RxFlag);
		 CAM_RxFlag = 0;
		 
		 while((UART2_RxDataBuff[1] != 0xFF) || (UART2_RxDataBuff[2] != 0xFF));
}

/**
* @brief Initialize GPIO Function of DMA1 Channel MT9V034
*/
void CAM_DMA1_GPIO_INIT(void)
{
     //GPIO INIT
	   GPIO_InitTypeDef  GPIO_InitStructure;
	   
	   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 |
                                     GPIO_Pin_1 |
                                     GPIO_Pin_2 |
                                     GPIO_Pin_3 |
                                     GPIO_Pin_4 |
                                     GPIO_Pin_5 |
                                     GPIO_Pin_6 |
                                     GPIO_Pin_7;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ; 
	   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING ;
	   
	   GPIO_Init(GPIOB, &GPIO_InitStructure); 
}

/**
* @brief Initialize PCLK of MT9V034
*/
void CAM_PLCK_GPIO_INIT(void)
{ 
     /*GPIO Config*/
	   GPIO_InitTypeDef  GPIO_InitStructure;
	
	   //AF Config
	   GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_1);
	
	   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	
	   GPIO_Init(GPIOD, &GPIO_InitStructure);
}


/**
* @brief Initialize VSYNC of MT9V034
*/
void CAM_VSYNC_GPIO_INIT(void)
{
     /*GPIO Config*/
	   GPIO_InitTypeDef  GPIO_InitStructure;
	
	   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	
	   GPIO_Init(GPIOD, &GPIO_InitStructure);
}


/**
* @brief Process VSYNC Signal
*/
void CAM_VSYNC_ITCallback(void)
{
     DMA1_Channel4 ->CNDTR  =  IMG_H*IMG_W;
	   DMA1_Channel4 ->CCR   |=  0x01;
}


/**
* @brief GET Firmware Number 
*/
uint16_t CAM_GET_FWVersion(void)
{
     uint16_t  temp;
     uint8_t   Tx_Buff[4];
     uint8_t   i = 0;	
	  
	   Tx_Buff[0] = 0xA5;
	   Tx_Buff[1] = GET_STATUS;
	   
	   temp = GET_VERSION;
	
	   Tx_Buff[2] = temp>>8;
	   Tx_Buff[3] = (uint8_t)temp;
	
	   for(; i<4; i++)
	   {
		     UART2_Send_Byte(Tx_Buff[i]);
		 }

		 while(!CAM_RxFlag);  
		 CAM_RxFlag = 0;
		 
     return ((uint16_t)(UART2_RxDataBuff[1] << 8) | (uint16_t)UART2_RxDataBuff[2]);
}


/**
* @brief SET Exposure Time 
*/
uint16_t CAM_SET_ExpTIM(uint16_t level)
{
     uint16_t  temp;
     uint8_t   Tx_Buff[4];
     uint8_t   i = 0;	
	  
	   Tx_Buff[0] = 0xA5;
	   Tx_Buff[1] = SET_EXP_TIME;
	   
	   temp = level;
	
	   Tx_Buff[2] = temp>>8;
	   Tx_Buff[3] = (uint8_t)temp;
	
	   for(; i<4; i++)
	   {
		     UART2_Send_Byte(Tx_Buff[i]);
		 }

		 while(!CAM_RxFlag);  
		 CAM_RxFlag = 0;
		 
     return ((uint16_t)(UART2_RxDataBuff[1] << 8) | (uint16_t)UART2_RxDataBuff[2]);
}


/**
* @brief Write Register 
*/
uint16_t CAM_WR_REG(uint16_t addr, uint16_t dat)
{
     uint16_t temp;
	   uint8_t  Tx_Buff[4];
	   uint8_t  i;
	
	   Tx_Buff[0] = 0xA5;
	   Tx_Buff[1] = SET_ADDR;
	   temp = addr;
	   Tx_Buff[2] = temp >> 8;
	   Tx_Buff[3] = (uint8_t)temp;
	
	   for(i = 0; i<4; i++)
		 {
		     UART2_Send_Byte(Tx_Buff[i]);
		 }
		 Delay_ms(10);
	
	   Tx_Buff[0] = 0xA5;
	   Tx_Buff[1] = SET_DATA;
	   temp = dat;
	   Tx_Buff[2] = temp >> 8;
	   Tx_Buff[3] = (uint8_t)temp;
		 
		 for(i = 0; i<4; i++)
		 {
		     UART2_Send_Byte(Tx_Buff[i]);
		 }
		 
		 while(!CAM_RxFlag);
		 CAM_RxFlag = 0;
		 
	   temp = (uint16_t)UART2_RxDataBuff[1]<<8 | (uint16_t)UART2_RxDataBuff[2];
	   return temp;
}
