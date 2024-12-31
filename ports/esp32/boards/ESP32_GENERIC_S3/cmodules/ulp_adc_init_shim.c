//pulled from idf4.4 - https://github.com/espressif/esp-idf/blob/release/v4.4/components/ulp/ulp_riscv_adc.c
//there seems to be a problem with the calibration function being removed from the idf, hence a linking error and failure to calibrate, possibly resulting in the weird readings not going below 2048 when pin is shorted to ground.


#include "ulp_adc_init_shim.h"
#include "esp_err.h"
#include "esp_check.h"
#include "esp_log.h"
#include "driver/adc.h"
#include "hal/adc_hal.h"
#include "esp_private/esp_sleep_internal.h"
#include "esp_private/sar_periph_ctrl.h"
#include "freertos/FreeRTOS.h"

extern esp_err_t adc1_rtc_mode_acquire(void);
extern uint32_t get_calibration_offset(adc_unit_t adc_n, adc_channel_t chan);

static const char *TAG = "ulp_riscv_adc";

esp_err_t ulp_riscv_adc_init_44(const ulp_riscv_adc_cfg_t *cfg)
{
    esp_err_t ret = ESP_OK;

    ESP_GOTO_ON_FALSE(cfg, ESP_ERR_INVALID_ARG, err, TAG, "cfg == NULL");

    adc1_config_channel_atten(cfg->channel, cfg->atten);
    adc1_config_width(cfg->width);


//    //Calibrate the ADC
//    uint32_t cal_val = get_calibration_offset(ADC_UNIT_1, cfg->channel);
//    adc_hal_set_calibration_param(ADC_UNIT_1, cal_val);

    adc1_rtc_mode_acquire();

err:
    return ret;
}
