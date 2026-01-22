#include "http-handlers.h"
#include "esp_http_server.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led.h"
#include "cJSON.h"
#include "sys/param.h"
#include "main.h"


esp_err_t led_on_handler(httpd_req_t* req) {
    const char *respone = "LED ON";

    ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, 0, 255, 0, 0));
    ESP_ERROR_CHECK(led_strip_refresh(led_strip));

    ESP_LOGI("HTTP", "LED ON");
    httpd_resp_send(req, respone, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

esp_err_t led_off_handler(httpd_req_t* req) {
    const char *response = "LED OFF";
    
    gpio_set_level(LED_PIN, 0);
    ESP_LOGI("HTTP", "LED OFF");
    httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

esp_err_t set_color_handler(httpd_req_t *req) {
    char content[100]; // buffer for the recieved data
    
    /* if the amount of data we received is larger than the buffer we
     will cutoff the amount of data we received to the size of the buffer */
    size_t recv_size = MIN(req->content_len, sizeof(content));

    int ret = httpd_req_recv(req, content, recv_size); // get the data

    if (ret <= 0) { // 0 return value indicates closed connection

        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
            // ADD: try to reconnect
            httpd_resp_send_408(req);
        }
        return ESP_FAIL;
    }

    const char *response = "DATA RECEIVED";
    httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);

    const cJSON *colors;

    colors = cJSON_Parse((const char *)content);
    const cJSON *red = cJSON_GetObjectItem(colors, "red");
    const cJSON *green = cJSON_GetObjectItem(colors, "green");
    const cJSON *blue = cJSON_GetObjectItem(colors, "blue");

    ESP_LOGI("COLORS", "RED: %d    GREEN: %d   BLUE: %d", red->valueint, green->valueint, blue->valueint);
    rgb_color_t color = {
        .red = red->valueint,
        .green = green->valueint,
        .blue = blue->valueint
    };

    turn_on_all_led(led_strip, num_leds, color);

    return ESP_OK;
}
