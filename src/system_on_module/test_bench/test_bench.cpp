#include "test_bench.h"
#include <esp32_utilities.h>

void TestBench::begin()
{
    //* 1. Test External I/O

    //* 2. Text Real Time Clock
    ESP_ERROR initialize_rtc = rtc.begin(RealTimeClock::RV8803_IC, esp.i2c0);
    //* 3. Test Internal Motion Unit (& calibrate?)
    //* 5. Test eMMC

    //* 6. Test Analog to Digital Converter

    //* 7. CAN bus

    //*
}