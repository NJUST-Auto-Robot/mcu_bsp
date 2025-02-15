#ifndef FOUR_DRVER_KINEMATIC_H
#define FOUR_DRVER_KINEMATIC_H

#include "dc_motor.h"
typedef struct four_drver_kinematic_t
{
    dc_motor_t *motor0;
    dc_motor_t *motor1;
    dc_motor_t *motor2;
    dc_motor_t *motor3;

    // >以下为底盘的配置信息
    // todo 完善逻辑
    float Distance_W; //左右轮子的间距
    
} four_drver_kinematic_t;

void fourDrverKinematicInit(four_drver_kinematic_t *robot, dc_motor_t *mt0, dc_motor_t *mt1, dc_motor_t *mt2, dc_motor_t *mt3);
void fourDrverKinematicRunOpenloop(four_drver_kinematic_t *robot, float velocity, float w);

#endif
