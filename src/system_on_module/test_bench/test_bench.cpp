#include "test_bench.h"
#include <esp32_utilities.h>

void TestBench::begin()
{
    //* 1. Test External I/O

    //* 2. Text Real Time Clock
    esp.i2c0.begin(i2c0_sda, i2c0_scl, I2C0_CLK_FREQUENCY_KHz);
    ESP_ERROR initialize_rtc = rtc.begin(RealTimeClock::RV8803_IC, esp.i2c0);
    //* 3. Test Internal Motion Unit (& calibrate?)

    //* 4. Test Environmental Sensor

    //* 5. Test eMMC

    //* 6. Test Analog to Digital Converter

    //* 7. CAN bus

    //*
}