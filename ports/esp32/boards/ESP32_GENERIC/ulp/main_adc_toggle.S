#include "sdkconfig.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "soc/soc_ulp.h"
#include "soc/sens_reg.h"

/*
Pseudo code

uint16_t var_vbat_raw;
uint16_t var_toggle;
uint16_t var_counter;

void main (void)
{      
    var_vbat_raw = ulp__adc_read_channel(ADC_UNIT_1, ADC_CHANNEL_1);
    
    if(var_toggle){
        ulp_gpio_output_level(4, 1);
        ulp_gpio_output_level(4, 0);
    }

    var_counter += 1
}
*/


.text
	.equ gpio_toggle, 	8 // gpio 33
	.equ gpio_adc_ch, 	6 // ADC1, ch6, gpio 34

.global var_toggle
var_toggle:
    .long 1

.global var_vbat_raw
var_vbat_raw:
    .long 0
    
.global var_counter
var_counter:
    .long 0

.global entry

entry:

    //R0 = ADC2 @ CH(n-1), n = 3
    adc     r1, 0, gpio_adc_ch + 1
    //var_reading = R0
    move    r2, var_vbat_raw
    st      r1, r2, 0


    //R0 = var_toggle
    move    r1, var_toggle
    ld      r0, r1, 0
	// if(R0 > 0) goto toggle_end
	jumpr	toggle_end, 0, EQ	

toggle_start:
    /* set pin as output */
	WRITE_RTC_REG(RTC_GPIO_ENABLE_W1TS_REG, RTC_GPIO_ENABLE_W1TS_S + gpio_toggle , 1, 1)
    
    /* pin set low */
    WRITE_RTC_REG(RTC_GPIO_OUT_W1TC_REG, RTC_GPIO_OUT_DATA_W1TC_S + gpio_toggle, 1, 1)

    /* pin set high */
	WRITE_RTC_REG(RTC_GPIO_OUT_W1TS_REG, RTC_GPIO_OUT_DATA_W1TS_S + gpio_toggle, 1, 1)

toggle_end:

    
	//var_counter += 1
	move	R1, var_counter 
	ld		R0, R1, 0
	add		R0, R0, 1
    st      R0, R1, 0

    halt