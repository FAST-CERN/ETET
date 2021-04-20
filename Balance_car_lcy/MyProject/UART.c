#include "main.h"

/*Private Variables*/
char      UART1_RxDataBuff[100];
uint8_t   UART1_RxAvalData = 0;
char      UART2_RxDataBuff[3];
uint8_t   UART2_RxCnt = 0;
char*     UART1_RxP   = UART1_RxDataBuff;
char*     UART2_RxP   = UART2_RxDataBuff;

/*External Variables*/
extern    uint8_t  CAM_RxFlag;

/*
The Function which initializes Peripheral UART1  
*/
void UART1_INIT(void)
{
	   /*APB2 Clock Enable*/
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1, ENABLE);
	  
     /*GPIO Config*/
	   GPIO_InitTypeDef GPIO_InitStruct;
	     
	   //AF Config
	   GPIO_PinAFConfig(GPIOA, GPIO_PinSource9 , GPIO_AF_1);
	   GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
	
		 //GPIO InitStructure Def
	   GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9;
	   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
     GPIO_Init(GPIOA, &GPIO_InitStruct);
	   
	   GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;
     GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	   GPIO_Init(GPIOA, &GPIO_InitStruct);
	  
     /*UART Config*/	 
	   UART_InitTypeDef UART_InitStruct;
	
	   //UART Initstruct Def
     UART_InitStruct.UART_BaudRate   = 9600;
     UART_InitStruct.UART_WordLength = UART_WordLength_8b;
     UART_InitStruct.UART_StopBits   = UART_StopBits_1;
     UART_InitStruct.UART_Parity     = UART_Parity_No;
     UART_InitStruct.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
     UART_InitStruct.UART_Mode       =	UART_Mode_Rx | UART_Mode_Tx;
	   UART_Init(UART1, &UART_InitStruct);
	 
	 	 /*NVIC Config*/
		 NVIC_InitTypeDef NVIC_InitStruct;
		 
		 //NVIC InitSuruct Def
		 NVIC_InitStruct.NVIC_IRQChannel    = UART1_IRQn;
		 NVIC_InitStruct.NVIC_IRQChannelPriority = 0;
		 NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		 NVIC_Init(&NVIC_InitStruct);
	
		 //Receive Data register interrupt Enable
		 UART_ITConfig(UART1, UART_IT_RXIEN, ENABLE);
		 
		 /*Enable UART1*/
		 UART_Cmd(UART1, ENABLE);
}

/*
UART1 TX Send a Byte to external Device 
*/
void UART1_Send_Byte(uint8_t data)
{
     UART_SendData(UART1, (uint16_t)data);	
	   while(UART_GetFlagStatus(UART1, UART_FLAG_TXEPT) == RESET);
}	

/*
UART1 TX Send a String to external Device
*/
void UART1_Send_String(char* buffer)
{
     uint16_t length;
	   length = (uint16_t)strlen(buffer);
	   
	   for(uint16_t i=0 ; i<length;i++)
	   {
	       UART_SendData(UART1, (uint16_t)(*(buffer+i)));	
	       while(UART_GetFlagStatus(UART1, UART_FLAG_TXEPT) == RESET);
	   }
}

/*
UART1 RX BUFFER Reader
*/
void UART1_IT_ReceiveDATA(void)
{
	   //check receive status
     if(UART_GetITStatus(UART1, UART_IT_RXIEN) != RESET) 
		 {
		    //Clear Receive Data register interrupt FLAG
			  UART_ClearITPendingBit(UART1, UART_IT_RXIEN);
			 
			  UART1_RxDataBuff[UART1_RxAvalData] = UART_ReceiveData(UART1);
			  UART1_RxP = &UART1_RxDataBuff[UART1_RxAvalData];
			  
        UART1_RxAvalData++;			 
        if(UART1_RxAvalData >99)
				{
				   UART1_RxAvalData = 0;
				}					
		 }
}


/*
The Function which initializes Peripheral UART2  
*/
void UART2_INIT(void)
{
	   /*APB1 Clock Source Enable*/
	   RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2, ENABLE);
	  
     /*GPIO Config*/
	   GPIO_InitTypeDef GPIO_InitStruct;
	     
	   //AF Config
	   GPIO_PinAFConfig(GPIOC, GPIO_PinSource4, GPIO_AF_3);
	   GPIO_PinAFConfig(GPIOC, GPIO_PinSource5, GPIO_AF_3);
	
		 //GPIO InitStructure Def
	   GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_4;
	   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
     GPIO_Init(GPIOC, &GPIO_InitStruct);                 //TX
	   
	   GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_5;
     GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	   GPIO_Init(GPIOC, &GPIO_InitStruct);                 //RX
	  
     /*UART Config*/	 
	   UART_InitTypeDef UART_InitStruct;
	
	   //UART Initstruct Def
     UART_InitStruct.UART_BaudRate   = 9600;
     UART_InitStruct.UART_WordLength = UART_WordLength_8b;
     UART_InitStruct.UART_StopBits   = UART_StopBits_1;
     UART_InitStruct.UART_Parity     = UART_Parity_No;
     UART_InitStruct.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
     UART_InitStruct.UART_Mode       = UART_Mode_Rx | UART_Mode_Tx;
	   UART_Init(UART2, &UART_InitStruct);
	 
	 	 /*NVIC Config*/
		 NVIC_InitTypeDef NVIC_InitStruct;
		 
		 //NVIC InitSuruct Def
		 NVIC_InitStruct.NVIC_IRQChannel    = UART2_IRQn;
		 NVIC_InitStruct.NVIC_IRQChannelPriority = 1;
		 NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		 NVIC_Init(&NVIC_InitStruct);
	
		 //Receive Data register interrupt Enable
		 UART_ITConfig(UART2, UART_IT_RXIEN, ENABLE);
		 
		 /*Enable UART2*/
		 UART_Cmd(UART2, ENABLE);
}


/*
UART2 TX Send a Byte to external Device 
*/
void UART2_Send_Byte(uint8_t data)
{
     UART_SendData(UART2, (uint16_t)data);	
	   while(UART_GetFlagStatus(UART2, UART_FLAG_TXEPT) == RESET);
}	

/*
UART2 TX Send a String to external Device
*/
void UART2_Send_String(char* buffer)
{
     uint16_t length;
	   length = (uint16_t)strlen(buffer);
	   
	   for(uint16_t i=0 ; i<length;i++)
	   {
	       UART_SendData(UART2, (uint16_t)(*(buffer+i)));	
	       while(UART_GetFlagStatus(UART2, UART_FLAG_TXEPT) == RESET);
	   }
}

/*
UART2 RX BUFFER Reader
*/
void UART2_IT_ReceiveDATA(void)
{
	   //check receive status
     if(UART_GetITStatus(UART2, UART_IT_RXIEN) != RESET) 
		 {
		    //Clear Receive Data register interrupt FLAG
			  UART_ClearITPendingBit(UART2, UART_IT_RXIEN);
			       
        UART2_RxDataBuff[UART2_RxCnt] = UART2 -> RDR & 0x01FF;
			  //UART2_RxDataBuff[UART2_RxCnt] = UART_ReceiveData(UART2);
			  UART2_RxP = &UART2_RxDataBuff[UART2_RxCnt];
			  UART2_RxCnt++; 
			 
			  if((UART2_RxCnt == 1)&&(UART2_RxDataBuff[0]!=0xA5))
				{
				    UART2_RxCnt = 0;
				}
				
				if(UART2_RxCnt ==3)
				{
				    UART2_RxCnt = 0;
					  CAM_RxFlag  = 1;
				}
		 }
}


