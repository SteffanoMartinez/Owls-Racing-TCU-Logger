#pragma once
/*
* Company: ANZE Suspension
* File Name: main.cpp
* Project: ESP32 System on Module
* Version: 1.0
* Compartible Hardware: REV1.0
* Date Created: September 23, 2021
* Last Modified: September 23, 2021
*/

//*********************************************************     READ ME    **********************************************************/

//*     All settings related to the esp hardware go here (buses speeds, cpu speed, etc)

//***********************************************************************************************************************************/

//********************************************************     APP GPIO     *********************************************************/

//* MCU
#define MCU_EN_PIN

//* VSPI
#define VSPI_MOSI_PIN 23
#define VSPI_MISO_PIN 19
#define VSPI_CLCK_PIN 18

//* HSPI
#define HSPI_MOSI_PIN 25
#define HSPI_MISO_PIN 17
#define HSPI_CLCK_PIN 16

//* eMMC Memory
#define eMMC0_EN_PIN_EXT -1
#define eMMC0_CD_PIN_EXT -1

//* CAN bus
#define CAN0_CONTROLLER_CS_PIN 27
#define CAN0_CONTROLLER_INT_PIN 36
#define CAN0_CONTROLLER_EN_PIN_EXT 5

//* ADC
#define ADC0_EN_PIN_EXT 4

//* IMU
#define IMU_EN_PIN_EXT 8

//* I2C_0
#define I2C0_SDA_PIN 21
#define I2C0_SCL_PIN 22

//* I2C_1
#define I2C1_SDA_PIN 4
#define I2C1_SCL_PIN 5

//* Internal GPIO's
#define GPIO34_PIN 34
#define GPIO26_PIN 26
#define GPIO27_PIN 27
#define GPIO12_PIN 12
#define GPIO13_PIN 13

//* External GPIO's
#define GPIO10_PIN_EXT 10
#define GPIO11_PIN_EXT 11
#define GPIO12_PIN_EXT 12
#define GPIO13_PIN_EXT 13
#define GPIO14_PIN_EXT 14
#define GPIO15_PIN_EXT 15

//* Power
#define P_5V_EN_PIN_EXT 9

//* End.