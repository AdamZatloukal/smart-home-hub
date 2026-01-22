#ifndef MAIN_H_
#define MAIN_H_

#include "led_strip.h"

#define MAX_LEDS 50

/* GLOBAL VARIABLES - defined in main.c */
extern led_strip_handle_t led_strip;        // handle to led strip 
extern int num_leds;                        // number of leds on the strip

#endif