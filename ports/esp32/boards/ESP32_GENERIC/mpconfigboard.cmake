set(SDKCONFIG_DEFAULTS
    boards/sdkconfig.base
    boards/sdkconfig.ble
)

set(MICROPY_FROZEN_MANIFEST ${MICROPY_BOARD_DIR}/manifest.py)
set(ulp_embedded_sources ${MICROPY_BOARD_DIR}/ulp/main_adc_toggle.S)