/*
 * @Author: skybase
 * @Date: 2025-01-14 09:45:46
 * @LastEditors: skybase
 * @LastEditTime: 2025-01-14 16:28:02
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \luntui\BSP\button\button.c
 */
#include "button.h"

static int idx;
static ButtonInstance *button_instance[BUTTON_NUM] = {0};

/**
 * @brief 使用HAL库对按键信息进行更新
 *
 * @note 根据不同单片机用户自己定义
 */
static void buttons_Check(void)
{
    for (int i = 0; i < idx; i++)
    {
        button_instance[i]->key_state = HAL_GPIO_ReadPin(button_instance[i]->GpioPort, button_instance[i]->GpioPin);
    }
}

void button_Init(ButtonInstance *_instance,
                 GPIO_TypeDef *GpioPort,
                 uint32_t GpioPin,
                 TRIGGER_LEVEL trigger_level,
                 button_module_callback button_down_callback,
                 button_module_callback button_continue_callback,
                 button_module_callback button_up_callback)
{
    memset(_instance, 0, sizeof(ButtonInstance));
    _instance->id = idx++;

    _instance->GpioPort = GpioPort;
    _instance->GpioPin = GpioPin;
    _instance->trigger_level = trigger_level;
    _instance->button_down_callback = button_down_callback;
    _instance->button_continue_callback = button_continue_callback;
    _instance->button_up_callback = button_up_callback;
}

static void button_Callback(void)
{
    for (int i = 0; i < idx; i++)
    {
        if (button_instance[i]->button_down_callback != NULL && button_instance[i]->press_state == BT_Down)
        {
            button_instance[i]->button_down_callback()
        }
        else if (button_instance[i]->button_continue_callback != NULL && button_instance[i]->press_state == BT_Pressing)
        {
            button_instance[i]->button_continue_callback()
        }
        else if (button_instance[i]->button_up_callback != NULL && button_instance[i]->press_state == BT_Up)
        {
            button_instance[i]->button_up_callback()
        }
    }
}
/**
 * @brief buttons的状态更新函数
 *
 * @param time_base 状态时间时基（ms)
 */
void button_State_Update(int time_base)
{
    ButtonInstance *_instance;

    button_Callback();
    buttons_Check();
    static uint8_t dead_pluse[BUTTON_NUM] = {0};
    static uint8_t cof[BUTTON_NUM] = {0};
    static int button_pressed_cal[BUTTON_NUM] = {0};

    for (int i = 0; i < idx; i++)
    {
        _instance = button_instance[i];

        _instance->key_state = _instance->trigger_level == TRIGGER_LEVEL_HIGH ? _instance->key_state : -_instance->key_state;

        _instance->press_state = BT_NONE;
        if (_instance->key_state && button_pressed_cal[i] == 0 && --dead_pluse[i] <= 0)
        {
            if (cof[i] == 1)
            {
                _instance->press_state = BT_Down;
                button_pressed_cal[i]++;
                return;
            }
            else
            {
                cof[i] = 1;
                return;
            }
        }
        else if (button_pressed_cal[i] > 0)
        {
            _instance->press_state = BT_Pressing;
            button_pressed_cal[i]++;
            _instance->press_time = button_pressed_cal[i] * 1.0 * time_base / 1000;
        }
        if (!_instance->key_state && button_pressed_cal[i] != 0)
        {
            _instance->press_state = BT_Up;
            button_pressed_cal[i] = 0;
            dead_pluse[i] = 3;
            cof[i] = 0;
            return;
        }
    }
}