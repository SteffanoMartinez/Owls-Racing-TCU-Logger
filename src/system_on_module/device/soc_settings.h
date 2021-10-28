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

//********************************************************     CPU SPEED     ********************************************************/
#define CPU_CLK_FREQUENCY_MHz

//********************************************************     BUS SPEEDS    ********************************************************/

//* UART
#define UART0_BAUD_RATE

//* eMMC
#define eMMC_CLK_FREQUENCY_MHz

//* SPI
#define VSPI_CLCK_FREQUENCY_MHz 40000

//* I2C
#define I2C0_CLK_FREQUENCY_KHz 4


//* I2C_0 & I2C_1
#define I2C0_CLK_FREQUENCY_KHz 400
#define I2C1_CLK_FREQUENCY_KHz 400
//********************************************************     CPU SPEED     ********************************************************/