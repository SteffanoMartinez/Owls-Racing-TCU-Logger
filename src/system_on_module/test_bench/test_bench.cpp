#include "test_bench.h"
#include <esp32_utilities.h>
#include <system_on_module/device/device_pinout.h>
#include <system_on_module/device/soc_settings.h>
#include <ACAN2517FD.h>

TerminalMessage can_error_debug_message;
SystemOnChip esp;
ACAN2517FD can(CAN0_CONTROLLER_CS_PIN, esp.hspi, CAN0_CONTROLLER_INT_PIN);

void TestBench::begin()
{

    esp.uart0.begin(115200);
    terminal.begin(&esp.uart0, false);
    //* 1. Test External I/O
    ESP_ERROR initialize_io = ioExpansion.begin(&esp.i2c0, 0x3E);
    if (initialize_io.on_error)
    {
        terminal.printMessage(TerminalMessage("IO Expansion Successfully Initialized", "I/O", ERROR, micros()));
    }
    else
    {
        terminal.printMessage(TerminalMessage("IO Expansion Failed Initialization", "I/O", INFO, micros()));
    }
    // When IO lib is ported, begin fucntion comes here.
    //* 2. Text Real Time Clock
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
    // Port ADC

    //* 7. CAN
    long initial_time = millis();
    esp.hspi.begin(HSPI_CLCK_PIN, HSPI_MISO_PIN, HSPI_MOSI_PIN);
    ACAN2517FDSettings settings(ACAN2517FDSettings::OSC_40MHz, 1000 * 1000, DataBitRateFactor::x8);
    settings.mDriverReceiveFIFOSize = 200;

    const uint32_t errorCode = can.begin(settings, []
                                         { can.isr(); });

    can_error_debug_message.body = "CAN Bus Error Code = ";
    can_error_debug_message.body += String(errorCode);
    can_error_debug_message.system = "CAN";
    can_error_debug_message.type = ERROR;
    can_error_debug_message.time = micros();
    can_error_debug_message.process_time = micros() - initial_time;

    terminal.printMessage(can_error_debug_message);
}