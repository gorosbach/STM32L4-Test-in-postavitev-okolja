#ifndef _HTS221_H
#define _HTS221_H

#include "stdint.h"

int HTS221_Init (void);
void HTS221_Get_Calibration (void);
float HTS221_Get_Temperature(void);
float HTS221_Get_Humidity(void);

#define HUMADRESS	0x5F
#define CALISTART 0x30
#define CALISTOP 0x3F		

struct Cal_Data {
uint8_t H0_rH_x2;
uint8_t H1_rH_x2;
uint8_t T0_degC_x8;
uint8_t T1_degC_x8;
uint16_t T1_msb;
uint16_t T0_msb;
int16_t H0_T0_OUT;
int16_t H1_T0_OUT;
int16_t T0_OUT;
int16_t T1_OUT;
int16_t T0_degC;
int16_t T1_degC;
};

#endif
