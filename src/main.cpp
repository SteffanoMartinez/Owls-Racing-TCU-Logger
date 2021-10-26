<<<<<<< HEAD
//**Team Number 24**//

#include <Arduino.h>
#include <esp32_utilities.h>
//#include <ACAN2517FD.h>
#include <MPU9250.h>
#include <quaternionFilters.h>

#define MPU9250_ADDRESS MPU9250_ADDRESS_AD0
#define I2Cport Wire
#define I2Cclock 400000
#define AHRS false       // Set to false for basic data read
#define SerialDebug true // Set to true to get Serial output for debugging
#define i2c_sda 21
#define i2c_scl 22

SystemOnChip esp;
Terminal terminal;

//PINS:

//**IMU**//
MPU9250 myIMU(MPU9250_ADDRESS_AD0, I2Cport, I2Cclock);

byte c = 0x00;

//Function Definitons
void imusetupTask(void *parameters);

void imurunTask(void *parameters);
=======
#include <system_on_module/app/app.h>
#include <system_on_module/test_bench/test_bench.h>

Application app;
TestBench testBench;
>>>>>>> 8a6afd5dea1b384e3f473b7c26d6f91ce5677ab2

void setup()
{
  // esp.uart0.begin(115200);
  // terminal.begin(&esp.uart0);
  Serial.begin(115200);
  disableCore0WDT();

  xTaskCreatePinnedToCore(imusetupTask,
                          "IMU", 10000, NULL, 18, NULL, 0);
  //xTaskCreatePinnedToCore(imurunTask,
  //                        "IMU", 10000, NULL, 18, NULL, 0);
}

void loop()
{
  //
}

void imusetupTask(void *parameters)
{
  Wire.begin(i2c_sda, i2c_scl, I2Cclock);

  TerminalMessage imu_test_debug_message;
  byte c = myIMU.readByte(MPU9250_ADDRESS_AD0, WHO_AM_I_MPU9250);
  // imu_test_debug_message.body = F("MPU9250 I AM 0x");
  // imu_test_debug_message.body += String(c, HEX);
  // imu_test_debug_message.body += " ";
  // imu_test_debug_message.body += F(" I should be ");
  // imu_test_debug_message.body += "0x071"; //0x071
  // imu_test_debug_message.body += " ";
  // imu_test_debug_message.body += String(HEX);
  // imu_test_debug_message.system = "IMU";
  // imu_test_debug_message.type = INFO;
  // imu_test_debug_message.time = micros();
  // terminal.printMessage(imu_test_debug_message);

  if (c == 0x71) // WHO_AM_I should always be 0x71
  {
    terminal.printMessage(TerminalMessage("MPU9250 is online...", "IMU", INFO, micros()));

    // Calibrate gyro and accelerometers, load biases in bias registers
    myIMU.calibrateMPU9250(myIMU.gyroBias, myIMU.accelBias);

    // Initilalize device to read accelerometer, magnetometer and gyroscope
    myIMU.initMPU9250();

    terminal.printMessage(TerminalMessage("MPU9250 initialized for active data mode....", "IMU", INFO, micros()));

    byte d = myIMU.readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);
    if (d != 0x48)
    {
      // Communication failed, stop here
      Serial.println(F("Communication failed, abort!"));
      abort();
    }
    else
    {
      terminal.printMessage(TerminalMessage("Magnetometer Unit is connected correctly",
                                            "IMU", INFO, micros()));
    }

    // Get magnetometer calibration from AK8963 ROM
    myIMU.initAK8963(myIMU.factoryMagCalibration);

    // Get sensor resolutions, only need to do this once
    myIMU.getAres();
    myIMU.getGres();
    myIMU.getMres();
  }
  else
  {
    Serial.print("Could not connect to MPU9250: 0x");
    terminal.printMessage(TerminalMessage(String((c, HEX)), "IMU", ERROR, micros()));
    // Communication failed, stop here
    Serial.println(F("Communication failed, abort!"));
  }
  while (1)
  {
    imurunTask((void *)NULL);
  }
} // Code above is plain setup

void imurunTask(void *parameters)
{
  if (myIMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0X01)
  {
    // Add a print statement to check for inside the loop
    myIMU.readAccelData(myIMU.accelCount); // Read the x/y/z adc values

    myIMU.ax = (float)myIMU.accelCount[0] * myIMU.aRes; // - myIMU.accelBias[0];
    myIMU.ay = (float)myIMU.accelCount[1] * myIMU.aRes; // - myIMU.accelBias[1];
    myIMU.az = (float)myIMU.accelCount[2] * myIMU.aRes; // - myIMU.accelBias[2];

    myIMU.readGyroData(myIMU.gyroCount); // Read the x/y/z adc values

    myIMU.gx = (float)myIMU.gyroCount[0] * myIMU.gRes;
    myIMU.gy = (float)myIMU.gyroCount[1] * myIMU.gRes;
    myIMU.gz = (float)myIMU.gyroCount[2] * myIMU.gRes;

    myIMU.readMagData(myIMU.magCount); // Read the x/y/z adc values

    myIMU.mx = (float)myIMU.magCount[0] * myIMU.mRes * myIMU.factoryMagCalibration[0] - myIMU.magBias[0];
    myIMU.my = (float)myIMU.magCount[1] * myIMU.mRes * myIMU.factoryMagCalibration[1] - myIMU.magBias[1];
    myIMU.mz = (float)myIMU.magCount[2] * myIMU.mRes * myIMU.factoryMagCalibration[2] - myIMU.magBias[2];
  }

  myIMU.updateTime();

  MahonyQuaternionUpdate(myIMU.ax, myIMU.ay, myIMU.az, myIMU.gx * DEG_TO_RAD,
                         myIMU.gy * DEG_TO_RAD, myIMU.gz * DEG_TO_RAD, myIMU.my,
                         myIMU.mx, myIMU.mz, myIMU.deltat);

  if (!AHRS)
  {
    myIMU.delt_t = millis() - myIMU.count;
    if (myIMU.delt_t > 500)
    {
      if (SerialDebug)
      {
        // Print acceleration values in milligs!
        Serial.print("X-acceleration: ");
        Serial.print(String((1000 * myIMU.ax)));
        Serial.print(" mg ");
        Serial.print("Y-acceleration: ");
        Serial.print(String(1000 * myIMU.ay));
        Serial.print(" mg ");
        Serial.print("Z-acceleration: ");
        Serial.print(String(1000 * myIMU.az));
        Serial.println(" mg ");

        // Print gyro values in degree/sec
        Serial.print("X-gyro rate: ");
        Serial.print(String((myIMU.gx, 3)));
        Serial.print(" degrees/sec ");
        Serial.print("Y-gyro rate: ");
        Serial.print(String(myIMU.gy, 3));
        Serial.print(" degrees/sec ");
        Serial.print("Z-gyro rate: ");
        Serial.print(String(myIMU.gz, 3));
        Serial.println(" degrees/sec");

        // Print mag values in degree/sec
        Serial.print("X-mag field: ");
        Serial.print(String(myIMU.mx));
        Serial.print(" mG ");
        Serial.print("Y-mag field: ");
        Serial.print(String(myIMU.my));
        Serial.print(" mG ");
        Serial.print("Z-mag field: ");
        Serial.print(String(myIMU.mz));
        Serial.println(" mG");

        myIMU.tempCount = myIMU.readTempData(); // Read the adc values
        // Temperature in degrees Centigrade
        myIMU.temperature = ((float)myIMU.tempCount) / 333.87 + 21.0;
        // Print temperature in degrees Centigrade
        Serial.print("Temperature is ");
        Serial.print(String(myIMU.temperature, 1));
        Serial.println(" degrees C");
      }
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    myIMU.count = millis();
  }
  else
  {
    myIMU.delt_t = millis() - myIMU.count;
    if (myIMU.delt_t > 500)
    {
      if (SerialDebug)
      {
        Serial.print("ax = ");
        Serial.print(String((int)1000 * myIMU.ax));
        Serial.print(" ay = ");
        Serial.print(String((int)1000 * myIMU.ay));
        Serial.print(" az = ");
        Serial.print(String((int)1000 * myIMU.az));
        Serial.println(" mg");

        Serial.print("gx = ");
        Serial.print(String((myIMU.gx, 2)));
        Serial.print(" gy = ");
        Serial.print(String(myIMU.gy, 2));
        Serial.print(" gz = ");
        Serial.print(String(myIMU.gz, 2));
        Serial.println(" deg/s");

        Serial.print("mx = ");
        Serial.print(String((int)myIMU.mx));
        Serial.print(" my = ");
        Serial.print(String((int)myIMU.my));
        Serial.print(" mz = ");
        Serial.print(String((int)myIMU.mz));
        Serial.println(" mG");

        Serial.print("q0 = ");
        Serial.print(String(*getQ()));
        Serial.print(" qx = ");
        Serial.print(String(*(getQ() + 1)));
        Serial.print(" qy = ");
        Serial.print(String(*(getQ() + 2)));
        Serial.print(" qz = ");
        Serial.println(String(*(getQ() + 3)));
      }
    }
    myIMU.count = millis();
    myIMU.sumCount = 0;
    myIMU.sum = 0;
  }
  vTaskDelete(NULL);
}