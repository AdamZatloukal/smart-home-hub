#ifndef LED_H_
#define LED_H_

#include "led_strip.h"

#define STRIP_GPIO  GPIO_NUM_1

typedef struct
{
    int red;
    int green;
    int blue;
}rgb_color_t;


led_strip_handle_t configure_strip(int num_leds);

void turn_on_all_led(led_strip_handle_t led_strip,int num_of_leds, rgb_color_t color);

#endif