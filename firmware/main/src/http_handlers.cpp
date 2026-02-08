#include "http_handlers.h"
#include "esp_http_server.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led.h"
#include "cJSON.h"
#include "sys/param.h"
#include "WS2812FX.h"
#include "main.h"
#include "save_config.h"

esp_err_t handle_post_request(httpd_req_t *req, char *content, int content_size) 
{   
    /* if the amount of data we received is larger than the buffer we
     will cutoff the amount of data we received to the size of the buffer */
    size_t recv_size = MIN(req->content_len, content_size);

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

    return ESP_OK;
}


extern "C" esp_err_t set_color_handler(httpd_req_t *req) 
{
    char content[100];
    handle_post_request(req, content, sizeof(content));

    const cJSON *colors;

    colors = cJSON_Parse((const char *)content);
    const cJSON *red = cJSON_GetObjectItem(colors, "red");
    const cJSON *green = cJSON_GetObjectItem(colors, "green");
    const cJSON *blue = cJSON_GetObjectItem(colors, "blue");

    ESP_LOGI("COLORS", "RED: %d    GREEN: %d   BLUE: %d", red->valueint, green->valueint, blue->valueint);
    rgb_color_t color = {
        .red = (uint8_t)(red->valueint),
        .green = (uint8_t)(green->valueint),
        .blue = (uint8_t)(blue->valueint)
    };

    // here we just set the color the rest is done in the fx loop task
    fx->setColor(RGB_TO_HEX(color.red, color.green, color.blue));
    fx->trigger();      // sets _triggered to true so that led_strip_refresh is called
    save_config(color_config);

    return ESP_OK;
}

extern "C" esp_err_t set_brightness_handler(httpd_req_t *req) 
{
    char content[100];
    handle_post_request(req, content, sizeof(content));

    cJSON *brightness_obj = cJSON_Parse((const char *)content);
    cJSON *brightness_item = cJSON_GetObjectItem(brightness_obj, "brightness");

    fx->setBrightness((uint8_t)(brightness_item->valueint));
    fx->trigger();      // sets _triggered to true so that led_strip_refresh is called
    save_config(brightness_config);

    return ESP_OK;
}

extern "C" esp_err_t set_speed_handler(httpd_req_t *req)
{
    char content[100];
    handle_post_request(req, content, sizeof(content));

    cJSON *speed_obj = cJSON_Parse((const char *)content);
    cJSON *speed_item = cJSON_GetObjectItem(speed_obj, "speed");

    fx->setSpeed((uint16_t)(speed_item->valueint));
    fx->trigger();      // sets _triggered to true so that led_strip_refresh is called
    save_config(speed_config);

    return ESP_OK;
}

extern "C" esp_err_t set_mode_handler(httpd_req_t *req)
{
    char content[100];
    handle_post_request(req, content, sizeof(content));

    cJSON *mode_obj = cJSON_Parse((const char *)content);
    cJSON *mode_item = cJSON_GetObjectItem(mode_obj, "mode");

    fx->setMode((uint8_t)(mode_item->valueint));
    fx->trigger();      // sets _triggered to true so that led_strip_refresh is called
    save_config(mode_config);

    return ESP_OK;
}