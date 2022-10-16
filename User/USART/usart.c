#include "usart.h"

//#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#define GETCHAR_PROTOTYPE int __io_getchar(void)

static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 嵌套向量中断控制器组选择 */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

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

    GPIO_InitTypeDef    GPIO_InitStructure;
    USART_InitTypeDef   USART_InitStructure;

    DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK,ENABLE);
    DEBUG_USART_APBxClkCmd(DEBUG_USART_GPIO_CLK,ENABLE);

    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(DEBUG_USARTx,&USART_InitStructure);

    NVIC_Configuration();

    USART_ITConfig(DEBUG_USARTx,USART_IT_RXNE,ENABLE);
    USART_Cmd(DEBUG_USARTx,ENABLE);

}


void USART_SendByte(USART_TypeDef* USARTx,uint8_t data){
    USART_SendData(USARTx,data);
    while (USART_GetFlagStatus(USARTx,USART_FLAG_TXE) == RESET){
    }
}


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

void USART_SendArray(USART_TypeDef* USARTx,uint8_t *array,uint8_t num){
    for (int i = 0; i < num; ++i) {
        USART_SendByte(USARTx,array[i]);
    }
    while (USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET){
    }
}

void USART_SendString(USART_TypeDef* USARTx,const uint8_t *str){
    uint8_t i = 0;
    do {
        USART_SendByte(USARTx,*(str+i));
        i++;
    } while (*(str+i) != '\0');
    while (USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET){
    }
}

//PUTCHAR_PROTOTYPE {
//    USART_SendData(DEBUG_USARTx,(uint8_t) ch);
//    while (USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_TC) == RESET){
//    }
//    return ch;
//}
//
//GETCHAR_PROTOTYPE {
//    while (USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_RXNE) == RESET){
//    }
//    return (int) USART_ReceiveData(DEBUG_USARTx);
//}
