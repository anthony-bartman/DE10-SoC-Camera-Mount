/*
 * Anthony Bartman
 * 4/27/19
 * Dr. Livingston
 * Function:
 * This method will hold all the method and variables used in the
 * Accelerometer.h file
 */
#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include <stdio.h>
#include <stdlib.h>
#include "alt_types.h";
#include "system.h";

//Base Addresses
#define ACCEL_ADDR 0xff2000b0
#define ACCEL_DATA 0xff2000b1
//Data Register Offsets
#define DATA_X0 0x32
#define DATA_X1 0x33
#define DATA_Y0 0x34
#define DATA_Y1 0x35
#define DATA_Z0 0x36
#define DATA_Z1 0x37

/*
 *	This method enables or disables the accelerometer
 */
void toggleAccelerometer();

/*
 *  This method will gather the x-value of the accelerometer
 *  and return that raw accelerometer data. The returned
 *  value in this method will be inverted so the servo will
 *  move based on the tilting of the board.
 */
int getAccelX();

/*
 *  This method will gather the y-value of the accelerometer
 *  and return the raw accelerometer data
 */
int getAccelY();

/*
 *  This method will gather the z-value of the accelerometer
 *  and return the raw accelerometer data
 */
int getAccelZ();

/*
 *  This method convert the raw accelData to a servo position
 *  value from 0 to 200.
 */
int accelToPos(int accelData);

#endif
