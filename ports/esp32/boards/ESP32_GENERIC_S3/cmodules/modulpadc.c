#include "py/obj.h"
#include "py/runtime.h"
#include "hal/adc_types.h"
#include "driver/gpio.h"
#include "ulp_riscv.h"
#include "ulp_test_adc.h"
#include "ulp_adc_init_shim.h"

extern const uint8_t ulp_main_bin_start[] asm("_binary_ulp_test_adc_bin_start");
extern const uint8_t ulp_main_bin_end[]   asm("_binary_ulp_test_adc_bin_end");

static mp_obj_t ulpadc_start() {
     ulp_riscv_adc_cfg_t cfg = {
//        .adc_n    = ADC_UNIT_1,
        .channel  = ADC_CHANNEL_1,
        .width    = ADC_BITWIDTH_DEFAULT,
        .atten    = ADC_ATTEN_DB_11,
//        .ulp_mode = ADC_ULP_MODE_RISCV,
    };
    ESP_ERROR_CHECK(ulp_riscv_adc_init_44(&cfg));

    esp_err_t err = ulp_riscv_load_binary(ulp_main_bin_start, (ulp_main_bin_end - ulp_main_bin_start));
    ESP_ERROR_CHECK(err);

    ulp_set_wakeup_period(0, 10000);

    err = ulp_riscv_run();
    ESP_ERROR_CHECK(err);

    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(ulpadc_start_obj, ulpadc_start);

static mp_obj_t ulpadc_stop() {
    ulp_riscv_timer_stop();
    ulp_riscv_halt(); 
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(ulpadc_stop_obj, ulpadc_stop);


static mp_obj_t ulpadc_reading_raw() {
    return mp_obj_new_int(ulp_vbat_raw);
}
static MP_DEFINE_CONST_FUN_OBJ_0(ulpadc_reading_raw_obj, ulpadc_reading_raw);

static const mp_rom_map_elem_t ulpadc_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_ulp_adc) },
    { MP_ROM_QSTR(MP_QSTR_start),    MP_ROM_PTR(&ulpadc_start_obj) },
    { MP_ROM_QSTR(MP_QSTR_stop),     MP_ROM_PTR(&ulpadc_stop_obj) },
    { MP_ROM_QSTR(MP_QSTR_raw),      MP_ROM_PTR(&ulpadc_reading_raw_obj) },
};

static MP_DEFINE_CONST_DICT(ulpadc_globals, ulpadc_globals_table);

const mp_obj_module_t ulpadc_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&ulpadc_globals,
};

MP_REGISTER_MODULE(MP_QSTR_ulp_adc, ulpadc_user_cmodule);
