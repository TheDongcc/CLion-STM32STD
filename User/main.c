#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "sys.h"
#include "rcc.h"
#include "exti.h"
#include "systick.h"
#include "USART/usart.h"


void InitAll();

int main(){

    InitAll();

    while(1){


    }

}

void InitAll(){
    Delay_Init();   //延时初始化函数
    LED_GPIO_Init();    //LED灯所用GPIO初始化
    KEY_GPIO_Init();    //按键所需GPIO初始化
//    EXTI_Key_Config();  //EXTI及其所用GPIO的初始化
//    HSE_SetSysClk(RCC_PLLMul_9);    //设置HSE时钟
//    HSI_SetSysClk(RCC_PLLMul_16);   //设置HSI时钟
//    MCO_GPIO_Config(RCC_MCO_HSE);   //MCO输出配置
    USART_Config(); //串口初始化

}

//void assert_failed(uint8_t* file, uint32_t line)
//{
//    while(1);
//}
