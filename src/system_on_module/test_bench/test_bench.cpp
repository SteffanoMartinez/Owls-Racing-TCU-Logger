#include "test_bench.h"

void TestBench::begin()
{
    esp.uart0.begin(115200);
    terminal.begin(&esp.uart0);

    terminal.printMessage(TerminalMessage("Test bench begin", "TES", INFO, micros()));

    esp.i2c0.begin(I2C0_SDA, I2C0_SCL, I2C0_CLK_FREQUENCY_KHz * 1000);
    esp.i2c1.begin(I2C1_SDA, I2C1_SCL, I2C1_CLK_FREQUENCY_KHz * 1000);

    //* 1. Test External I/O

    if (!io_expansion.begin(0x3E))
    {
        Serial.println("Failed to communicate.");
        while (1)
            ;
    }
    //* 2. Text Real Time Clock
    ESP_ERROR rtc_initialize = rtc.begin(RealTimeClock::RV8803_IC, &esp.i2c0);

    if (rtc_initialize.on_error)
    {
        testBenchErrors.io_expansion = true;
    }
    else
        terminal.printMessage(TerminalMessage("RTC Initialied Successfully", "TES", INFO, micros()));

    //* 3. Test Internal Motion Unit (& calibrate?)

    //* 4. Test Environmental Sensor

    //* 5. Test eMMC

    //* 6. Test Analog to Digital Converter

    //* 7. CAN bus

    //* Print all errors that are true

    vTaskDelete(NULL);
}