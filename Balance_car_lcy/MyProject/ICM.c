#include "main.h"

int16_t ICM_ACC_X = 0x0000;
int16_t ICM_ACC_Y = 0x0000;
int16_t ICM_ACC_Z = 0x0000;
int16_t ICM_GYR_X = 0x0000;
int16_t ICM_GYR_Y = 0x0000;
int16_t ICM_GYR_Z = 0x0000;

float   angle_acc    = 0;
float   angle_v_gry  = 0;
float   angle_result = 0;

/*
The Function which Initializes ICM20602
*/
void ICM_INIT(void)//六轴传感器初始化
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
		 ICM_RegisterW_Byte(ICM20602_CONFIG      , 0x03);   //Gyroscope & Tempreature Sensor BW RATE NOISE
	   ICM_RegisterW_Byte(ICM20602_SMPLRT_DIV  , 0x07);   //Set the Update Rate of Sensor Register
		 ICM_RegisterW_Byte(ICM20602_GYRO_CONFIG , 0x18);   //Selcet the Full Scale Range of Gyroscope +-2000dps
		 ICM_RegisterW_Byte(ICM20602_ACCEL_CONFIG, 0x10);   //Selcet the Full Scale Range of Accelerometer +-8g
		 ICM_RegisterW_Byte(ICM20602_ACCEL_CONFIG_2, 0x26); //Average 16 samples 5.1Hz
}

/*
The Function which Gets the Data of Accelerometer 
*/
void ICM_GETDATA_ACC(void)//加速度计获取X,Y,X轴加速度。分别放在ICM_ACC_X，ICM_ACC_Y，ICM_ACC_Z里
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
void ICM_GETDATA_GYR(void)//陀螺仪获取绕X,Y,Z轴角速度，分别放在ICM_GYR_X,ICM_GYR_Y,ICM_GYR_Z里
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
* @brief calculate the angle
*/
void ICM_ANGLE(void)//计算角度，加速度计：angle_acc，陀螺仪：angle_v_gry，经滤波后：angle_result
{    

	    angle_acc   = (float)atan((double)ICM_ACC_Z / (double)ICM_ACC_X)/Pi*180;

			angle_v_gry = (float)ICM_GYR_Y*2000/(float)32768;

			angle_result = Complementary_Filter(angle_acc, angle_v_gry);
}

/**
* @brief Complementary Filter, deal with data form acc&gyro
*/
float Complementary_Filter(float accel_m, float gyro_m)//卡尔曼滤波
{
     static float   last_angle;
	   static float   temp_angle;
	   static uint8_t  flag;
	 
	   if(!flag)
		 {
		    flag = 1;
			  last_angle = accel_m;
		 }
	  
		 temp_angle = (float)((tao_imu/(tao_imu + dt_imu))*(last_angle + dt_imu*gyro_m)+(dt_imu/(tao_imu+dt_imu))*accel_m);
		 
		 if(isnan(temp_angle))
		 {
		    temp_angle = accel_m;
		 }
		 
	   last_angle = temp_angle;
		 
		 return temp_angle;
}

/**
* @brief Runge-Kutta Integrator
* @param 
* @param 
* @extal 
*/
float Runge_Kutta_Integrator(int16_t val)//龙格库塔求积分
{
      static uint8_t t;
	    static float   val_p1;
	    static float   val_p2;
	    static float   val_p3;
	    float  result;
	
	    if(t<3)
			{
			   result = (float)val*dt_imu;
				 t++;
			}
			else
			{
			   result = (val_p3+val_p2*2+val_p1*2+val)*dt_imu/6;
			}
			
			val_p3 = val_p2;
			val_p2 = val_p1;
			val_p1 = (float)val;
			
			return result;
}

/*
The Function which check the status of ICM20602
*/
void ICM_IF_NORM(void)//检查六轴传感器状态
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
