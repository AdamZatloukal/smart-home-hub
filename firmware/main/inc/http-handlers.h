#ifndef HTTP_HANDLERS_H_
#define HTTP_HANDLERS_H_

#include "esp_http_server.h"


#define LED_PIN GPIO_NUM_18 // temporary

/**
 * Events regarding http server
 */

/**
 * @brief temorary
 */
esp_err_t led_on_handler(httpd_req_t* req);

/**
 * @brief temporary
 */
esp_err_t led_off_handler(httpd_req_t* req);

/**
 * @brief this handler receives a request that contains a JSON file that contains RGB colors.
 *      JSON is parsed and afterwards every led on led_strip is turned on with said color
 * @param received http request sent by the frontend
 * @return error in case reading the request failed or the led strip failded to init
 */
esp_err_t set_color_handler(httpd_req_t *req);


#endif