#include <stdio.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "main.h"
#include "led.h"
#include "wifi.h"
#include "WS2812FX.h"   // figure how to mix C and CPP (viz. clovece-nezlob-se)

int num_leds = MAX_LEDS;
led_strip_handle_t led_strip = NULL;

void app_main(void)
{
    /* INIT LED STRIP */
    led_strip = configure_strip(num_leds);

    /* INIT WIFI */
    esp_err_t wifi_status = WIFI_FAILURE;
    // init nvs - used by the wifi driver
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }

    wifi_status = connect_wifi();
    if (wifi_status != WIFI_SUCCESS) {
        ESP_LOGI("WIFI", "Failed to assocciate to AP, dying ...");
        return;
    }

    /* START WEBSERVER */
    httpd_handle_t server_instance = start_webserver();
}
