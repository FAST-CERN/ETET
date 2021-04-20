#include "main.h"

extern  KEY_BASE KEY_STAT;

/**
* @brief Peripheral KEY Configuration
*/
void KEY_Config(void)
{    
     /*GPIO Config*/
     GPIO_InitTypeDef  GPIO_InitStructure;	
	   GPIO_InitStructure.GPIO_Pin   = KEY6_PIN;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ; 
	   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	   GPIO_Init(GPIOA, &GPIO_InitStructure);
	   
	   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	   GPIO_InitStructure.GPIO_Pin   = KEY1_PIN | KEY2_PIN | KEY3_PIN | KEY4_PIN;
	   GPIO_Init(GPIOB, &GPIO_InitStructure);
	   
	   GPIO_InitStructure.GPIO_Pin   = KEY5_PIN;
	   GPIO_Init(GPIOC, &GPIO_InitStructure);
	
     /*KEY_STAT Initailization */
     KEY_STAT.Key_LOOP_H     = 0;
     KEY_STAT.Key_LOOP_L     = 0;     
     KEY_STAT.Key_Scan_Temp  = 0;         
     KEY_STAT.Key_Value      = 0;
     KEY_STAT.Pre_Key_Value  = 0;
     KEY_STAT.Key_Read_SHORT = 0;     
     KEY_STAT.Key_Read_LONG  = 0;
     KEY_STAT.Key_Valid_VAL  = 0;      
}

/**
* @brief Scan and Process Data from KEY
*/
void KEY_SCAN(void)
{
     /*Get GPIO input Data*/ 
	   KEY_STAT.Key_Scan_Temp = (uint8_t)((0xffff&(1<<8))>>3)                |    //(uint16_t)GPIOA->IDR
                             	(((uint16_t)GPIOB->IDR & (1<<10))>>10)       |
	                            (((uint16_t)GPIOB->IDR & (0xE000))>>12)      | 
	                            (((uint16_t)GPIOC->IDR & (1<<6))>>2)         | 
	                            0xC0;
	      
	   /*Process the data*/
	   KEY_STAT.Pre_Key_Value = KEY_STAT.Key_Value     ;
     KEY_STAT.Key_Value     = ~KEY_STAT.Key_Scan_Temp;

		 if( KEY_STAT.Pre_Key_Value == KEY_STAT.Key_Value )
		 {
				 if( KEY_STAT.Key_Value != KEY_INIVAL )                
				 {
						 KEY_STAT.Key_LOOP_L = 0;
					
						 if(KEY_STAT.Key_LOOP_H >= 8)
						 {
						    KEY_STAT.Key_Valid_VAL = KEY_STAT.Key_Value;
						    KEY_STAT.Key_Read_SHORT = 1;
							
							  if(KEY_STAT.Key_LOOP_H >=100)
							  {
									 KEY_STAT.Key_Read_SHORT = 0;
								   KEY_STAT.Key_Read_LONG  = 1;
								 
								   KEY_STAT.Key_LOOP_H = 101;
							  }
							  else
								   KEY_STAT.Key_LOOP_H ++;
						 }
						 else
							  KEY_STAT.Key_LOOP_H ++;									
				}
				else
				{
						KEY_STAT.Key_LOOP_H = 0;
						KEY_STAT.Key_LOOP_L ++ ;
					
						if(KEY_STAT.Key_LOOP_L>=5)
		        {
							 KEY_STAT.Key_LOOP_L = 0;

							 KEY_STAT.Key_Read_SHORT = 0;
							 KEY_STAT.Key_Read_LONG  = 0;
		        }									
				}                
		 }
		 else
		 {
				KEY_STAT.Key_LOOP_H = 0;
				KEY_STAT.Key_LOOP_L = 0;
		 }
	   
}

/*
Read Data from KEY and make decisions
*/
void KEY_Reader(void)
{
     if(KEY_STAT.Key_Read_SHORT == 1)
	   {
		    if(KEY_STAT.Key_LOOP_H == 0)    
        {
					 switch (KEY_STAT.Key_Valid_VAL)
					 {
						 case 1<<0:
							 KEY1_Server();
						   break;
						 case 1<<1:
							 KEY2_Server();
						   break;
						 case 1<<2:
							 KEY3_Server();
						   break;
						 case 1<<3:
							 KEY4_Server();
						   break;
						 case 1<<4:
							 KEY5_Server();
						   break;
						 case 1<<5:
							 KEY6_Server();
						   break;
					 }				 	 					 
           KEY_STAT.Key_Read_SHORT = 0; 
        }
	   }
     else
     {
        if(KEY_STAT.Key_Read_LONG == 1)
        {
           if(KEY_STAT.Key_LOOP_L == 0)
           {
              //NULL
           }               
        }
     }		 
}

/**
* @brief Execute Function of Key1
*/
void KEY1_Server(void)
{

}

/*
Execute Function of Key2
*/
void KEY2_Server(void)
{

}

/*
Execute Function of Key3
*/
void KEY3_Server(void)
{

}

/*
Execute Function of Key4
*/
void KEY4_Server(void)
{

}

/*
Execute Function of Key5
*/
void KEY5_Server(void)
{

}

/*
Execute Function of Ke6
*/
void KEY6_Server(void)
{

}

/**
* @brief KEY Test Function
*/
void KEY_TEST(void)
{
     LED1_Toggle();
}	
