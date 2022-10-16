#include "systick.h"

static uint32_t E_us = 0;
static uint32_t E_ms = 0;

/*SysTick初始化函数*/
void Delay_Init(){
    // 选择systick的时钟源为HCLK
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);

    // 每微秒/毫秒所需的计时数
    E_us = SystemCoreClock / 8000000;
    E_ms = E_us * 1000;
}

/*  微秒延时函数
 *  最大延时值为 2^24 / 9 = 1,864,135 us = 1864 ms = 1.8 s
 * */
void Delay_us(uint32_t us){
    uint32_t temp;

    // 设置需要计时的微秒数
    SysTick->LOAD = us * E_us;
    // 清空计数器
    SysTick->VAL = 0x00;
    // 使能SysTick定时器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    //开始倒计时
    do {
        temp = SysTick->CTRL;
    } while (temp != 0x10001);//倒计时结束触发条件

    //关闭SysTick计数器
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    // 清空计数器
    SysTick->VAL = 0x00;
}

/*  毫秒延时函数
 *  最大延时值为 2^24 / 9 = 1,864,135 us = 1864 ms = 1.8 s
 * */
void Delay_ms(uint32_t ms){
    uint32_t temp;

    SysTick->LOAD = ms * E_ms;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    do {
        temp = SysTick->CTRL;
    } while (temp != 0x10001);

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0x00;
}


