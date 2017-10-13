#include "stm32l4xx_hal.h"
#include "LPS22HM.h"

extern I2C_HandleTypeDef hi2c2; //poveš, da boš imel opravka s strukturo, ki je deklarirana zunaj

int LPS22HM_Init()
{
		uint8_t data[3];
		data[0] = 0x11;
		data[1] = 0x01;		
		HAL_I2C_Master_Transmit(&hi2c2, PRESSADRESS<<1, data, 2, 50);
	
		data[0] = 0x0f; //whoami request
		HAL_I2C_Master_Transmit(&hi2c2, PRESSADRESS<<1, data, 1, 50);
		data[0] = 0x00;
		HAL_I2C_Master_Receive(&hi2c2, PRESSADRESS<<1, data, 1, 50);
	
		return(data[0]); //vrne vrednost registra Who am i
}

float LPS22HM_Get_Pressure()
{
		uint8_t data[3];
		uint8_t dataIn[5];
		data[0] = 0x11;
		data[1] = 0x01;		
		HAL_I2C_Master_Transmit(&hi2c2, PRESSADRESS<<1, data, 2, 50);
		for(int i = 0; i< 5; i++){
		
			switch(i)
			{
				case 0:
				data[0] = LPS22HB_PRES_OUT_XL;	
				break;
				
				case 1:
				data[0] = LPS22HB_PRES_OUT_L;	
				break;
				
				case 2:
				data[0] = LPS22HB_PRES_OUT_H;	
				break;
				
				case 3:
				data[0] = LPS22HB_TEMP_OUT_L;	
				break;
				
				case 4:
				data[0] = LPS22HB_TEMP_OUT_H;	
				break;
			}
			
		HAL_I2C_Master_Transmit(&hi2c2, PRESSADRESS<<1, data, 1, 50);
		HAL_Delay(20);
		HAL_I2C_Master_Receive(&hi2c2, PRESSADRESS<<1, data, 1, 50);
		dataIn[i] = *data;	
		}
				
		int32_t val = ((dataIn[2]<<24) | (dataIn[1]<<16) | (dataIn[0]<<8)) >> 8;
		float fval = (float)val/4096;
		fval = fval+((ASL*120)/1000);
	
		return(fval);
}

float LPS22HM_Get_Temperature()
{
		uint8_t data[3];
		uint8_t dataIn[5];
		data[0] = 0x11;
		data[1] = 0x01;		
		HAL_I2C_Master_Transmit(&hi2c2, PRESSADRESS<<1, data, 2, 50);
		for(int i = 0; i< 5; i++){
		
			switch(i)
			{
				case 0:
				data[0] = LPS22HB_PRES_OUT_XL;	
				break;
				
				case 1:
				data[0] = LPS22HB_PRES_OUT_L;	
				break;
				
				case 2:
				data[0] = LPS22HB_PRES_OUT_H;	
				break;
				
				case 3:
				data[0] = LPS22HB_TEMP_OUT_L;	
				break;
				
				case 4:
				data[0] = LPS22HB_TEMP_OUT_H;	
				break;
			}
			
		HAL_I2C_Master_Transmit(&hi2c2, PRESSADRESS<<1, data, 1, 50);
		HAL_Delay(20);
		HAL_I2C_Master_Receive(&hi2c2, PRESSADRESS<<1, data, 1, 50);
		dataIn[i] = *data;	
		}

		int32_t temp = (dataIn[4]<<8 | dataIn[3]);
		float ftemp = (float)temp / 100;
 		
		return(ftemp);
}

	
