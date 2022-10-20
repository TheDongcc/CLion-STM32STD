#include "key.h"
#include "delay.h"
#include "systick.h"

void KEY_GPIO_Init(){
    //创建GPIO初始化所需的结构体
    GPIO_InitTypeDef GPIOInitStructure;

    //KEY0的初始化
    RCC_APB2PeriphClockCmd(KEY0_GPIO_CLK,ENABLE);
    GPIOInitStructure.GPIO_Pin = KEY0_GPIO_PIN;
    GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY0_GPIO_PORT,&GPIOInitStructure);

    //KEY1的初始化
    RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK,ENABLE);
    GPIOInitStructure.GPIO_Pin = KEY1_GPIO_PIN;
    GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY1_GPIO_PORT,&GPIOInitStructure);

//    //KEY_UP的初始化
//    RCC_APB2PeriphClockCmd(KEY2_GPIO_CLK,ENABLE);
//    GPIOInitStructure.GPIO_Pin = KEY2_GPIO_PIN;
//    GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPD;
//    GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(KEY2_GPIO_PORT,&GPIOInitStructure);

}

uint8_t Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
    if (GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON){
        while (GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON){
//            delay_ms(1);
            Delay_ms(1);
        }
        return KEY_ON;
    } else{
        return KEY_OFF;
    }
}




