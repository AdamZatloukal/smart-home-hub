#include "freertos/FreeRTOS.h"
#include "wifi.h"
#include <stdio.h>
#include "esp_wifi.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_http_server.h"
#include "driver/gpio.h"
#include "led.h"
#include "http_handlers.h"

static const char* TAG = "WIFI";

/*
* arg is user data passed in the handler
* event_base is the category of the event (selected in event_register) - IP_EVENT
* event_id is the specific event id - IP_EVENT_STA_GOT_IP
* event_data is the infromation from the event
* void* means a pointer to any type - generic pointer
*       we cannot directly dereference it and need to cast it to the correct type
*/
static void got_ip_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
    ESP_LOGI(TAG, "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));

    retry_num = 0; 
    xEventGroupSetBits(wifi_event_group, WIFI_SUCCESS);
}

static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    esp_err_t status_connect;
    /* if the event is that the ESP32 was configured as a station it means we can connect to the AP*/
    if (event_id == WIFI_EVENT_STA_START) {
        ESP_LOGI(TAG, "Connecting to AP...");

        status_connect = esp_wifi_connect(); // tries to connect to the AP
    
        ESP_LOGI("WIFI", "esp_wifi_connect status: %s", esp_err_to_name(status_connect));
    }
    else if (event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (retry_num < MAX_FAILURES) {
            ESP_LOGI(TAG, "Connecting to AP...");

            status_connect = esp_wifi_connect();
            retry_num++;
        }
        else {
            xEventGroupSetBits(wifi_event_group, WIFI_FAILURE);
        }
    }
}

esp_err_t connect_wifi() {
    int status = WIFI_FAILURE;

    /* network interface init*/
    esp_netif_init(); // initializes the TCP/IP stack
    esp_event_loop_create_default(); // creates an event loop so that we can handle events
    esp_netif_create_default_wifi_sta(); // create the interface for wifi station - like a door between our code and the wifi driver

    /* look in the docs for these functions - AI told me to add them*/
    esp_event_handler_instance_t got_ip_event_handler_instance;
    esp_event_handler_instance_register(IP_EVENT, // type of event we want to register
                                        IP_EVENT_STA_GOT_IP, // specific type of ip event
                                        &got_ip_handler, // call this function what IP_EVENT_STA_GOT_IP happens
                                         NULL, // data that will be passed as arg to the on_got_ip function
                                         &got_ip_event_handler_instance); // handler instance - needed for when we want to unregister the event

    esp_event_handler_instance_t wifi_handler_event_instance;
    esp_event_handler_instance_register(WIFI_EVENT,
                                        ESP_EVENT_ANY_ID,
                                        &wifi_event_handler,
                                        NULL,
                                        &wifi_handler_event_instance);

    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT(); // creates a struct with wifi init information

    esp_wifi_init(&config); // prepares and powers up the WiFi system on the ESP32. It allocates memory, loads data and starts a RTOS task.
    esp_wifi_set_mode(WIFI_MODE_STA); // set the mode of the ESP as station

    wifi_event_group = xEventGroupCreate();

    /* !!!!!!!!!!!!!!!!!! SENSITIVE INFORAMTION !!!!!!!!!!!!!!!!!! */
    wifi_config_t wifi_config = { // set the configuration for the network we want to connect to
        .sta = {
            .ssid = "-",
            .password = "-"
        }
    };

    esp_wifi_set_config(WIFI_IF_STA, &wifi_config); // configures wifi settings like the ssid and password
    esp_wifi_start(); // enables the HW required for WiFi - events will start to happen

    // blocks the execution of the function until the condition is true
    EventBits_t bits = xEventGroupWaitBits(wifi_event_group, 
                                        WIFI_FAILURE | WIFI_SUCCESS, // 0010 | 0001 -> 0011 (0x03) - the code will continue to execute when this is true - this adds the two bits into a mask
                                        pdFALSE, // the bits we are waiting for will not be cleared
                                        pdFALSE, // wait stops when any one of the bits is set
                                        portMAX_DELAY); // block indefinitely

    /* check for what event actually happened */
    if (bits & WIFI_SUCCESS) { // 0001 (WIFI_SUCCESS) & 0001 -> 0001 (true) 
        status = WIFI_SUCCESS; // 0010 (WIFI_FAILURE) & 0001 -> 0000 (false)
        ESP_LOGI(TAG, "Connected to AP");
    }
    else if (bits & WIFI_FAILURE) { 
        status = WIFI_FAILURE;
        ESP_LOGI(TAG, "Failed to connect to the AP");
    }
    else {
        ESP_LOGI(TAG, "Unexpected event");
        status = WIFI_FAILURE;
    }

    /* unregister the events after they are not needed */
    esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_handler_event_instance);
    esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, got_ip_event_handler_instance);
    vEventGroupDelete(wifi_event_group);

    return status;
}

httpd_handle_t start_webserver() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    httpd_handle_t server_handle = NULL;

    /*
    * GET mean the server (ESP) is sending data to us
    * POST means that we are sending the data to the server
    */

    httpd_uri_t set_color = {
        .uri = "/set/color",
        .method = HTTP_POST,
        .handler = set_color_handler,
    };

    httpd_uri_t set_brightness = {
        .uri = "/set/brightness",
        .method = HTTP_POST,
        .handler = set_brightness_handler
    };

    httpd_uri_t set_speed = {
        .uri = "/set/speed",
        .method = HTTP_POST,
        .handler = set_speed_handler
    };

    httpd_uri_t set_mode = {
        .uri = "/set/mode",
        .method = HTTP_POST,
        .handler = set_mode_handler
    };

    if (httpd_start(&server_handle, &config) == ESP_OK) {
        ESP_ERROR_CHECK(httpd_register_uri_handler(server_handle, &set_color));
        ESP_ERROR_CHECK(httpd_register_uri_handler(server_handle, &set_brightness));
        ESP_ERROR_CHECK(httpd_register_uri_handler(server_handle, &set_speed));
        ESP_ERROR_CHECK(httpd_register_uri_handler(server_handle, &set_mode));
    };

    return server_handle;

}