#include "usart.h"
#include "stdio.h"

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)

static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 嵌套向量中断控制器组选择 */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* 配置USART为中断源 */
    NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
    /* 抢断优先级*/
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    /* 子优先级 */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    /* 使能中断 */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    /* 初始化配置NVIC */
    NVIC_Init(&NVIC_InitStructure);
}

void USART_Config(){
    // 加此句后 printf函数不加'\n'也能输出
    setvbuf(stdout,NULL,_IONBF,0);

    GPIO_InitTypeDef    GPIO_InitStructure;
    USART_InitTypeDef   USART_InitStructure;

    // 开USART时钟 开所用到的GPIO时钟
    DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK,ENABLE);
    DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK,ENABLE);

    // 配置USART TX的IO
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

    // 配置USART RX的IO
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

    // 配置串口工作参数
    USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    // 串口初始化
    USART_Init(DEBUG_USARTx,&USART_InitStructure);

    // 串口中断的配置
    NVIC_Configuration();
    // 开启串口"接收"中断
    USART_ITConfig(DEBUG_USARTx,USART_IT_RXNE,ENABLE);

    // 使能串口
    USART_Cmd(DEBUG_USARTx,ENABLE);
}

/*  发送一个字节  */
void USART_SendByte(USART_TypeDef* USARTx,uint8_t data){
    USART_SendData(USARTx,data);
    while (USART_GetFlagStatus(USARTx,USART_FLAG_TXE) == RESET){
    }
}

/*  同时发送两个字节  */
void USART_SendHalfWord(USART_TypeDef* USARTx,uint16_t data){
    uint8_t data_h,data_l;
    data_h = (data & 0xFF00)>>8;
    data_l = data & 0x00FF;
    USART_SendData(USARTx,data_h);
    while (USART_GetFlagStatus(USARTx,USART_FLAG_TXE) == RESET){
    }
    USART_SendData(USARTx,data_l);
    while (USART_GetFlagStatus(USARTx,USART_FLAG_TXE) == RESET){
    }
}

/*  发送8位数组  */
void USART_SendArray(USART_TypeDef* USARTx,uint8_t *array,uint8_t num){
    for (int i = 0; i < num; ++i) {
        USART_SendByte(USARTx,array[i]);
    }
    while (USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET){
    }
}

/*  发送字符串  */
void USART_SendString(USART_TypeDef* USARTx,const uint8_t *str){
    uint8_t i = 0;
    do {
        USART_SendByte(USARTx,*(str + i));
        i++;
    } while (*(str + i) != '\0');
    while (USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET){
    }
}

// printf函数重定义
PUTCHAR_PROTOTYPE {
    USART_SendData(DEBUG_USARTx,(uint8_t) ch);
    while (USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_TC) == RESET){
    }
    return ch;
}

// 此处未重定义成功,请勿使用!!!
GETCHAR_PROTOTYPE {
    while (USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_RXNE) == RESET){
    }
    return (int) USART_ReceiveData(DEBUG_USARTx);
}

