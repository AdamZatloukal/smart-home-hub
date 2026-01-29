#ifndef MAIN_H_
#define MAIN_H_

/* add cpp compilation (ws2812fx is cpp)*/
#ifdef __cplusplus
extern "C" {
#endif

#include "led_strip.h"
#include "WS2812FX.h"

extern WS2812FX *fx;

#define MAX_LEDS 20

/* GLOBAL VARIABLES - defined in main.c */
extern led_strip_handle_t led_strip;        // handle to led strip 
extern int num_leds;                        // number of leds on the strip
extern TaskHandle_t task_read_mic_handle;

void read_mic(void *parameter); // RTOS task
void fx_loop(void *parameter);
void wifi_webserver(void *parameter);


#ifdef __cplusplus
}
#endif

#endif