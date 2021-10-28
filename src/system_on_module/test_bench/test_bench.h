#pragma once

#include <Arduino.h>
#include <esp32_utilities.h>
#include <ACAN2517FD.h>

class TestBench
{
public:
    void begin();
    SystemOnChip esp;
    Terminal terminal;
    RealTimeClock rtc;
    EMMC_Memory emmc;
    SX1509 ioExpansion;
    
};

extern TestBench testBench;
