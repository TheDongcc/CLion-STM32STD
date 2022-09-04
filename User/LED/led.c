#include "led.h"

void LED_GPIO_Init(){
    //创建GPIO初始化所需的结构体
    GPIO_InitTypeDef GPIO_InitStruct;

    //LED0的初始化
    RCC_APB2PeriphClockCmd(LED0_GPIO_CLK,ENABLE);
    GPIO_InitStruct.GPIO_Pin = LED0_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED0_GPIO_PORT,&GPIO_InitStruct);

    //LED1的初始化
    RCC_APB2PeriphClockCmd(LED1_GPIO_CLK,ENABLE);
    GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED1_GPIO_PORT,&GPIO_InitStruct);

    //设置LED初始化后为熄灭状态
    GPIO_SetBits(LED0_GPIO_PORT,LED0_GPIO_PIN);
    GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);
}

