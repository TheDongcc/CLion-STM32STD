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
//            while (Key_Scan(KEY0_GPIO_PORT,KEY0_GPIO_PIN) == KEY_ON);
            LED0_Toggle;
//            delay_ms(100);
        }else{

        }
    }

}



