#include "main.h"

/*External Variables*/
extern uint8_t *CAM_BufADDR;
extern uint8_t CAM_Finish_Flag;
 
/**
* @brief Initialize DMA Module
*/
void DMA1_INIT(void)
{
	   /*Enable Clock Source of DMA1*/
	   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	   /*GPIP Config*/
     CAM_DMA1_GPIO_INIT();
	
	   /*DMA1 Config*/
	   DMA_InitTypeDef DMA_InitStructure;
		 DMA_DeInit(DMA1_Channel4);

		 DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)GPIO_IDR_ADDR(B0);		// 源地址
		 DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)CAM_BufADDR;					// 目标地址
		 DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;					// 外设作为源
		 DMA_InitStructure.DMA_BufferSize         = IMG_H*IMG_W;										// 传输多少个数据
		 DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;  		// 外设地址不增加
		 DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;						// 内存地址依次+1
		 DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;		// 外设每次传输一个字节
		 DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;				// 内存每次传输一个字节
		 DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;								// 非循环模式
		 DMA_InitStructure.DMA_Priority           = DMA_Priority_VeryHigh;					// 优先级最高
		 DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;								// 非内存到内存模式
		 DMA1_Channel4 -> CCR                    |=(1<<15);                         // Auto Reload Enable                     
		 DMA_Init(DMA1_Channel4, &DMA_InitStructure);

     /*DMA1 Interrupt Config*/
     NVIC_InitTypeDef NVIC_InitStructure;

		 NVIC_InitStructure.NVIC_IRQChannel         = DMA1_Channel4_5_IRQn;                                 
		 NVIC_InitStructure.NVIC_IRQChannelPriority = 0;						
		 NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;								
		 NVIC_Init(&NVIC_InitStructure);
 
		 DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);													  // 配置DMA传输完成中断
		 
		 DMA_Cmd(DMA1_Channel4, ENABLE);																	          // 开启DMA1
     DMA_Cmd(DMA1_Channel4, DISABLE);                                           // 
}


/**
*  @brief DMA1 CH14 Interrupt Call back
*/
void DMA1_CH14_IT_CallBack(void)
{
     if(DMA_GetITStatus(DMA1_IT_TC4) != RESET)
		 {
		    DMA_ClearITPendingBit(DMA1_IT_TC4);		 
			  DMA_Cmd(DMA1_Channel4, DISABLE);
			   
			  CAM_Finish_Flag = 1;
		 }
}
