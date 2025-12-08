#ifndef INC_WS2812_H_
#define INC_WS2812_H_

#include "string.h"
#include "main.h"
#include "spi.h"

#define	WS2812_0	0xC0
#define	WS2812_1	0xF0
#define	WS2812_RST	0x00
#define LED_NUMS   	4
#define RGB_BIT   	24

typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
}LEDType;

static void WS2812_Update(void);

static void WS2812_CreatData(uint8_t R,uint8_t G,uint8_t B);

static void WS2812_MakeBuffer();

static void WS2812_TurnOff(void);

static void WS2812_Color_Pos(uint32_t color, uint16_t Pos);

static void WS2812_HSV2RGB(uint16_t h, uint8_t s, uint8_t v,
                           uint8_t* R, uint8_t* G, uint8_t* B);

/* 仅颜色旋转：亮度固定由 max_brightness 控制，色相步进由 hue_speed 控制 */
void WS2812_Rotating_Update(uint8_t max_brightness, uint8_t hue_speed);

#endif /* INC_WS2812_H_ */
