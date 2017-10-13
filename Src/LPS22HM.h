#ifndef _LPS22HM_H
#define _LPS22HM_H

int LPS22HM_Init(void);
float LPS22HM_Get_Pressure(void);
float LPS22HM_Get_Temperature(void);



#define PRESSADRESS 0x5D
#define LPS22HB_PRES_OUT_XL	0X28 //LSB
#define LPS22HB_PRES_OUT_L	0X29
#define LPS22HB_PRES_OUT_H	0X2A //MSB
#define LPS22HB_TEMP_OUT_L	0X2B //LSB
#define LPS22HB_TEMP_OUT_H	0X2C //MSB


#define ASL 300 //nadmorska visina

#endif
