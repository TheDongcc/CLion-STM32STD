#include "rcc.h"

// HSE时钟设置函数
void HSE_SetSysClk(uint32_t RCC_PLLMul_x){
    // HSE启动状态变量
    ErrorStatus HSEStartUpStatus;
    // 复位RCC时钟配置到初始状态
    RCC_DeInit();
    // 使能HSE，配置外部晶振
    RCC_HSEConfig(RCC_HSE_ON);
    // 等待HSE启动完成
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    // HSE启动稳定后继续执行
    if (HSEStartUpStatus == SUCCESS){
        // 使能FLASH预取缓冲区
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        // SYSCLK周期与闪存访问时间的比例，参照Flash编程手册ACR寄存器
        // 0：0 < SYSCLK <= 24M
        // 1：24< SYSCLK <= 48M
        // 2：48< SYSCLK <= 72M
        FLASH_SetLatency(FLASH_Latency_2);
        // AHB预分频因子设置为1分频，HCLK = SYSCLK
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        // APB1预分频因子设置为2分频，PCLK1 = HCLK/2
        RCC_PCLK1Config(RCC_HCLK_Div2);
        // APB2预分频因子设置为1分频，PCLK2 = HCLK
        RCC_PCLK2Config(RCC_HCLK_Div1);
        // 设置PLL时钟来源为HSE，设置PLL倍频因子
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_x);
        // 开启PLL
        RCC_PLLCmd(ENABLE);
        // 等待 PLL稳定
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){}
        // 当PLL稳定之后，把PLL时钟作为系统时钟SYSCLK源
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        // 读取时钟切换状态位，确保PLLCLK被选为系统时钟源
        while (RCC_GetSYSCLKSource() != (uint8_t)0x08){}

    } else{
        //HSE启动失败后的执行代码区
    }

}

// HSI时钟设置函数
void HSI_SetSysClk(uint32_t RCC_PLLMul_x){
    // HSI启动状态变量
    FlagStatus HSIStartUpStatus;
    // 复位RCC时钟配置到初始状态
    RCC_DeInit();
    // 使能HSI
    RCC_HSICmd(ENABLE);
    // 等待HSI启动完成
    do {
        HSIStartUpStatus = RCC_GetFlagStatus(RCC_FLAG_HSIRDY);
    } while (HSIStartUpStatus == RESET);

    // HSI启动稳定后继续执行
    if (HSIStartUpStatus == SET){
        // 使能FLASH预取缓冲区
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        // SYSCLK周期与闪存访问时间的比例，参照Flash编程手册ACR寄存器
        // 0：0 < SYSCLK <= 24M
        // 1：24< SYSCLK <= 48M
        // 2：48< SYSCLK <= 72M
        FLASH_SetLatency(FLASH_Latency_2);
        // AHB预分频因子设置为1分频，HCLK = SYSCLK
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        // APB1预分频因子设置为2分频，PCLK1 = HCLK/2
        RCC_PCLK1Config(RCC_HCLK_Div2);
        // APB2预分频因子设置为1分频，PCLK2 = HCLK
        RCC_PCLK2Config(RCC_HCLK_Div1);
        // 设置PLL时钟来源为HSE，设置PLL倍频因子
        RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_x);
        // 开启PLL
        RCC_PLLCmd(ENABLE);
        // 等待 PLL稳定
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){}
        // 当PLL稳定之后，把PLL时钟作为系统时钟SYSCLK源
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        // 读取时钟切换状态位，确保PLLCLK被选为系统时钟源
        while (RCC_GetSYSCLKSource() != (uint8_t)0x08){}

    } else{
        //HSE启动失败后的执行代码区
    }

}
/**
  * @brief  Configure the MCO pin and Selects the clock source to output on MCO pin.
  * @param  RCC_MCO: specifies the clock source to output.
  *     @arg RCC_MCO_NoClock: No clock selected
  *     @arg RCC_MCO_SYSCLK: System clock selected
  *     @arg RCC_MCO_HSI: HSI oscillator clock selected
  *     @arg RCC_MCO_HSE: HSE oscillator clock selected
  *     @arg RCC_MCO_PLLCLK_Div2: PLL clock divided by 2 selected
  * @retval None
  */
void MCO_GPIO_Config(uint8_t RCC_MCO){
    // MCO位于PA8引脚复用
    // 创建MCO_GPIO初始化所需的结构体
    GPIO_InitTypeDef GPIOInitStructure;

    // MCO的初始化
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_IOPAEN,ENABLE);
    GPIOInitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIOInitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //注意使用复用推完
    GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIOInitStructure);

    //选择相应的时钟源进行输出
    RCC_MCOConfig(RCC_MCO);
}
