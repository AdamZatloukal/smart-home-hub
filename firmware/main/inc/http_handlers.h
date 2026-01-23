#ifndef HTTP_HANDLERS_H_
#define HTTP_HANDLERS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_http_server.h"


#define LED_PIN GPIO_NUM_18 // temporary

/**
 * Events regarding http server
 */

/**
 * @brief this handler receives a request that contains a JSON file that contains RGB colors.
 *      JSON is parsed and afterwards every led on led_strip is turned on with said color
 * @param received http request sent by the frontend
 * @return error in case reading the request failed or the led strip failded to init
 */
esp_err_t set_color_handler(httpd_req_t *req);

esp_err_t set_color_handler(httpd_req_t *req);
esp_err_t set_brightness_handler(httpd_req_t *req);
esp_err_t set_speed_handler(httpd_req_t *req);
esp_err_t set_mode_handler(httpd_req_t *req);

esp_err_t handle_post_request(httpd_req_t *req, char *content, int content_size);


#ifdef __cplusplus
}
#endif

#endif