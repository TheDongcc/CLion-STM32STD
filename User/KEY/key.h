#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

//KEY0端口定义
#define KEY0            0
#define KEY0_GPIO_CLK   RCC_APB2Periph_GPIOE
#define KEY0_GPIO_PORT  GPIOE
#define KEY0_GPIO_PIN   GPIO_Pin_4

//KEY1端口定义
#define KEY1            1
#define KEY1_GPIO_CLK   RCC_APB2Periph_GPIOE
#define KEY1_GPIO_PORT  GPIOE
#define KEY1_GPIO_PIN   GPIO_Pin_3

////KEY_UP端口定义
//#define KEY2            2
//#define KEY2_GPIO_CLK   RCC_APB2Periph_GPIOA
//#define KEY2_GPIO_PORT  GPIOA
//#define KEY2_GPIO_PIN   GPIO_Pin_0


//定义按键状态
#define KEY_ON  0
#define KEY_OFF 1

void KEY_GPIO_Init();
uint8_t Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);


#endif
