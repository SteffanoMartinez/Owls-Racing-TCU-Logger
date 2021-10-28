#pragma once

#include <Arduino.h>
#include <esp32_utilities.h>

#include <ACAN2517FD.h>

#include "../device/device_pinout.h"
#include "../device/soc_settings.h"
#include <SparkFunSX1509.h>
struct TestBenchErrors
{
    TestBenchErrors()
    {
        io_expansion = false;
    }

    bool io_expansion;
};


class TestBench
{
public:
    void begin();

    SystemOnChip esp;
    Terminal terminal;
    RealTimeClock rtc;
    EMMC_Memory emmc;
    SX1509 ioExpansion;
    


private:

    SystemOnChip esp;
    Terminal terminal;
    RealTimeClock rtc;
    SX1509 io_expansion;
    TestBenchErrors testBenchErrors;

    // SystemOnChip esp;
    Terminal terminal;
    //RealTimeClock rtc;

};

extern TestBench testBench;
