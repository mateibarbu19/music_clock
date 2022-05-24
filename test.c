#include <stdio.h>
#include "pico/stdlib.h"

/* SDCard Dependencies */
#include "f_util.h"
#include "ff.h"
#include "rtc.h"
#include "hw_config.h"

#define delay 250

#define ROTARY_ENCODER_0_A 12
#define ROTARY_ENCODER_0_B 13
#define ROTARY_ENCODER_0_C 11
#define ROTARY_ENCODER_1_A 15
#define ROTARY_ENCODER_1_B 14
#define ROTARY_ENCODER_1_C 10

void button_callback(uint gpio, uint32_t events) {
    if (gpio == ROTARY_ENCODER_0_C) {
        static uint32_t time;

        if (to_ms_since_boot(get_absolute_time()) > time + delay) {
            time = to_ms_since_boot(get_absolute_time());
            puts("Button 0 pressed.");
        }
    }

    if (gpio == ROTARY_ENCODER_1_C) {
        static uint32_t time;

        if (to_ms_since_boot(get_absolute_time()) > time + delay) {
            time = to_ms_since_boot(get_absolute_time());
            puts("Button 1 pressed.");
        }
    }

    if (gpio == ROTARY_ENCODER_0_A) {
        static uint32_t time;

        if (to_ms_since_boot(get_absolute_time()) > time + delay) {
            if(gpio_get(ROTARY_ENCODER_0_B)) {
                puts("CW 0");
            }
            time = to_ms_since_boot(get_absolute_time());
        }
    }

    if (gpio == ROTARY_ENCODER_0_B) {
        static uint32_t time;

        if (to_ms_since_boot(get_absolute_time()) > time + delay) {
            if(gpio_get(ROTARY_ENCODER_0_A)) {
                puts("CCW 0");
            }
            time = to_ms_since_boot(get_absolute_time());
        }
    }

    if (gpio == ROTARY_ENCODER_1_B) {
        static uint32_t time;

        if (to_ms_since_boot(get_absolute_time()) > time + delay) {
            if(gpio_get(ROTARY_ENCODER_1_A)) {
                puts("CCW 1");
            }
            time = to_ms_since_boot(get_absolute_time());
        }
    }

    if (gpio == ROTARY_ENCODER_1_A) {
        static uint32_t time;

        if (to_ms_since_boot(get_absolute_time()) > time + delay) {
            if(gpio_get(ROTARY_ENCODER_1_B)) {
                puts("CW 1");
            }
            time = to_ms_since_boot(get_absolute_time());
        }
    }
}

void buttons_init(void) {
    gpio_set_irq_enabled_with_callback(10, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    for (int i = 10; i <= 15; i++) {
        gpio_init(i);
        gpio_set_dir(i, GPIO_IN);
        gpio_pull_up(i);
        gpio_set_irq_enabled(i, GPIO_IRQ_EDGE_FALL, true);
    }
}

int main() {
    /* Init */
    stdio_init_all();
    time_init();

    buttons_init();

    while (1) {
        puts("---");
        sleep_ms(250);
    }
}
