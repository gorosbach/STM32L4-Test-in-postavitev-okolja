#include "stm32l4xx_hal.h"
#include "HTS221.h"


extern I2C_HandleTypeDef hi2c2; //pove�, da bo� imel opravka s strukturo, ki je deklarirana zunaj

struct Cal_Data cdata;

/* Funkcija inicializira senzor*/

int HTS221_Init (void)
{
		uint8_t data[3];
		
		data[0] = 0x20;
		data[1] = 0x01;		
		HAL_I2C_Master_Transmit(&hi2c2, HUMADRESS<<1, data, 2, 50);
		data[0] = 0x0f; //whoami request

		HAL_I2C_Master_Transmit(&hi2c2, HUMADRESS<<1, data, 1, 50);
		data[0] = 0x00;
		HAL_I2C_Master_Receive(&hi2c2, HUMADRESS<<1, data, 1, 50);
		
		return(data[0]); // vrne vrednost registra who am i (0XBCh)
}

/* Funkcija prebere 16 karlibracijskih registrov ki se zacnejo na 0x30h in koncajo na 0x3f ter njihove vrednosti prekopira v strukturo
	 Cal_Data*/

void HTS221_Get_Calibration (void) 
{
	uint8_t data[3];
	uint8_t caliData[16];
	uint8_t i = 0;
	
	
for(int x = CALISTART;x<(CALISTOP+0x01);x++)
		{
			data[0] = x;
			HAL_I2C_Master_Transmit(&hi2c2, HUMADRESS<<1, data, 1, 50);
			HAL_Delay(10);
			HAL_I2C_Master_Receive(&hi2c2, HUMADRESS<<1, data, 1, 50);
			caliData[i] = data[0];
			i++;
		}
		/* OD  TUKAJ NAPREJ PRERACUNAJ VSE KALIBRACIJSKE SPREMENLJIVKE */
	
		cdata.H0_rH_x2 = caliData[0];
		cdata.H1_rH_x2 = caliData[1];
		cdata.T0_degC_x8 = caliData[2];
		cdata.T1_degC_x8 = caliData[3];
		cdata.T1_msb = (caliData[5] & 0xC)>>2;
		cdata.T0_msb = caliData[5] & 0x3;
		cdata.H0_T0_OUT = caliData[7]<<8 | caliData[6];
		cdata.H1_T0_OUT = caliData[11]<<8 | caliData[10];
		cdata.T0_OUT = caliData[13]<<8 | caliData[12];
		cdata.T1_OUT = caliData[15]<<8 | caliData[14];

		cdata.T0_degC = cdata.T0_msb<<8 | cdata.T0_degC_x8;
		cdata.T1_degC = cdata.T1_msb<<8 | cdata.T1_degC_x8;
		cdata.T0_degC = cdata.T0_degC >> 3;
		cdata.T1_degC = cdata.T1_degC >> 3;
		}

/* Funkcija prebere vse 4 registre, izloci pa vlago */
float HTS221_Get_Temperature()
{
		uint8_t data[4];
		data[0] = 0x21;
		data[1] = 0x01;		//one shot
		HAL_I2C_Master_Transmit(&hi2c2, HUMADRESS<<1, data, 2, 50);
	
		data[0] = 0x20;
		data[1] = 0x80;		//enable
		HAL_I2C_Master_Transmit(&hi2c2, HUMADRESS<<1, data, 2, 50);
	
		for(int x= 0; x<4; x++)
		{
			switch(x)
			{
				case 0:
				data[0] = 0x28;	
				break;
				
				case 1:
				data[0] = 0x29;	
				break;
				
				case 2:
				data[0] = 0x2a;	
				break;
				
				case 3:
				data[0] = 0x2b;	
				break;
			}	
		
		HAL_I2C_Master_Transmit(&hi2c2, HUMADRESS<<1, data, 1, 50);
		HAL_Delay(5);
		HAL_I2C_Master_Receive(&hi2c2, HUMADRESS<<1, data, 1, 50);
		data[x] = *data;
		}
		int16_t T_OUT = data[3]<<8 | data[2];

		float fTemp=(float)(T_OUT-cdata.T0_OUT)*(float)(cdata.T1_degC-cdata.T0_degC)/(float)(cdata.T1_OUT-cdata.T0_OUT) + cdata.T0_degC;	
		return(fTemp);
}

/* Funkcija prebere vse 4 registre, izloci pa temperaturo */
float HTS221_Get_Humidity()
{
		uint8_t data[3];
		data[0] = 0x21;
		data[1] = 0x01;		//one shot
		HAL_I2C_Master_Transmit(&hi2c2, HUMADRESS<<1, data, 2, 50);
	
		data[0] = 0x20;
		data[1] = 0x80;		//enable
		HAL_I2C_Master_Transmit(&hi2c2, HUMADRESS<<1, data, 2, 50);
	
		for(int x= 0; x<4; x++)
		{
			switch(x)
			{
				case 0:
				data[0] = 0x28;	
				break;
				
				case 1:
				data[0] = 0x29;	
				break;
				
				case 2:
				data[0] = 0x2a;	
				break;
				
				case 3:
				data[0] = 0x2b;	
				break;
			}	
		
		HAL_I2C_Master_Transmit(&hi2c2, HUMADRESS<<1, data, 1, 50);
		HAL_Delay(5);
		HAL_I2C_Master_Receive(&hi2c2, HUMADRESS<<1, data, 1, 50);
		data[x] = *data;
		}
	
		int16_t H_OUT = data[1]<<8 | data[0];

		float fHum = (float)(H_OUT-cdata.H0_T0_OUT)*(float)(cdata.H1_rH_x2-cdata.H0_rH_x2)/(float)(cdata.H1_T0_OUT-cdata.H0_T0_OUT)+ cdata.H0_rH_x2;
		fHum *=5.0f;

		return(fHum);
}
