#ifndef __EXTI_H
#define __EXTI_H

#include "stm32f10x.h"

//KEY0端口定义
#define KEY0_INT_CLK                RCC_APB2Periph_GPIOE
#define KEY0_INT_PORT               GPIOE
#define KEY0_INT_PIN                GPIO_Pin_4
#define KEY0_INT_EXTI_PORTSOURCE    GPIO_PortSourceGPIOE
#define KEY0_INT_EXTI_PINSOURCE     GPIO_PinSource4
#define KEY0_INT_EXTI_LINE          EXTI_Line4
#define KEY0_INT_EXTI_IRQ           EXTI4_IRQn
#define KEY0_IRQHandler             EXTI4_IRQHandler

//KEY0端口定义
#define KEY1_INT_CLK                RCC_APB2Periph_GPIOE
#define KEY1_INT_PORT               GPIOE
#define KEY1_INT_PIN                GPIO_Pin_3
#define KEY1_INT_EXTI_PORTSOURCE    GPIO_PortSourceGPIOE
#define KEY1_INT_EXTI_PINSOURCE     GPIO_PinSource3
#define KEY1_INT_EXTI_LINE          EXTI_Line3
#define KEY1_INT_EXTI_IRQ           EXTI3_IRQn
#define KEY1_IRQHandler             EXTI3_IRQHandler

void EXTI_Key_Config();

#endif
