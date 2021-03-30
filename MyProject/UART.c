#include "main.h"

extern char      UART1_RxDataBuff[100];
extern uint16_t  UART1_RxCounter;
extern char*     UART1_RxP;

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
			 
			  UART1_RxDataBuff[UART1_RxCounter%100] = UART_ReceiveData(UART1);
			  
			  UART1_RxCounter++;			 
			  if(UART1_RxCounter == 65499)
					 UART1_RxCounter = 0;					
		 }
}
