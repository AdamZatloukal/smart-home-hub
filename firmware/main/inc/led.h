#ifndef LED_H_
#define LED_H_

#include "led_strip.h"

#define STRIP_GPIO  GPIO_NUM_1
#define MAX_LEDS 50

led_strip_handle_t configure_strip(void);

void test_led_strip(void);


#endif