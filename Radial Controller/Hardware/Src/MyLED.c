#include "MyLED.h"

/// @brief 点亮用户LED
/// @param  
void User_LED_ON(void)
{
    HAL_GPIO_WritePin(User_LED_GPIO_Port, User_LED_Pin, GPIO_PIN_RESET);
}

/// @brief 熄灭用户LED
/// @param  
void User_LED_OFF(void)
{
    HAL_GPIO_WritePin(User_LED_GPIO_Port, User_LED_Pin, GPIO_PIN_SET);
}

/// @brief 切换用户LED状态
/// @param
void User_LED_Toggle(void)
{
    HAL_GPIO_TogglePin(User_LED_GPIO_Port, User_LED_Pin);
}