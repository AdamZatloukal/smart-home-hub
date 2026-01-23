#include "nvs_flash.h"
#include "led.h"
#include "save_config.h"
#include "main.h"
#include "esp_log.h"


// TEMPORARY CHOSE DIFFERENT DEFAULT COLOR!!!!!!!!!!!!!
rgb_color_t default_color {
    .red = 255,
    .green = 255,
    .blue = 255
};

void save_config(config_t config_type)
{
    /* create nvs handle and open nvs */
    nvs_handle_t nvs_handle_config = NULL;
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &nvs_handle_config));

    /* store data in nvs */
    switch (config_type)
    {
    case color_config:
        rgb_color_t rgb_color;
        HEX_TO_RGB(fx->getColor(), rgb_color.red, rgb_color.green, rgb_color.blue);
        ESP_ERROR_CHECK(nvs_set_u8(nvs_handle_config, "color-red", rgb_color.red));
        ESP_ERROR_CHECK(nvs_set_u8(nvs_handle_config, "color-green", rgb_color.green));
        ESP_ERROR_CHECK(nvs_set_u8(nvs_handle_config, "color-blue", rgb_color.blue));
        break;

    case brightness_config:
        ESP_ERROR_CHECK(nvs_set_u8(nvs_handle_config, "brightness", fx->getBrightness()));
        break;

    case speed_config:
        ESP_ERROR_CHECK(nvs_set_u16(nvs_handle_config, "speed", fx->getSpeed()));
        break;

    case mode_config:
        ESP_ERROR_CHECK(nvs_set_u8(nvs_handle_config, "mode", fx->getMode()));
        break;

    default:
        break;
    }
    ESP_ERROR_CHECK(nvs_commit(nvs_handle_config));    // save the changes
}

void load_config(void) {
    /* create nvs handle and open nvs */
    nvs_handle_t nvs_handle_config = NULL;
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &nvs_handle_config));

    rgb_color_t rgb_color;

    esp_err_t err_red = nvs_get_u8(nvs_handle_config, "color-red", &rgb_color.red);
    esp_err_t err_green = nvs_get_u8(nvs_handle_config, "color-green", &rgb_color.green);
    esp_err_t err_blue = nvs_get_u8(nvs_handle_config, "color-blue", &rgb_color.blue);

    if (err_red != ESP_OK || err_green != ESP_OK || err_blue != ESP_OK)
        fx->setColor(RGB_TO_HEX(default_color.red, default_color.green, default_color.blue));
    else
        fx->setColor(RGB_TO_HEX(rgb_color.red, rgb_color.green, rgb_color.blue));


    uint8_t brightness_value;
    esp_err_t err = nvs_get_u8(nvs_handle_config, "brightness", &brightness_value);
    
    if (err != ESP_OK) 
        fx->setBrightness(255);
    else 
        fx->setBrightness(brightness_value);


    uint16_t speed_value;
    err = nvs_get_u16(nvs_handle_config, "speed", &speed_value);

    if (err != ESP_OK) 
        fx->setSpeed(1000);
    else 
        fx->setSpeed(speed_value);


    uint8_t mode_value;
    err = nvs_get_u8(nvs_handle_config, "mode", &mode_value);

    if (err != ESP_OK) 
        fx->setMode(FX_MODE_STATIC);
    else 
        fx->setMode(mode_value);
}