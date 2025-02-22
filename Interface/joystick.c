/*
 * @Author: skybase
 * @Date: 2024-08-14 00:52:05
 * @LastEditors: skybase
 * @LastEditTime: 2024-11-06 21:42:43
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARM\BSP\Interface\joystick.c
 */
#include "joystick.h"



volatile uint16_t button_state = 0x0000;
volatile uint16_t button_state_extence = 0x0000;
volatile spindle joystick_spin = {0};


void JoystickDataUpdate()
{
    uint32_t _gpio_state_a = LL_GPIO_ReadInputPort(GPIOA);
    uint32_t _gpio_state_b = LL_GPIO_ReadInputPort(GPIOB);
    uint32_t _gpio_state_c = LL_GPIO_ReadInputPort(GPIOC);

    button_state = (!(_gpio_state_a & A_Pin)) ? button_state | A : button_state & ~A;
    button_state = (!(_gpio_state_a & B_Pin)) ? button_state | B : button_state & ~B;
    button_state = (!(_gpio_state_a & BACK_Pin)) ? button_state | Back : button_state & ~Back;
    button_state = (!(_gpio_state_a & DOWM_Pin)) ? button_state | DPadDown : button_state & ~DPadDown;
    button_state = (!(_gpio_state_a & RIGHT_Pin)) ? button_state | DPadRight : button_state & ~DPadRight;
    button_state = (!(_gpio_state_a & START_Pin)) ? button_state | Start : button_state & ~Start;
    button_state_extence = (!(_gpio_state_a & CLEAR_Pin)) ? button_state_extence | Clear : button_state_extence & ~Clear;
    button_state_extence = (!(_gpio_state_a & THRBO_Pin)) ? button_state_extence | Thrbo : button_state_extence & ~Thrbo;
    button_state_extence = (!(_gpio_state_a & HOME_Pin)) ? button_state_extence | Beitong : button_state_extence & ~Beitong;
    button_state_extence = (!(_gpio_state_c & LB_Pin)) ? button_state_extence | LB : button_state_extence & ~LB;
    button_state_extence = (!(_gpio_state_c & RB_Pin)) ? button_state_extence | RB : button_state_extence & ~RB;

    button_state = (!(_gpio_state_b & RS_Pin)) ? button_state | RightShoulder : button_state & ~RightShoulder;
    button_state = (!(_gpio_state_b & LS_Pin)) ? button_state | LeftShoulder : button_state & ~LeftShoulder;

    button_state = (!(_gpio_state_c & RT_Pin)) ? button_state | RightThumb : button_state & ~RightThumb;
    button_state = (!(_gpio_state_c & LT_Pin)) ? button_state | LeftThumb : button_state & ~LeftThumb;
    button_state = (!(_gpio_state_c & X_Pin)) ? button_state | X : button_state & ~X;
    button_state = (!(_gpio_state_c & Y_Pin)) ? button_state | Y : button_state & ~Y;
    button_state = (!(_gpio_state_c & UP_Pin)) ? button_state | DPadUp : button_state & ~DPadUp;
    button_state = (!(_gpio_state_c & LEFT_Pin)) ? button_state | DPadLeft : button_state & ~DPadLeft;

    // 摇杆数据
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_vals, 5);
    joystick_spin.HL = adc_vals[0];
    joystick_spin.VL = adc_vals[1];
    joystick_spin.HR = adc_vals[2];
    joystick_spin.VR = adc_vals[3];
}

// struct dataPack data;
void JoystickDataTransmit()
{
    // data.bs = button_state;
    // data.bse = button_state_extence;
    // data.frame[0] = 0xfe;
    // data.frame[1] = 0xaa;
    // data.sp = joystick_spin;

    // data.ddr8 = 0;
    // uint8_t *dataTemp = (uint8_t *)&data;
    // for (int i = 0; i < sizeof(struct dataToTransmit); i++)
    // {
    //     data.ddr8 += *dataTemp;
    //     dataTemp++;
    // }
    // HAL_UART_Transmit_DMA(&huart1, (uint8_t *)&data, sizeof(struct dataToTransmit));
}

