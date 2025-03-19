#ifndef C602_H_
#define C602_H_

#include "stdint.h"
#include "motor_def.h"

extern Motor_Controller_struct motor_3508_instnce[8];

void C602_Set_Current_5_8(void);
void C602_Set_Current_1_4(void);
#endif