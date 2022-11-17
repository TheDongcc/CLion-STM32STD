#ifndef __GENERAL_TIM_H
#define __GENERAL_TIM_H

#include "stm32f10x.h"


//计数一次时间（中断间隔时间）为： TIM_Period * PSC
//例：72M时钟，PSC（分频倍数）为72，TIM_Period（自动重装载值）为100，则计数一次时间为100us
//可使用中断来增加计数时间

#define            GENERAL_TIM                   TIM3
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM3
#define 		   TIM_ARR					     10	//自动重装载的值(1~65536)
#define            GENERAL_TIM_Period            (TIM_ARR - 1)
#define    		   PSC							 720		//分频倍数 (1~65536)
#define            GENERAL_TIM_Prescaler         (PSC - 1)
#define            Pulse_Value                   5
#define            GENERAL_TIM_IRQ               TIM3_IRQn
#define            GENERAL_TIM_IRQHandler        TIM3_IRQHandler

// TIM3 输出比较通道1
#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH1_PORT          GPIOA
#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_6

// TIM3 输出比较通道2
#define            GENERAL_TIM_CH2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH2_PORT          GPIOA
#define            GENERAL_TIM_CH2_PIN           GPIO_Pin_7

// TIM3 输出比较通道3
#define            GENERAL_TIM_CH3_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM_CH3_PORT          GPIOB
#define            GENERAL_TIM_CH3_PIN           GPIO_Pin_0

// TIM3 输出比较通道4
#define            GENERAL_TIM_CH4_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM_CH4_PORT          GPIOB
#define            GENERAL_TIM_CH4_PIN           GPIO_Pin_1

void Change_Period(uint32_t VAL);
void Change_Pluse(float VAL);
void GENERAL_TIM_Init();

#endif
