/*
 * @Author: skybase
 * @Date: 2025-01-13 18:11:08
 * @LastEditors: skybase
 * @LastEditTime: 2025-02-28 03:45:06
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \undefinedd:\Project\Embedded_project\Stm_pro\25Rc_jump_stm32H7_RT_THREAD\BSP\Motor\motor_def.h
 */
#ifndef MOTOR_DEF_H
#define MOTOR_DEF_H

#include "stdio.h"


/* 反馈来源设定,若设为OTHER_FEED则需要指定数据来源指针,详见Motor_Controller_s*/
typedef enum
{
    MOTOR_FEED = 0,
    OTHER_FEED,
} Feedback_Source_e;

/* 电机正反转标志 */
typedef enum
{
    MOTOR_DIRECTION_NORMAL = 0,
    MOTOR_DIRECTION_REVERSE = 1
} Motor_Reverse_Flag_e;

typedef enum
{
    MOTOR_STOP = 0,
    MOTOR_ENABLED = 1,
} Motor_Working_Type_e;

/* 电机控制设置,包括闭环类型,反转标志和反馈来源 */
typedef struct
{
    Motor_Working_Type_e motor_enable_flag;  // 使能标志
    Motor_Reverse_Flag_e motor_reverse_flag; // 是否反转
    Feedback_Source_e angle_feedback_source; // 角度反馈类型
    Feedback_Source_e speed_feedback_source; // 速度反馈类型

} Motor_Control_Setting_s;

typedef struct
{
    struct normal
    {
        float velocity_lim;
        float iq_lim;
    };
    
    struct reverse
    {
        float velocity_lim;
        float iq_lim;
    };
    

} Motor_Limit_Setting_s;


/* 电机类型枚举 */
typedef enum
{
    MOTOR_TYPE_NONE = 0,
    MOTOR_TYPE_DC, // 一般直流电机

} Motor_Type_e;

typedef struct
{
    uint32_t id;                // 程序中的id,用于其它模块访问该电机模块
    uint32_t motor_protocal_id; // 协议帧的id

    Motor_Control_Setting_s motor_cofig;
    Motor_Limit_Setting_s motor_lim_cofig;

    // 输入和输出数据不互通
    struct in // 用作输入传感,不参与输出控制
    {
        float velocity; // rad/s
        float deg_pos;  // (rad)
        float iq;       // (A)
    } get;
    struct out // 用作电机输出
    {
        float velocity;
        float deg_pos;
        float iq;
    } set;

} Motor_Controller_struct;

#endif // !MOTOR_DEF_H
