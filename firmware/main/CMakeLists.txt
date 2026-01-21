idf_component_register(SRC_DIRS "src"
                       REQUIRES  led_strip driver nvs_flash esp_http_server esp_wifi json
                       INCLUDE_DIRS "inc"
                       )
