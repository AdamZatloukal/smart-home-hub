#ifndef WIFI_H_
#define WIFI_H_

#ifdef __cplusplus
extern "C" {
#endif

/* these includes are just needed for the declarations*/
#include "freertos/event_groups.h"
#include "esp_http_server.h"
#include "esp_http_client.h"

#define WIFI_SUCCESS 1 << 0 // 0001
#define WIFI_FAILURE 1 << 1 // 0010

#define MAX_FAILURES 10

// retry tracker - how many times did we fail to connect
static uint8_t retry_num = 0;
static EventGroupHandle_t wifi_event_group;

extern esp_http_client_handle_t client_handle;


/**
 * @interface functions that can be used in app_main
 */

/**
 * @brief configures a local HTTP server, registers all uri and starts the server
 * @return handle to the created http server
 */
httpd_handle_t start_webserver();

/**
 * @warning CONTAINS NETWORK CREDENTIALS!!!!
 * @brief initializes network interface, creates events for 
 *       got_ip_event_handler_instance and wifi_handler_event_instance
 *       inits esp wifi drivers and RTOS, waits until we are connected to an AP or till failure
 * @return error code in case we cannot connect to an AP
 */
esp_err_t connect_wifi();


/**
 * Events regarding wifi connection
 */

 /**
  * @brief called when the esp receives IP address and prints it 
  * @param arg is user data passed in the handler
  * @param event_base is the category of the event (selected in event_register) - IP_EVENT
  * @param event_id is the specific event id - IP_EVENT_STA_GOT_IP
  * @param event_data is the infromation from the event
  * @note void* means a pointer to any type - generic pointer
  *    we cannot directly dereference it and need to cast it to the correct type
*/
static void got_ip_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

 /**
  * @brief executes when any wifi event happens - tries to connect to an AP
  * @param arg is user data passed in the handler
  * @param event_base is the category of the event (selected in event_register) - WIFI_EVENT
  * @param event_id is the specific event id - ESP_EVENT_ANY_ID
  * @param event_data is the infromation from the event
  * @note void* means a pointer to any type - generic pointer
  *    we cannot directly dereference it and need to cast it to the correct type
*/
static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

void start_client(void);
void send_post_request_mic(const char *post_data, int post_data_len);

#ifdef __cplusplus
}
#endif

#endif