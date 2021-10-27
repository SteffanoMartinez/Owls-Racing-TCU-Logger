#pragma once

#include <Arduino.h>
#include <esp32_utilities.h>

class TestBench
{
public:
    void begin();

private:
    // SystemOnChip esp;
    Terminal terminal;
    //RealTimeClock rtc;
};

extern TestBench testBench;
