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
	{AUTO_EXP,			0},									// �Զ��ع�����		��Χ1-63 0Ϊ�ر� ����Զ��ع⿪��  EXP_TIME�������õ����ݽ����Ϊ����ع�ʱ�䣬Ҳ�����Զ��ع�ʱ�������
																			// һ������ǲ���Ҫ����������ܣ���Ϊ�������ع���һ�㶼�ȽϾ��ȣ�����������߷ǳ������ȵ�������Գ������ø�ֵ������ͼ���ȶ���
	{EXP_TIME,			450},								// �ع�ʱ��			����ͷ�յ�����Զ����������ع�ʱ�䣬������ù���������Ϊ�������������ع�ֵ
	{FPS,				    50},								// ͼ��֡��			����ͷ�յ�����Զ���������FPS���������������Ϊ������������FPS
	{SET_COL,			  IMG_W},						  // ͼ��������		��Χ1-752     
	{SET_ROW,			  IMG_H},						  // ͼ��������		��Χ1-480
	{LR_OFFSET,			0},									// ͼ������ƫ����	��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ188 376 752ʱ�޷�����ƫ��    ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
	{UD_OFFSET,			0},									// ͼ������ƫ����	��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ120 240 480ʱ�޷�����ƫ��    ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
	{GAIN,				  32},								// ͼ������			��Χ16-64     ����������ع�ʱ��̶�������¸ı�ͼ�������̶�
	{INIT,				  0}									// ����ͷ��ʼ��ʼ��
};

//Config Info of Camera Get form UART2
int16_t GET_CFG[CONFIG_FINISH-1][2]=
{
	{AUTO_EXP,			0},									// �Զ��ع�����
	{EXP_TIME,			0},									// �ع�ʱ��
	{FPS,				    0},									// ͼ��֡��
	{SET_COL,			  0},								  // ͼ��������
	{SET_ROW,			  0},									// ͼ��������
	{LR_OFFSET,			0},									// ͼ������ƫ����
	{UD_OFFSET,			0},									// ͼ������ƫ����
	{GAIN,				  0},									// ͼ������
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
