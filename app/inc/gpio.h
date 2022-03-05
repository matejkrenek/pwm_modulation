#include "stm8s.h"

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
} GPIO;

void gpio_init(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin, GPIO_Mode_TypeDef mode);
void gpio_low(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin);
void gpio_high(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin);
void gpio_reverse(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin);
int gpio_read(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin);

GPIO gpio = {
    .init = gpio_init,
    .low = gpio_low,
    .high = gpio_high,
    .reverse = gpio_reverse,
    .read = gpio_read,
};