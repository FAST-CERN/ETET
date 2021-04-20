#include "main.h"

/*
The Function Initializes Peripheral SPI1
*/
void SPI1_INIT(void)
{
     /*SPI1 Clock Enable*/
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	   /*SPI1 GPIO Config Init*/
	   GPIO_InitTypeDef GPIO_InitStruct;
	   
	   //AF Config
	   GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_5);
	   GPIO_PinAFConfig(GPIOD, GPIO_PinSource3, GPIO_AF_5);
	   GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_1);
	   GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_1);
	
	   //GPIO InitStruct Def
	   GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
     GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	   GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_5;
	   GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
	   GPIO_Init(GPIOD, &GPIO_InitStruct);
	
   	 /*SPI1 InitStruct Def*/
		 SPI_InitTypeDef SPI_InitStruct;

     SPI_InitStruct.SPI_Mode      = SPI_Mode_Master;
		 SPI_InitStruct.SPI_DataSize  = SPI_DataSize_8b;
		 SPI_InitStruct.SPI_DataWidth = SPI_DataWidth_8b;
		 SPI_InitStruct.SPI_CPOL      = SPI_CPOL_Low;
		 SPI_InitStruct.SPI_CPHA      = SPI_CPHA_1Edge;
		 SPI_InitStruct.SPI_NSS       = SPI_NSS_Soft;
		 SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
		 SPI_InitStruct.SPI_FirstBit  = SPI_FirstBit_MSB;
		 
		 SPI_Init(SPI1, &SPI_InitStruct);
		 
		 /*ENABLE PERIPH SPI1*/
		 SPI_Cmd(SPI1, ENABLE);
		 
		 /*Enable Transmit/Receive Function*/
		 SPI_BiDirectionalLineConfig(SPI1, SPI_Direction_Tx);
		 SPI_BiDirectionalLineConfig(SPI1, SPI_Direction_Rx);
}

/*
RESET The CS Line OF SPI1
*/
void SPI1_M_CSLow(void)
{
     SPI_CSInternalSelected(SPI1, SPI_CS_BIT0, ENABLE);
}

/*
SET The CS Line OF SPI1
*/
void SPI1_M_CSHigh(void)
{
     SPI_CSInternalSelected(SPI1, SPI_CS_BIT0, DISABLE);
}

/*
SPI1 Master Write and Read a Byte
*/
uint32_t SPI1_M_ReadWrite_Byte(uint8_t Tx_Data)
{
	      static uint16_t temp;
	      static uint8_t  count;
	   
        SPI_SendData(SPI1, Tx_Data);
	      while((!SPI_GetFlagStatus(SPI1, SPI_FLAG_TXEPT)) || (!SPI_GetFlagStatus(SPI1, SPI_FLAG_RXAVL)))
				{
				      temp++;
				      if(temp > 10)
							{
							    SPI_SendData(SPI1, Tx_Data);
								  count++;
								  if(count >5)
									{
									   count = 0;
										 return 0;
									}
								  temp = 0;
							}
				}
				
				temp  = 0;
				count = 0;
	      return SPI_ReceiveData(SPI1);
}

/*
The Function Initializes Peripheral SPI2
*/
void SPI2_INIT(void)
{
     /*SPI2 Clock Enable*/
	   RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
	   /*SPI2 GPIO Config Init*/
	   GPIO_InitTypeDef GPIO_InitStruct;
	   
	   //AF Config
	   GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_5);
	   GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_5);

	   //GPIO InitStruct Def
	   GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
     GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	   GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_11 | GPIO_Pin_12;
	   GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
	   GPIO_Init(GPIOC, &GPIO_InitStruct);
	
   	 /*SPI2 InitStruct Def*/
		 SPI_InitTypeDef SPI_InitStruct;

     SPI_InitStruct.SPI_Mode      = SPI_Mode_Master;
		 SPI_InitStruct.SPI_DataSize  = SPI_DataSize_8b;
		 SPI_InitStruct.SPI_DataWidth = SPI_DataWidth_8b;
		 SPI_InitStruct.SPI_CPOL      = SPI_CPOL_Low;
		 SPI_InitStruct.SPI_CPHA      = SPI_CPHA_1Edge;
		 SPI_InitStruct.SPI_NSS       = SPI_NSS_Soft;
		 SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
		 SPI_InitStruct.SPI_FirstBit  = SPI_FirstBit_MSB;
		 
		 SPI_Init(SPI2, &SPI_InitStruct);
		 
		 /*ENABLE PERIPH SPI2*/
		 SPI_Cmd(SPI2, ENABLE);
		 
		 /*Enable Transmit/Receive Function*/
		 SPI_BiDirectionalLineConfig(SPI2, SPI_Direction_Tx);
		 SPI_BiDirectionalLineConfig(SPI1, SPI_Direction_Rx);
}

/*
RESET The CS Line of SPI2
*/
void SPI2_CSLow(void)
{
     GPIO_ResetBits(GPIOC, GPIO_Pin_15);     
}

/*
SET The CS Line of SPI2
*/
void SPI2_CSHigh(void)
{
     GPIO_SetBits(GPIOC, GPIO_Pin_15);
}

/*
RESET The DC Line of SPI2
*/
void SPI2_DCLow(void)
{
     GPIO_ResetBits(GPIOC, GPIO_Pin_14);
}

/*
SET The DC Line of SPI2
*/
void SPI2_DCHigh(void)
{
     GPIO_SetBits(GPIOC, GPIO_Pin_14);
}

/*
RESET The RST Line of SPI2
*/
void SPI2_RSTLow(void)
{
     GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}

/*
SET The RST Line of SPI2
*/
void SPI2_RSTHigh(void)
{
     GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

/*
SPI2 Master Write and Read a Byte
*/
void SPI2_Write_Byte(uint8_t Tx_Data)
{
        SPI_SendData(SPI2, Tx_Data);
	      while(!SPI_GetFlagStatus(SPI2, SPI_FLAG_TXEPT));
}

