#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "sys.h"
#include "rcc.h"
#include "exti.h"
#include "systick.h"
#include "USART/usart.h"
#include "basic_tim.h"
#include "general_tim.h"

void InitAll();
//__IO uint32_t time = 0;
////int mode = 0;
__IO uint32_t val = 500;
int dir = 1;

int main() {

    InitAll();
    GENERAL_TIM_Init();
    Change_Period(50);
    Change_Pluse(2.5);

    GPIO_InitTypeDef Cs;
    Cs.GPIO_Pin = GPIO_Pin_7;
    Cs.GPIO_Mode = GPIO_Mode_Out_PP;
    Cs.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&Cs);

//    Change_Pluse(val);

    while (1) {

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
//    USART_Config(); //串口初始化


}

//void assert_failed(uint8_t* file, uint32_t line)
//{
//    while(1);
//}


