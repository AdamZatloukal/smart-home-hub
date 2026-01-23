#ifndef SAVE_CONFIG_H__
#define SAVE_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "led.h"

typedef enum {
    color_config,
    brightness_config,
    speed_config,
    mode_config
}config_t;

extern rgb_color_t default_color;

void save_config(config_t config_type);
void load_config(void);

#ifdef __cplusplus
}
#endif
#endif