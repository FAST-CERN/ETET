#ifndef _SPI_H_
#define _SPI_H_

#include "HAL_Device.h"

void SPI1_INIT(void);
void SPI1_M_CSLow(void);
void SPI1_M_CSHigh(void);
uint32_t SPI1_M_ReadWrite_Byte(uint8_t);

void SPI2_INIT(void);
void SPI2_CSLow(void);
void SPI2_CSHigh(void);
void SPI2_DCLow(void);
void SPI2_DCHigh(void);
void SPI2_RSTLow(void);
void SPI2_RSTHigh(void);
void SPI2_Write_Byte(uint8_t);

#endif
