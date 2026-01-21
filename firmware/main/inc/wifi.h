#ifndef WIFI_H_
#define WIFI_H_

#include "freertos/event_groups.h"
#include "esp_http_server.h"


/**
 * @example 
    * esp_err_t status = WIFI_FAILURE;

        gpio_set_direction(LED_PIN ,GPIO_MODE_OUTPUT);

        // init nvs - used by the wifi driver
        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
            nvs_flash_erase();
            nvs_flash_init();
        }

        status = connect_wifi();

        if (status != WIFI_SUCCESS) {
            ESP_LOGI(TAG, "Failed to assocciate to AP, dying ...");
            return;
        }

        start_webserver();
 */

 /* these includes are just needed for the declarations*/

#define WIFI_SUCCESS 1 << 0 // 0001
#define WIFI_FAILURE 1 << 1 // 0010

#define MAX_FAILURES 10

#define LED_PIN GPIO_NUM_18

// retry tracker - how many times did we fail to connect
static uint8_t retry_num = 0;
static EventGroupHandle_t wifi_event_group;


/**
 * @interface functions that can be used in app_main
 */
httpd_handle_t start_webserver();
esp_err_t connect_wifi();

/**
 * Events regarding wifi connection
 */
static void got_ip_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);


/**
 * Events regarding http server
 */
esp_err_t led_on_handler(httpd_req_t* req);
esp_err_t led_off_handler(httpd_req_t* req);
esp_err_t data_colors_handler(httpd_req_t *req);

#endif