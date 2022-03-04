#include "stm8s.h"

#define len(arr) sizeof(arr)/sizeof(arr[0])

void delay(uint32_t iterations)
{
    for(uint32_t i = 0; i < iterations; i++);
}

typedef struct {
    bool prev, now;
    uint8_t power;
} Button;

typedef struct {
    uint8_t led, counter;
} PWM;

typedef struct {
    void (*init)(GPIO_TypeDef*, GPIO_Pin_TypeDef, GPIO_Mode_TypeDef);
    void (*low)(GPIO_TypeDef*, GPIO_Pin_TypeDef);
    void (*high)(GPIO_TypeDef*, GPIO_Pin_TypeDef);
    void (*reverse)(GPIO_TypeDef*, GPIO_Pin_TypeDef);
    int (*read)(GPIO_TypeDef*, GPIO_Pin_TypeDef);
    void (*deinit)();
} GPIO;

void pin_init(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin, GPIO_Mode_TypeDef mode) {
    GPIO_Init(port, pin, mode);
}

void pin_low(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin) {
    port->ODR &= (uint8_t)(~pin);
}

void pin_high(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin) {
    port->ODR |= (uint8_t)pin;
}

void pin_reverse(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin) {
    port->ODR ^= (uint8_t)pin;
}

int pin_read(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin) {
    switch (GPIO_ReadInputPin(port, pin)) {
        case RESET:
            return 1;
        default:
            return 0;
    }
}

void deinit() {
    GPIO_DeInit(GPIO_PIN_ALL);
}

GPIO gpio = {
    .init = pin_init,
    .low = pin_low,
    .high = pin_high,
    .reverse = pin_reverse,
    .read = pin_read,
    .deinit = deinit
};