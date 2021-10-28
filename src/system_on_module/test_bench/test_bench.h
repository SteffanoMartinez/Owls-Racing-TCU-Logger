#pragma once

#include <Arduino.h>
#include <esp32_utilities.h>

class TestBench
{
public:
    void begin();
    SystemOnChip esp;
    Terminal terminal;
    RealTimeClock rtc;
    EMMC_Memory emmc;
    SX1509 ioExpansion;
    MCP2518FD canController;
};

extern TestBench testBench;
