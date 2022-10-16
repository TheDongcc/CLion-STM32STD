#include "exti.h"

// NVIC配置函数
static void EXTI_NVIC_Config(){
    /*按键0的NVIC配置*/
    NVIC_InitTypeDef NVIC_InitStruct;
    // 设置NVIC优先级分组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    // 配置中断源：按键0
    NVIC_InitStruct.NVIC_IRQChannel = KEY0_INT_EXTI_IRQ;
    // 配置抢占优先级
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    // 配置子优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    // 使能中断通道
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    // NVIC初始化
    NVIC_Init(&NVIC_InitStruct);

    /*按键1的NVIC配置*/
    NVIC_InitStruct.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStruct);
}


// 配置EXTI中断
void EXTI_Key_Config(){
    //创建初始化所需的结构体
    GPIO_InitTypeDef GPIOInitStructure;
    EXTI_InitTypeDef EXTI_InitStruct;

    // 配置NVIC
    EXTI_NVIC_Config();

    //KEY0的初始化
    RCC_APB2PeriphClockCmd(KEY0_INT_CLK,ENABLE);
    GPIOInitStructure.GPIO_Pin = KEY0_INT_PIN;
    GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIOInitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(KEY0_INT_PORT,&GPIOInitStructure);

    // 开启AFIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    // 选择GPIO引脚作为EXTI输入线
    GPIO_EXTILineConfig(KEY0_INT_EXTI_PORTSOURCE,KEY0_INT_EXTI_PINSOURCE);

    // 选择需要操作的EXTI线
    EXTI_InitStruct.EXTI_Line = KEY0_INT_EXTI_LINE;
    // 选择模式
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    // 选择中断触发方式
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    // 使能EXTI线
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    // 根据结构体，初始化EXTI
    EXTI_Init(&EXTI_InitStruct);


    /*按键1的EXTI配置*/
    RCC_APB2PeriphClockCmd(KEY1_INT_CLK,ENABLE);
    GPIOInitStructure.GPIO_Pin = KEY1_INT_PIN;
    GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIOInitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(KEY1_INT_PORT,&GPIOInitStructure);

    GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE,KEY1_INT_EXTI_PINSOURCE);
    EXTI_InitStruct.EXTI_Line = KEY1_INT_EXTI_LINE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;

    EXTI_Init(&EXTI_InitStruct);

}

