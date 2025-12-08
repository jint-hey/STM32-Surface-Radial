#ifndef _MYENCODER_H
#define _MYENCODER_H

#include "main.h"

#define Encoder_K_PIN_LEVEL HAL_GPIO_ReadPin(Encoder_K_GPIO_Port, Encoder_K_Pin)

extern TIM_HandleTypeDef htim2;


int16_t Encoder_Get_Div4(void);
void Encoder_Get_Num(void);

#endif
