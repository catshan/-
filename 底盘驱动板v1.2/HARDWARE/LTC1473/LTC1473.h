#ifndef __LTC1473
#define __LTC1473

#include "sys.h"

#define LTC1473_IN1 	PBout(12)
#define LTC1473_IN2 	PBout(13)
#define LTC1473_DIODE	PBout(14)

typedef enum
{
	LTC1473_MODE_POWER,
	LTC1473_MODE_CAP,
}LTC1473_MODE;

void LTC1473_Init(void);
void LTC1473_Cmd(FunctionalState cmd);
void LTC1473_Change(LTC1473_MODE mode);
#endif
