#include "test_bench.h"
#include <esp32_utilities.h>
#include <system_on_module/device/device_pinout.h>
#include <system_on_module/device/soc_settings.h>
RealTimeClock rtc;
SystemOnChip esp;
EMMC_Memory emmc;

void TestBench::begin()
{
    esp.uart0.begin(115200);
    terminal.begin(&esp.uart0);

    terminal.printMessage(TerminalMessage("Test bench begin", "TES", INFO, micros()));

    esp.i2c0.begin(I2C0_SDA, I2C0_SCL, I2C0_CLK_FREQUENCY_KHz * 1000);
    esp.i2c1.begin(I2C1_SDA, I2C1_SCL, I2C1_CLK_FREQUENCY_KHz * 1000);

    //* 1. Test External I/O
    ESP_ERROR io;
    // When IO lib is ported, begin fucntion comes here.

    if (!io_expansion.begin(0x3E))
    {
        Serial.println("Failed to communicate.");
        while (1)
            ;
    }
    //* 2. Text Real Time Clock
<<<<<<< HEAD
    ESP_ERROR rtc_initialize = rtc.begin(RealTimeClock::RV8803_IC, &esp.i2c0);

    if (rtc_initialize.on_error)
    {
        testBenchErrors.io_expansion = true;
    }
    else
        terminal.printMessage(TerminalMessage("RTC Initialied Successfully", "TES", INFO, micros()));

=======
    esp.i2c0.begin(I2C0_SDA_PIN, I2C0_SCL_PIN, I2C0_CLK_FREQUENCY_KHz * 1000);
    ESP_ERROR initialize_rtc = rtc.begin(RealTimeClock::RV8803_IC, &esp.i2c0);
    if (initialize_rtc.on_error)
    {
        terminal.printMessage(TerminalMessage("RTC Failed Initialization", "RTC", ERROR, micros()));
    }
    else
    {
        terminal.printMessage(TerminalMessage("RTC Succesfully Initialized", "RTC", INFO, micros()));
    }
>>>>>>> 092051fb0968885b39f93681d73f874b19e72874
    //* 3. Test Internal Motion Unit (& calibrate?)
    // When IMU lib is ported, begin function comes here.

    //* 5. Test eMMC
    ESP_ERROR initialize_emmc = emmc.begin(eMMC0_EN_PIN_EXT, eMMC0_CD_PIN_EXT, eMMC_MODE, MODE_1_BIT);
    if (initialize_emmc.on_error)
    {
        terminal.printMessage(TerminalMessage("eMMC Falied Initialization", "EMC", ERROR, micros()));
    }
    else
    {
        terminal.printMessage(TerminalMessage("eMMC Succesfully Initialized", "EMC", INFO, micros()));
    }

    //* 6. Test Analog to Digital Converter

    //* 7. CAN bus

    //* Print all errors that are true

    vTaskDelete(NULL);
}