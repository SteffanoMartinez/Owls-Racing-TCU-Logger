//**Team Number 24**//

#include <Arduino.h>
#include <esp32_utilities.h>
#include <system_on_module/test_bench/test_bench.h>

TestBench test;

void setup()
{
  test.begin();
}

void loop()
{
  vTaskDelete(NULL);
}

