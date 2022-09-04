#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

//LED0端口定义
#define LED0_GPIO_CLK   RCC_APB2Periph_GPIOB
#define LED0_GPIO_PORT  GPIOB
#define LED0_GPIO_PIN   GPIO_Pin_5

//LED1端口定义
#define LED1_GPIO_CLK   RCC_APB2Periph_GPIOE
#define LED1_GPIO_PORT  GPIOE
#define LED1_GPIO_PIN   GPIO_Pin_5

#define ON  0
#define OFF 1

#define LED0(a) if(a){GPIO_SetBits(LED0_GPIO_PORT,LED0_GPIO_PIN);} \
                else{GPIO_ResetBits(LED0_GPIO_PORT,LED0_GPIO_PIN);}

#define LED1(a) if(a){GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);} \
                else{GPIO_ResetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);}

//LED状态切换
#define DigitalToggle(p,i)  {p->ODR ^= i;}
#define LED0_Toggle     DigitalToggle(LED0_GPIO_PORT,LED0_GPIO_PIN)
#define LED1_Toggle     DigitalToggle(LED1_GPIO_PORT,LED1_GPIO_PIN)

void LED_GPIO_Init();

#endif
