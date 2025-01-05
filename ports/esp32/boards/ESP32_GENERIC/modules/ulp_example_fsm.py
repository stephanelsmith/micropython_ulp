import time
import esp32

# Pin Toggle signal on GPIO 4
# ADC on GPIO 2

u = esp32.ULP()
u.adc_init(6) # ADC1_CH6, GPIO34
u.rtc_init(33)  # RTC_8, GPIO33
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
        reading = u.read(u.VAR_VBAT_RAW) & 0xffff
        counter = u.read(u.VAR_COUNTER)  & 0xffff
        print(f"ADC:{reading}, counter:{counter}")
        time.sleep(0.1)
        
showReadings()