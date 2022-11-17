#include "general_tim.h"

// 中断优先级配置
static void GENERAL_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    // 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQ;
    // 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void GENERAL_TIM_Mode_Config(void){
    GPIO_InitTypeDef GPIO_InitStructure;

    // 输出比较通道1 GPIO 初始化
    RCC_APB2PeriphClockCmd(GENERAL_TIM_CH1_GPIO_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GENERAL_TIM_CH1_PORT, &GPIO_InitStructure);

    // TIM时钟使能
    GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK,ENABLE);

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    // 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;
    // 驱动CNT计数器的时钟 = Fck_int/(psc+1)
    TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;
    // 时钟分频因子 ，配置死区时间时需要用到
//    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    // 计数器计数模式，设置为向上计数
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    // 重复计数器的值，没用到不用管
//    TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
    // 初始化定时器
    TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);

    TIM_OCInitTypeDef  TIM_OCInitStructure;
    // 配置为PWM模式1
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    // 输出使能
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    // 输出通道电平极性配置
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    // 输出比较通道 1
    TIM_OCInitStructure.TIM_Pulse = Pulse_Value;

    TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
    TIM_Cmd(GENERAL_TIM, ENABLE);
}
uint32_t temp = 0;
// 改变PWM频率，范围：5~3000Hz，VAL为赫兹数
void Change_Period(uint32_t VAL){
    temp = ((10000 / VAL) * 10) - 1;

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period=temp;
    TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;

    TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
}
uint32_t Pluse = 0;
// 改变PWM的占空比，VAL为占空比的百分比数,范围：0~100
void Change_Pluse(float VAL){
    Pluse = (temp * VAL) / 100;

    TIM_OCInitTypeDef  TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = Pluse;

    TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);
}

void GENERAL_TIM_Init(){
    GENERAL_TIM_NVIC_Config();
    GENERAL_TIM_Mode_Config();
}

