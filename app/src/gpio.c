#include "gpio.h"
#include "stm8s.h"

void gpio_init(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin, GPIO_Mode_TypeDef mode){
    GPIO_Init(port, pin, mode);
}

void gpio_low(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin) {
    port->ODR &= (uint8_t)(~pin);
}

void gpio_high(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin) {
    port->ODR |= (uint8_t)pin;
}

void gpio_reverse(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin) {
    port->ODR ^= (uint8_t)pin;
}

int gpio_read(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin) {
    switch (GPIO_ReadInputPin(port, pin)) {
        case RESET:
            return 1;
        default:
            return 0;
    }
}