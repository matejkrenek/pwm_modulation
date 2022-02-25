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

Button B0_state = {0, 0, 10};
Button B1_state = {0, 0, 10};
PWM pwm = {255, 0};

void main(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    GPIO_Init(GPIOB, GPIO_PIN_0, GPIO_MODE_IN_PU_IT);
    GPIO_Init(GPIOB, GPIO_PIN_1, GPIO_MODE_IN_PU_IT);
    GPIO_Init(GPIOB, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_SLOW);

    while (1)
    {
        if(GPIO_ReadInputPin(GPIOB, GPIO_PIN_0) == RESET) {
            B0_state.now = 1;
        } else {
            B0_state.now = 0;
        }

        if(GPIO_ReadInputPin(GPIOB, GPIO_PIN_1) == RESET) {
            B1_state.now = 1;
        } else {
            B1_state.now = 0;
        }

        if(B0_state.now && !B0_state.prev) {
            pwm.led += B0_state.power;

            if(pwm.led >= 255) {
                pwm.led = 0;
            }

            pwm.counter = 0;
        }

        if(B1_state.now && !B1_state.prev) {
            pwm.led -= B1_state.power;

            if(pwm.led <= 0) {
                pwm.led = 255;
            }

            pwm.counter = 0;
        }

        if((pwm.led - pwm.counter) > B1_state.power) {
            GPIO_WriteHigh(GPIOB, GPIO_PIN_2);
        } else {
            GPIO_WriteLow(GPIOB, GPIO_PIN_2);
        }

        delay(50);
        pwm.counter += 1;
        B0_state.prev = B0_state.now;
        B1_state.prev = B1_state.now;
    }
}
