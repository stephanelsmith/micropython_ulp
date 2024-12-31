#ifndef NEW_ULP_ADC_INIT
#define NEW_ULP_ADC_INIT

#include "esp_err.h"
#include "hal/adc_types.h"
#include "driver/adc.h"

typedef struct {
    adc_channel_t channel;  // ADC channel
    adc_atten_t atten;      // ADC channel attenuation
    adc_bits_width_t width; // ADC bit width, only used for ADC unit 1
} ulp_riscv_adc_cfg_t;      // ULP Riscv ADC configuration parameters


esp_err_t ulp_riscv_adc_init_44(const ulp_riscv_adc_cfg_t *cfg);

#endif
