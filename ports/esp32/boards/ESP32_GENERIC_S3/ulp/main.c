/* ULP-RISC-V example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.

   This code runs on ULP-RISC-V  coprocessor
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "ulp_riscv.h"
#include "ulp_riscv_adc.h"
#include "ulp_riscv_utils.h"
#include "ulp_riscv_adc_ulp_core.h"
#include "hal/adc_types.h"

unsigned int vbat;
unsigned int vbat_raw;

int main (void)
{      
    //GPIO15 = ADC2_CH4 
    //https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/peripherals/gpio.html
    vbat_raw = ulp_riscv_adc_read_channel(ADC_UNIT_1, ADC_CHANNEL_1);
    
    return 0;
}
