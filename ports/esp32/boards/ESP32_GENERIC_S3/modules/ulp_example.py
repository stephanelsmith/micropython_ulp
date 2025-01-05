import time
import esp32

# Pin Toggle signal on GPIO 4
# ADC on GPIO 2

u = esp32.ULP()
u.adc_init(1) # ADC1_CH1, GPIO2
u.rtc_init(3)  # RTC_3, GPIO3
u.run_embedded()

def togglePinToggle():
    state = u.read(u.VAR_TOGGLE)
    u.write(u.VAR_TOGGLE, not state)

def startULP():
    u.resume()

def stopULP():
    u.pause()

def showReadings():
    while True:
        reading = u.read(u.VAR_VBAT_RAW)
        counter = u.read(u.VAR_COUNTER)
        print(f"ADC:{reading}, counter:{counter}")
        time.sleep(0.1)

showReadings()