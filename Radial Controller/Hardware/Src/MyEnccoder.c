#include "MyEncoder.h"

int16_t Encoder_Num = 0;

/// @brief 获取编码器计数的变化量（除以 4 后输出）。并且会清掉已消耗的那部分计数，只保留余数（防止重复计算）。

/// @param  
/// @return 返回编码器计数变化的格数（每转一格对应编码器 4 个脉冲）。可能为+1、-1或 0。
int16_t Encoder_Get_Div4(void)
{
    int16_t temp = __HAL_TIM_GET_COUNTER(&htim2); // 踩坑记录:TIM_GetCounter()返回无符号16位整数, 赋值给有符号整型前不要做运算

    //配置编码器时，每转一格会产生 4 个计数脉冲，因此这里除以 4 输出实际的“格数”变化。
    //如果 temp 在 -3 ～ 3 之间，temp / 4 为 0 → 表示计数还不够 4 个，不认为用户转动了一格。
    //如果 temp ≥ 4 或 ≤ -4，则 temp / 4 至少为 ±1，说明用户有转动。
    if (temp / 4)
    {
        __HAL_TIM_SET_COUNTER(&htim2, temp % 4);
        /*
        temp % 4 是取余操作：
        比如累计计数 temp = 10，10 / 4 = 2（返回 2 步），10 % 4 = 2（还剩 2 个脉冲没凑够一整步）。
        函数返回 2 步之后，把计数器置为 2，下次就继续从 2 开始累加。
        这样可以保证每个计数“只用一次”，不会重复统计。
        */
        return temp / 4;
        /*当 temp / 4 != 0 时，直接返回 temp / 4，可能是 1、2、-1、-2 等（取决于一次读取间隔内转了多大步数）。
        否则返回 0，表示“这段时间内转动不足 1 步”。
        */
    }
    else
    {
        return 0;
    }
}

/// @brief 累计编码器的总计数值（每转一格对应编码器 4 个脉冲）。并且会清掉已消耗的那部分计数，只保留余数（防止重复计算）。
/// @param  
void Encoder_Get_Num(void)
{
    int16_t temp = __HAL_TIM_GET_COUNTER(&htim2); // 踩坑记录:TIM_GetCounter()返回无符号16位整数, 赋值给有符号整型前不要做运算
    if ((temp / 4) > 0)
    {
        __HAL_TIM_SET_COUNTER(&htim2, temp % 4);
        Encoder_Num++;
    }
    else if ((temp / 4) < 0)
    {
        __HAL_TIM_SET_COUNTER(&htim2, temp % 4);
        Encoder_Num--;
    }
}
