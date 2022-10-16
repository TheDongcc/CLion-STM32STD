#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"
#include "core_cm3.h"

void Delay_Init();
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);


#endif
