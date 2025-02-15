/*
 * @Author: skybase
 * @Date: 2024-08-14 00:52:25
 * @LastEditors: skybase
 * @LastEditTime: 2024-11-08 05:20:28
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARM\BSP\Interface\joystick.h
 */
#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

typedef enum
{
    None = 0,
    DPadUp = 1,
    DPadDown = 2,
    DPadLeft = 4,
    DPadRight = 8,
    Start = 0x10,
    Back = 0x20,
    LeftThumb = 0x40,
    RightThumb = 0x80,
    LeftShoulder = 0x100,
    RightShoulder = 0x200,
    A = 0x1000,
    B = 0x2000,
    X = 0x4000,
    Y = 0x8000

} GamepadButtonFlags;

typedef enum
{
    LB = 1,
    RB = 2,
    Beitong = 4,
    Thrbo = 8,
    Clear = 0x10,
}GamepadButtonFlags_expand;

#pragma pack(1)
typedef struct
{
    uint16_t VL;
    uint16_t HL;
    uint16_t VR;
    uint16_t HR;

} spindle;

struct dataPack
{
    uint8_t frame[2];
    uint16_t bs;
    uint16_t bse;
    spindle sp;
    uint8_t ddr8;
};
#pragma pack()



void JoystickDataUpdate();
void JoystickDataTransmit();

extern struct dataPack joystick_data;

#ifdef __cplusplus
}
#endif

#endif
