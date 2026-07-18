#include "MyTask.h"
#include "MyEncoder.h"
#include "MyLED.h"
#include "WS2812.h"
#include "MyDial.h"
#include "usb_device.h"

static uint8_t press_flag = 0x00;
extern volatile uint8_t ws2812_update_flag;

/// @brief 处理编码器旋转和按键按下/释放
void ProcessEncoderAndButton(void)
{
    int16_t Encoder_Dir = Encoder_Get_Div4();

    // 正转
    if (Encoder_Dir == 1 && press_flag == 0x00)
    {
        USBD_HID_SendData(200);
        User_LED_Toggle();
    }
    // 反转
    if (Encoder_Dir == -1 && press_flag == 0x00)
    {
        USBD_HID_SendData(-200);
        User_LED_Toggle();
    }

    // 按下
    if (HAL_GPIO_ReadPin(Encoder_K_GPIO_Port, Encoder_K_Pin) == 0 && press_flag == 0x00)
    {
        press_flag = 0xff;
        USBD_HID_SendData(1);
        User_LED_Toggle();
    }
    // 释放
    if (HAL_GPIO_ReadPin(Encoder_K_GPIO_Port, Encoder_K_Pin) == 1 && press_flag == 0xff)
    {
        press_flag = 0x00;
        USBD_HID_SendData(0);
        User_LED_Toggle();
    }
}

/// @brief 在主循环中执行RGB灯旋转更新
void ProcessRGBUpdate(void)
{
    if (ws2812_update_flag)
    {
        ws2812_update_flag = 0;
        WS2812_Rotating_Update(80, 2); // 亮度100，色相速度2
    }
}
