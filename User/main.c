#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"


int main(){
    LED_GPIO_Init();
    KEY_GPIO_Init();
    delay_init();


    while (1){

        if (Key_Scan(KEY0_GPIO_PORT,KEY0_GPIO_PIN) == KEY_ON){
            LED0_Toggle;
        }else if (Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON){
            LED1_Toggle;
        }
    }

}



