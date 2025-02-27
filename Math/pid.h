/*
 * @Author: Ptisak
 * @Date: 2023-06-17 21:10:18
 * @LastEditors: skybase
 * @LastEditTime: 2024-11-05 20:26:46
 * @Version: Do not edit
 */
/******************************************************************************
/// @brief
/// @copyright Copyright (c) 2017 <dji-innovations, Corp. RM Dept.>
/// @license MIT License
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction,including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense,and/or sell
/// copies of the Software, and to permit persons to whom the Software is furnished
/// to do so,subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
/// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
*******************************************************************************/
#ifndef __pid_H
#define __pid_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"

enum
{
    LLAST = 0,
    LAST = 1,
    NOW = 2,

    POSITION_PID,
    DELTA_PID,
};
typedef struct __pid_t
{
    float p;
    float i;
    float d;

    float set[3]; // 目标�?,包含NOW�? LAST�? LLAST上上�?
    float get[3]; // 测量�?
    float err[3]; // 误差

    float pout; // p输出
    float iout; // i输出
    float dout; // d输出

    float pos_out;      // 本次位置式输�?
    float last_pos_out; // 上次输出
    float delta_u;      // 本次增量�?
    float delta_out;    // 本次增量式输�? = last_delta_out + delta_u
    float last_delta_out;
    float out;

    float max_err;
    float deadband; // err < deadband return
    uint32_t pid_mode;
    uint32_t MaxOutput;     // 输出限幅
    uint32_t IntegralLimit; // 积分限幅

    void (*f_param_init)(struct __pid_t *pid, // PID参数初始�?
                         uint32_t pid_mode,
                         uint32_t maxOutput,
                         uint32_t integralLimit,
                         float p,
                         float i,
                         float d);
    void (*f_pid_reset)(struct __pid_t *pid, float p, float i, float d); // pid三个参数修改

} pid_t;

void PID_struct_init(
    pid_t *pid,
    uint32_t mode,
    uint32_t maxout,
    uint32_t intergral_limit,

    float kp,
    float ki,
    float kd);

float pid_calc(pid_t *pid, float get, float set);
float pid_sp_calc(pid_t *pid, float get, float set, float gyro);

#endif
