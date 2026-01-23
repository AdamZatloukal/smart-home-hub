#ifndef LED_H_
#define LED_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "led_strip.h"

#define STRIP_GPIO  GPIO_NUM_1

#define RGB_TO_HEX(red, green, blue) (((red & 0xFF) << 16) | ((green & 0xFF) << 8) | (blue & 0xFF))
#define HEX_TO_RGB(hex, r, g, b) \
    do { \
        (r) = ((hex) >> 16) & 0xFF; \
        (g) = ((hex) >> 8) & 0xFF; \
        (b) = (hex) & 0xFF; \
    } while (0)

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}rgb_color_t;

led_strip_handle_t configure_strip(int num_leds);

void turn_on_all_led(led_strip_handle_t led_strip,int num_of_leds, rgb_color_t color);

#ifdef __cplusplus
}
#endif

#endif