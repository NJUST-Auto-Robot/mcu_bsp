#ifndef C602_H_
#define C602_H_

#include "./motor_def.h"
#include "../Math/pid.h"

typedef struct
{
    uint8_t id;
    PID_t pid;
    Encoder_t encoder;
    motorControlCallback control_callback;

} C602_t;


#endif