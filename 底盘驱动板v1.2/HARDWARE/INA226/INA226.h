#ifndef __INA226_H
#define __INA226_H

#include "sys.h"

#define INA226_ADDR 0x80

#define Addr_Config 			0x00
#define Addr_ShuntVoltage 0x01
#define Addr_BusVoltage 	0x02
#define Addr_Power			 	0x03
#define Addr_Current		 	0x04
#define Addr_Calibration 	0x05
#define Addr_MaskOrEnable	0x06
#define Addr_AlertLimit 	0x07
#define Addr_DieID 				0xFF

#define Die_ID 0x2260

typedef struct 
{
	float Current;
	float Power;
	float BusVoltage;
}INA226_INFO;

extern INA226_INFO inaInfo;

u8 INA226_Init(void);
u8 INA226_WriteData(u8 addr,u16 data);
u16 INA226_ReadData(u8 addr);

float INIA226_GetCurrent(void );
float INA226_GetPower(void );
float INA226_GetShuntVoltage(void );
float INA226_GetBusVoltage(void );


#endif
