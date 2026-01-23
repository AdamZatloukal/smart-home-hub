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
#include "WS2812FX.h"
#include "save_config.h"

int num_leds = MAX_LEDS;
led_strip_handle_t led_strip = NULL;
WS2812FX *fx = NULL;

void fx_loop(void *parameter)
{
    fx = new WS2812FX(num_leds, led_strip);
    fx->init();
    load_config();
    fx->start();    // so that service calls led_strip_refresh

    while (true)
    {
        // temporary for testing
        fx->fill(fx->getColor(), 0, num_leds);

        fx->service();
        rgb_color_t color;

        // temporary for testing (doesnt print anyways
        HEX_TO_RGB(fx->getColor(), color.red, color.green, color.blue);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void wifi_webserver(void *parameter)
{
    /* INIT WIFI */
    esp_err_t wifi_status = WIFI_FAILURE;
    wifi_status = connect_wifi();
    if (wifi_status != WIFI_SUCCESS)
    {
        ESP_LOGI("WIFI", "Failed to assocciate to AP, dying ...");
        vTaskDelete(NULL);
    }

    /* START WEBSERVER */
    httpd_handle_t server_instance = start_webserver();

    // add: if wifi disconnects check and reconnect
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


extern "C" void app_main(void)
{
    /* INIT LED STRIP */
    led_strip = configure_strip(num_leds);

    // init nvs - used by the wifi driver, memory of last color
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        nvs_flash_erase();
        nvs_flash_init();
    }

    xTaskCreatePinnedToCore(wifi_webserver,
                            "wifi",
                            4096,
                            NULL,
                            1,
                            NULL,
                            0);

    xTaskCreatePinnedToCore(fx_loop,
                            "fx_loop",
                            4096,
                            NULL,
                            1,
                            NULL,
                            1);
}
