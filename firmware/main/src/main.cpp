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
#include "i2s_mic.h"

#include "driver/i2s_std.h"
#include "esp_http_client.h"
#include "esp_comm.h"

int num_leds = MAX_LEDS;
led_strip_handle_t led_strip = NULL;
WS2812FX *fx = NULL;
esp_http_client_handle_t client_handle;
TaskHandle_t task_read_mic_handle = NULL;

void fx_loop(void *parameter)
{
    fx = new WS2812FX(num_leds, led_strip);
    fx->init();
    load_config();
    fx->start(); // so that service calls led_strip_refresh

    while (true)
    {
        /* looks like it works without this*/
        // if (fx->getMode() == FX_MODE_STATIC)
        //     fx->fill(fx->getColor(), 0, num_leds);

        fx->service();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    vTaskDelete(NULL);
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
    //vTaskResume(task_read_mic_handle);  // when we connect to wifi we can send post requests
    //esp_now_setup();
    start_client();

    // add: if wifi disconnects check and reconnect
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);
}

void read_mic(void *parameter)
{
    start_client();    // create client instance

    int32_t *r_buffer = (int32_t *)calloc(1, BUFFER_SIZE);  // allocates 2048 bytes and fills it with 0 (int32_t is 4B so 2048/4 is 512 samples)
    assert(r_buffer);   // check if calloc was successful
    size_t r_bytes = 0; // number of bytes that was read using i2s_channel_read

    i2s_channel_enable(rx_chan);
    vTaskSuspend(NULL); // suspend this task until wifi is connected

    while (true)
    {
        if (i2s_channel_read(rx_chan, r_buffer, BUFFER_SIZE, &r_bytes, portMAX_DELAY) == ESP_OK)
        {
            int samples_read = r_bytes / sizeof(int32_t); 
            ESP_LOGI("debug", "buffer0: %d, buffer1: %d, r_bytes: %d", r_buffer[0], r_buffer[1], r_bytes);
            send_post_request_mic((const char *)r_buffer, r_bytes);
        }
        else
        {
            printf("Reading has failed");
        }
        
    }
    free(r_buffer);
    vTaskDelete(NULL);
}

extern "C" void app_main(void)
{
    // should fix a bug where incorrect pixels light up at startup - nope
    rgb_color_t off = {
        .red = 0,
        .green = 0,
        .blue = 0};

    /* INIT LED STRIP */
    led_strip = configure_strip(num_leds);
    turn_on_all_led(led_strip, num_leds, off);

    // init nvs - used by the wifi driver, memory of last color
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        nvs_flash_erase();
        nvs_flash_init();
    }

    /*
    i2s_init();

    xTaskCreatePinnedToCore(read_mic,
                            "read mic data",
                            4096,
                            NULL,
                            1,
                            &task_read_mic_handle,
                            0);
    */

    xTaskCreatePinnedToCore(wifi_webserver,
                            "wifi",
                            4096,
                            NULL,
                            2,
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
