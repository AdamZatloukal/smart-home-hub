#include "driver/i2s_std.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "i2s_mic.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


i2s_chan_handle_t rx_chan;

// the mic outputs 24b - for this test we will use 16b only
void i2s_init(void)
{
    /* when we register a channel we also initialize the i2s peripheral*/
    /**
     * dma descriptor is a linked list nnode containing the following info: pointer to the buffer with the data,
     *      size of the buffer
     *      pointer to the next descriptor
     *      others (non important right now)
     *
     * dma frame num is the number of frames (samples) that are in the buffer
     */
    i2s_chan_config_t rx_chan_config = {
        .id = I2S_NUM_AUTO,
        .role = I2S_ROLE_MASTER,
        .dma_desc_num = 6,            // how many nodes
        .dma_frame_num = 512,         // sample = 32b (24 data 1 dalay 7 padding), buffer size is 9600B -> frame num = 9600B/4B = 2400 frames
        .auto_clear_after_cb = false, // the rest is copied from the I2S_CHANNEL_DEFAULT_CONFIG macro
        .auto_clear_before_cb = false,
        .allow_pd = false,
        .intr_priority = 0};

    /* how does dma work with this info *
     * dma starts with the first descriptor and fills its buffer with 512 samples
     * when that buffer is full it fills the next one until all 6 are filled
     * and the cycle starts again
     */

    ESP_ERROR_CHECK(i2s_new_channel(&rx_chan_config, NULL, &rx_chan));

    i2s_std_slot_config_t slot_config = {
        .data_bit_width = I2S_DATA_BIT_WIDTH_24BIT, // 2 - 25 data (one clock cycle delay)
        .slot_bit_width = I2S_SLOT_BIT_WIDTH_32BIT, // 26 - 32 padding      (1 cylce delay + 24 cycles data + 7 cycles padding = 32 clock cycles = 1/2 frame)
        .slot_mode = I2S_SLOT_MODE_MONO,            // in reality each WS cycle still transmits both left and right channel but no data are on the right channel
        .slot_mask = I2S_STD_SLOT_LEFT,             // data is only on the left channel
        .ws_width = 32,                             // ws stays hight for 32 SCK cycles and low for 32 SCK cycles
        .ws_pol = false,                            // left channel is first which corresponds to ws low
        .bit_shift = true,                          // since the MSB of each word is delays one SCK cycle from the start of the half-frame
        .left_align = true,                         // MSB first
        .bit_order_lsb = false,                     // LSB is NOT first
        .big_endian = false                         // least significant bytte is transmitted first (little endian)
    };

    /* slot is one half of a frame (sample) - so left and right - we only use left */
    i2s_std_config_t rx_std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(SAMPLING_FREQUENCY), // one frame is 48KHz (28,8 us), one clock cycle is 3,072 MHz (325 ns)
        .slot_cfg = slot_config,
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = BCLK_PIN,
            .ws = WS_PIN,
            .dout = I2S_GPIO_UNUSED,
            .din = DIN_PIN,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };
    /* sets up the channels params*/
    ESP_ERROR_CHECK(i2s_channel_init_std_mode(rx_chan, &rx_std_cfg));

    /* set SEL low/high to set what channel the mic will use */
    /* when LOW output is LEFT channel
     * when HIGH output is RIGHT channel
     */
    gpio_set_direction(SEL_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(SEL_PIN, 0);
}

I2S_STD_PHILIP_SLOT_DEFAULT_CONFIG()