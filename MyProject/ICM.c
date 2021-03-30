#include "main.h"

uint16_t ICM_ACC_X = 0x0000;
uint16_t ICM_ACC_Y = 0x0000;
uint16_t ICM_ACC_Z = 0x0000;
uint16_t ICM_GYR_X = 0x0000;
uint16_t ICM_GYR_Y = 0x0000;
uint16_t ICM_GYR_Z = 0x0000;

/*
The Function which Initializes ICM20602
*/
void ICM_INIT(void)
{ 
	   uint8_t temp = 0x00; 
	 
     Delay_ms(10);
	   ICM_IF_NORM();
	
	   ICM_RegisterW_Byte(ICM20602_PWR_MGMT_1, 0x80); //Reset
	   Delay_ms(5);
	 
	   do
		 {
			   temp = ICM_RegisterR_Byte(ICM20602_PWR_MGMT_1);
		 }while( temp != 0x41 );                         
		 
		 ICM_RegisterW_Byte(ICM20602_PWR_MGMT_1  , 0x01);   //Clock Source Auto Select
		 ICM_RegisterW_Byte(ICM20602_PWR_MGMT_2  , 0x00);   //Set Gyroscope and Accelerometer ON
		 ICM_RegisterW_Byte(ICM20602_CONFIG      , 0x01);   //Gyroscope & Tempreature Sensor BW RATE NOISE
	   ICM_RegisterW_Byte(ICM20602_SMPLRT_DIV  , 0x07);   //Set the Update Rate of Sensor Register
		 ICM_RegisterW_Byte(ICM20602_GYRO_CONFIG , 0x18);   //Selcet the Full Scale Range of Gyroscope 2000dps
		 ICM_RegisterW_Byte(ICM20602_ACCEL_CONFIG, 0x10);   //Selcet the Full Scale Range of Accelerometer 8g
		 ICM_RegisterW_Byte(ICM20602_ACCEL_CONFIG_2, 0x03); //Average 16 samples 5.1Hz
}

/*
The Function which Gets the Data of Accelerometer 
*/
void ICM_GETDATA_ACC(void)
{
     uint8_t data[6];
	
	   data[0]=ICM_RegisterR_Byte(ICM20602_ACCEL_XOUT_H);
	   data[1]=ICM_RegisterR_Byte(ICM20602_ACCEL_XOUT_L);
     data[2]=ICM_RegisterR_Byte(ICM20602_ACCEL_YOUT_H);
	   data[3]=ICM_RegisterR_Byte(ICM20602_ACCEL_YOUT_L);
	   data[4]=ICM_RegisterR_Byte(ICM20602_ACCEL_ZOUT_H);
	   data[5]=ICM_RegisterR_Byte(ICM20602_ACCEL_ZOUT_L);
	
	   ICM_ACC_X = (int16_t)(((uint16_t)data[0]<<8)| data[1]);
	   ICM_ACC_Y = (int16_t)(((uint16_t)data[2]<<8)| data[3]);
	   ICM_ACC_Z = (int16_t)(((uint16_t)data[4]<<8)| data[5]);
}

/*
The Function which Gets the Data of Accelerometer 
*/
void ICM_GETDATA_GYR(void)
{
     uint8_t data[6];
	
	   data[0]=ICM_RegisterR_Byte(ICM20602_GYRO_XOUT_H);
	   data[1]=ICM_RegisterR_Byte(ICM20602_GYRO_XOUT_L);
     data[2]=ICM_RegisterR_Byte(ICM20602_GYRO_YOUT_H);
	   data[3]=ICM_RegisterR_Byte(ICM20602_GYRO_YOUT_L);
	   data[4]=ICM_RegisterR_Byte(ICM20602_GYRO_ZOUT_H);
	   data[5]=ICM_RegisterR_Byte(ICM20602_GYRO_ZOUT_L);
	
	   ICM_GYR_X = (int16_t)(((uint16_t)data[0]<<8)| data[1]);
	   ICM_GYR_Y = (int16_t)(((uint16_t)data[2]<<8)| data[3]);
	   ICM_GYR_Z = (int16_t)(((uint16_t)data[4]<<8)| data[5]);
}

/**
* @brief calculate the bias angle
*/
float ICM_BIAS(void)
{
      return 0;
}

/*
The Function which check the status of ICM20602
*/
void ICM_IF_NORM(void)
{
     uint8_t temp = 0;
	 
	   do
		 {		 
			   temp = ICM_RegisterR_Byte(ICM20602_WHO_AM_I);
			   Delay_ms(10);
		 }
	   while(temp!=0x12);
}

/*
SPI Master Write a Byte
*/
void ICM_RegisterW_Byte(uint8_t addr,uint8_t data)
{
     SPI1_M_CSLow();
	
	   SPI1_M_ReadWrite_Byte(addr &(~(1<<7)));
	   SPI1_M_ReadWrite_Byte(data);
	   
	   SPI1_M_CSHigh();
}

/*
SPI Master Read a Byte
*/
uint8_t ICM_RegisterR_Byte(uint8_t addr)
{
        uint8_t temp;
	       
	      SPI1_M_CSLow();
	
	      SPI1_M_ReadWrite_Byte(addr |(1<<7));
	      temp = (uint8_t)SPI1_M_ReadWrite_Byte(0x00);
	   
	      SPI1_M_CSHigh();
	
	      return temp;
}
