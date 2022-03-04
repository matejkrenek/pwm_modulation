#include "gpio.c"

Button B0_state = {0, 0, 10};
Button B1_state = {0, 0, 10};
PWM pwm = {125, 0};

void main(void)
{
    gpio.deinit();
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    gpio.init(GPIOB, GPIO_PIN_0, GPIO_MODE_IN_PU_IT);
    gpio.init(GPIOB, GPIO_PIN_1, GPIO_MODE_IN_PU_IT);
    gpio.init(GPIOB, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_SLOW);

    while (1)
    {
        if(gpio.read(GPIOB, GPIO_PIN_0)) {
            B0_state.now = 1;
        } else {
            B0_state.now = 0;
        }

        if(gpio.read(GPIOB, GPIO_PIN_1)) {
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
            gpio.high(GPIOB, GPIO_PIN_2);
        } else {
            gpio.low(GPIOB, GPIO_PIN_2);
        }

        delay(50);
        pwm.counter += 1;
        B0_state.prev = B0_state.now;
        B1_state.prev = B1_state.now;
    }
}
