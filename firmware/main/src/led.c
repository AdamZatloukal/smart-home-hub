#include "led_strip.h"
#include "led.h"
#include "esp_log.h"

static const char* TAG = "led strip";

void test_led_strip(void)
{
    led_strip_handle_t led_strip = configure_strip();
    
    for (int i = 0; i < MAX_LEDS; i++)
    {
        vTaskDelay(pdMS_TO_TICKS(200));
        ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, i, 255, 0, 0));
        ESP_LOGI(TAG, "LED i: %i turned on", i);
        ESP_ERROR_CHECK(led_strip_refresh(led_strip));
    }

    vTaskDelay(pdMS_TO_TICKS(5000));
    led_strip_clear(led_strip);
}

led_strip_handle_t configure_strip(void)
{
    led_strip_config_t strip_config = {
        .strip_gpio_num = STRIP_GPIO,
        .max_leds = MAX_LEDS,
        .led_model = LED_MODEL_WS2812,
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
        .flags = {
            .invert_out = false}};

    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = 10 * 1000 * 1000, // 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
        .mem_block_symbols = 64,
        .flags = {
            .with_dma = true}};

    led_strip_handle_t led_strip = NULL;
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    ESP_LOGI(TAG, "Created led strip object that uses RMT");

    return led_strip;
}