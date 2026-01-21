#include <stdio.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "wifi.h"
#include "led.h"



void app_main(void)
{
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

    httpd_handle_t server_instance = start_webserver();
}
