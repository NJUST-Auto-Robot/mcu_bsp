#include "four_drver_kinematic.h"

//* 本库基于四个直流有刷电机驱动四驱底盘
// !可以与闭环电机系统配合使用(闭环+真实坐标系)
// !可以与开环电机系统配合使用(开环)
// >非完善,目前仅写了开环

/**
 * @brief 四驱底盘的初始化函数,电机的绑定从左上角开始顺时针计算
 *
 */
void fourDrverKinematicInit(four_drver_kinematic_t *robot, dc_motor_t *mt0, dc_motor_t *mt1, dc_motor_t *mt2, dc_motor_t *mt3)
{
    memset(robot, 0, sizeof(four_drver_kinematic_t));

    robot->motor0 = mt0;
    robot->motor1 = mt1;
    robot->motor2 = mt2;
    robot->motor3 = mt3;
}

/**
 * @brief 四驱底盘的驱动函数,所有速度基于pwm占空比的ccr值
 * @param velocity 正为前进,负为后退
 * @param w 正为左转,负为右转
 */
void fourDrverKinematicRunOpenloop(four_drver_kinematic_t *robot, float velocity, float w)
{
    float v_left = velocity + (w);
    float v_right = velocity - (w);

    robot->motor0->velocity_pwm = v_left;
    robot->motor1->velocity_pwm = v_right;
    robot->motor2->velocity_pwm = v_right;
    robot->motor3->velocity_pwm = v_left;

    DCMotorSetSpeedOpenLoop(robot->motor0, 0, 0);
    DCMotorSetSpeedOpenLoop(robot->motor1, 0, 0);
    DCMotorSetSpeedOpenLoop(robot->motor2, 0, 0);
    DCMotorSetSpeedOpenLoop(robot->motor3, 0, 0);

}
