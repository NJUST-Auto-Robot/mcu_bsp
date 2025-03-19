#include "c602.h"
#include "fdcan.h"

Motor_Controller_struct motor_3508_instnce[8];

uint8_t motor_current_data[8];

static void motor_set_current(uint8_t id)
{
    if (MOTOR_STOP == motor_3508_instnce[id].motor_cofig.motor_enable_flag)
    {
        motor_3508_instnce[id].set.current = 0;
        return;
    }
    else
    {
        // if (motor_3508_instnce[id].motor_lim_cofig)
        // {
        //     motor_3508_instnce[0].set.current = -motor_3508_instnce[0].set.current;
        // }

        if (MOTOR_DIRECTION_REVERSE == motor_3508_instnce[id].motor_cofig.motor_reverse_flag)
        {
            motor_3508_instnce[id].set.current = -motor_3508_instnce[0].set.current;
        }
    }
}
void C602_Set_Current_1_4(void)
{
    motor_set_current(0);
    motor_set_current(1);
    motor_set_current(2);
    motor_set_current(3);


    // 手册有说明，该段表示1-2号继电器得电，45-48号继电器得电。
    motor_current_data[0] = (int16_t)motor_3508_instnce[0].set.current >> 8;
    motor_current_data[1] = (int16_t)motor_3508_instnce[0].set.current;
    motor_current_data[2] = (int16_t)motor_3508_instnce[1].set.current >> 8;
    motor_current_data[3] = (int16_t)motor_3508_instnce[1].set.current;
    motor_current_data[4] = (int16_t)motor_3508_instnce[2].set.current >> 8;
    motor_current_data[5] = (int16_t)motor_3508_instnce[2].set.current;
    motor_current_data[6] = (int16_t)motor_3508_instnce[3].set.current >> 8;
    motor_current_data[7] = (int16_t)motor_3508_instnce[3].set.current;

    FDCAN1_Send_Msg(0x200, motor_current_data);
}

void C602_Set_Current_5_8(void)
{
    motor_set_current(4);
    motor_set_current(5);
    motor_set_current(6);
    motor_set_current(7);
    

    // 手册有说明，该段表示1-2号继电器得电，45-48号继电器得电。
    motor_current_data[0] = (int16_t)motor_3508_instnce[4].set.current >> 8;
    motor_current_data[1] = (int16_t)motor_3508_instnce[4].set.current;
    motor_current_data[2] = (int16_t)motor_3508_instnce[5].set.current >> 8;
    motor_current_data[3] = (int16_t)motor_3508_instnce[5].set.current;
    motor_current_data[4] = (int16_t)motor_3508_instnce[6].set.current >> 8;
    motor_current_data[5] = (int16_t)motor_3508_instnce[6].set.current;
    motor_current_data[6] = (int16_t)motor_3508_instnce[7].set.current >> 8;
    motor_current_data[7] = (int16_t)motor_3508_instnce[7].set.current;

    FDCAN1_Send_Msg(0x1FF, motor_current_data);
}

void C602_Get_Info(uint32_t id, uint8_t *data)
{
    switch (id)
    {
    case 0x201:
    {
        motor_3508_instnce[0].get.deg_pos = (data[0] << 8) + data[1];
        motor_3508_instnce[0].get.velocity = (data[2] << 8) + data[3];
        motor_3508_instnce[0].get.current = (data[4] << 8) + data[5];
        break;
    }
    case 0x202:
    {
        motor_3508_instnce[1].get.deg_pos = (data[0] << 8) + data[1];
        motor_3508_instnce[1].get.velocity = (data[2] << 8) + data[3];
        motor_3508_instnce[1].get.current = (data[4] << 8) + data[5];
        break;
    }
    case 0x203:
    {
        motor_3508_instnce[2].get.deg_pos = (data[0] << 8) + data[1];
        motor_3508_instnce[2].get.velocity = (data[2] << 8) + data[3];
        motor_3508_instnce[2].get.current = (data[4] << 8) + data[5];
        break;
    }
    case 0x204:
    {
        motor_3508_instnce[3].get.deg_pos = (data[0] << 8) + data[1];
        motor_3508_instnce[3].get.velocity = (data[2] << 8) + data[3];
        motor_3508_instnce[3].get.current = (data[4] << 8) + data[5];
        break;
    }
    }
}
