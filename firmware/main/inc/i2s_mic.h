#ifndef I2S_MIC_H_
#define I2S_MIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "driver/i2s_std.h"

#define BUFFER_SIZE 9600

#define BCLK_PIN GPIO_NUM_7
#define WS_PIN   GPIO_NUM_21
#define DIN_PIN  GPIO_NUM_14
#define SEL_PIN  GPIO_NUM_4

/* this is the WS frequency one frame is one sample */
#define SAMPLING_FREQUENCY 48000

extern i2s_chan_handle_t rx_chan;

void i2s_init(void);



#ifdef __cplusplus
}
#endif

#endif