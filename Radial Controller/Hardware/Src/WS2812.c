/*
参考:
1. SPI+DMA驱动WS2812
    https://blog.csdn.net/weixin_56719449/article/details/135886089
2. copilot
*/
#include "ws2812.h"
#include <math.h>

uint8_t RGB_BIT_Buffer[RGB_BIT];
uint8_t buffer[RGB_BIT*LED_NUMS];
LEDType LED[LED_NUMS];

/// @brief 将当前 buffer 通过 SPI+DMA 发送到 WS2812 LEDs，如果 SPI 空闲的话
static void WS2812_Update()
{
    // 如果 SPI 正在忙，直接返回，避免重复启动 DMA
    if (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY)
    {
        return;
    }
	HAL_SPI_Transmit_DMA(&hspi1,buffer,RGB_BIT*LED_NUMS);
}

/// @brief 将 RGB 值转换为 WS2812 数据格式，存入 RGB_BIT_Buffer
/// @param R 红色分量，范围 0-255
/// @param G 绿色分量，范围 0-255
/// @param B 蓝色蓝色，范围 0-255
static void WS2812_CreatData(uint8_t R,uint8_t G,uint8_t B)
{
    uint8_t temp[RGB_BIT] = {0};
    for (uint8_t i=0;i<8;i++){
        temp[7-i] =  (G & 0x01) ? WS2812_1 : WS2812_0;
        G = G >> 1;
    }
    for (uint8_t i=0;i<8;i++){
        temp[15-i] =  (R & 0x01) ? WS2812_1 : WS2812_0;
        R = R >> 1;
    }
    for (uint8_t i=0;i<8;i++){
        temp[23-i] =  (B & 0x01) ? WS2812_1 : WS2812_0;
        B = B >> 1;
    }
    memcpy(RGB_BIT_Buffer, temp, RGB_BIT);
}

/// @brief 将 RGB 数组的数据生成发送用的 buffer
static void WS2812_MakeBuffer()
{
	for(uint16_t i=0;i < LED_NUMS;i++)
	{
		WS2812_CreatData(LED[i].R,LED[i].G,LED[i].B);
		memcpy(buffer + i * RGB_BIT, RGB_BIT_Buffer, RGB_BIT);
	}
}

/// @brief 熄灭所有RGB灯
static void WS2812_TurnOff()
{
	for(uint16_t i=0;i<LED_NUMS*24;i++)
	{
		buffer[i]=WS2812_0;
	}
}

/// @brief 设置指定位置LED颜色
/// @param color 颜色值，格式 0xRGB，每一个颜色分量占 8 位
/// @param Pos LED 位置，范围 0 到 LED_NUMS-1
static void WS2812_Color_Pos(uint32_t color,uint16_t Pos)
{
	uint8_t R,G,B;
	uint16_t i;

	R=(color >> 16 ) & 0x00FF;
	G=(color >> 8  ) & 0x0000FF;
	B=(color 	   ) & 0x000000FF;

	WS2812_CreatData(R,G,B);
	
	if(Pos < LED_NUMS && Pos >=0)
	{
		memcpy(buffer + RGB_BIT * Pos, RGB_BIT_Buffer,RGB_BIT);
	}
	else
	{
		WS2812_TurnOff();
	}
}

/// @brief 将 HSV 颜色空间转换为 RGB 颜色空间
/// @param h 色相，范围 0-359
/// @param s 饱和度，范围 0-255
/// @param v 亮度，范围 0-255
/// @param R 指向存储红色分量的指针
/// @param G 指向存储绿色分量的指针
/// @param B 指向存储蓝色分量的指针
static void WS2812_HSV2RGB(uint16_t h, uint8_t s, uint8_t v,
                           uint8_t* R, uint8_t* G, uint8_t* B)
{
    float C = v / 255.0f * s / 255.0f;
    float X = C * (1 - fabsf(fmodf(h / 60.0f, 2) - 1));
    float m = v / 255.0f - C;

    float r, g, b;

    if      (h < 60)  { r=C; g=X; b=0; }
    else if (h < 120) { r=X; g=C; b=0; }
    else if (h < 180) { r=0; g=C; b=X; }
    else if (h < 240) { r=0; g=X; b=C; }
    else if (h < 300) { r=X; g=0; b=C; }
    else              { r=C; g=0; b=X; }

    *R = (uint8_t)((r + m) * 255);
    *G = (uint8_t)((g + m) * 255);
    *B = (uint8_t)((b + m) * 255);
}

/// @brief 仅颜色旋转：亮度固定由 max_brightness 控制，色相步进由 hue_speed 控制
/// @param max_brightness 最大亮度，范围 0-255
/// @param hue_speed 色相变化速度，范围 1-255
void WS2812_Rotating_Update(uint8_t max_brightness, uint8_t hue_speed)
{
    static uint32_t step = 0;  // 色相时基

    // 参数约束
    // 允许 0 亮度（全灭）；如需最小亮度可改成 if (max_brightness==0) max_brightness=1;
    if (hue_speed == 0) hue_speed = 1;  // 0 会导致不旋转，这里将其视为 1

    const uint16_t HUE_OFFSET_PER_LED = (360 / LED_NUMS); // 相邻灯的色相偏移
    uint16_t baseHue = (uint16_t)((step * (uint32_t)hue_speed) % 360);

    for (uint8_t i = 0; i < LED_NUMS; i++) {
        uint16_t ledHue = (baseHue + i * HUE_OFFSET_PER_LED) % 360;

        uint8_t R, G, B;
        WS2812_HSV2RGB(ledHue, 255, max_brightness, &R, &G, &B);

        LED[i].R = R;
        LED[i].G = G;
        LED[i].B = B;
    }

    step++;                // 推进色相
    WS2812_MakeBuffer();
    WS2812_Update();
}
