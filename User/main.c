#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

int main(){
    LED_GPIO_Init();
    delay_init();
//    LED0(ON);
//    LED1(ON);
    while (1){
//        LED0_Toggle;
//        delay_ms(100);
    }

}



