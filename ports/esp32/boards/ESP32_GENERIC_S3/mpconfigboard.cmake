set(IDF_TARGET esp32s3)

set(SDKCONFIG_DEFAULTS
    boards/sdkconfig.base
    boards/sdkconfig.usb
    boards/sdkconfig.ble
    boards/sdkconfig.spiram_sx
    boards/ESP32_GENERIC_S3/sdkconfig.board
)



set(MICROPY_SOURCE_BOARD
    ${MICROPY_SOURCE_BOARD}
    ${MICROPY_BOARD_DIR}/cmodules/modulpadc.c
    ${MICROPY_BOARD_DIR}/cmodules/ulp_adc_init_shim.c
)

set(ulp_app_name ulp_test_adc)
set(ulp_sources ${MICROPY_BOARD_DIR}/ulp/main.c)
set(ulp_exp_dep_srcs "${MICROPY_BOARD_DIR}/cmodules/modulpadc.c")
