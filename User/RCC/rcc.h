#ifndef __RCC_H
#define __RCC_H

#include "stm32f10x.h"


void HSE_SetSysClk(uint32_t RCC_PLLMul_x);
void HSI_SetSysClk(uint32_t RCC_PLLMul_x);
void MCO_GPIO_Config(uint8_t RCC_MCO);

#endif