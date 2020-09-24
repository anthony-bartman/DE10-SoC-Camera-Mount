/*
 * Anthony Bartman
 * 4/27/19
 * Dr. Livingston
 * Function:
 * This class has all of the logic for many methods regarding
 * the accelerometer on the DE-10 board
 */

#include "Accelerometer.h"

//Pointers to Accelerometer registers
volatile alt_16* accelAddr = (alt_16*) ACCEL_ADDR;
volatile alt_16* accelData = (alt_16*) ACCEL_DATA;
int enableAccelerometer = 0;

//File static methods
static int signExt(int num);

//This method will toggle the accelerometer's default settings and enable other methods
void toggleAccelerometer() {
	if(enableAccelerometer == 0){ //Enables Accelerometer
		enableAccelerometer = 1;
	} else {  		//Disables Accelerometer
		enableAccelerometer = 0;
	}
}

//Gets accelerometer x-data
int getAccelX(){
	if(enableAccelerometer == 1){
		alt_8 x0 = 0;
		alt_8 x1 = 0;
		//Gets Part 1 of X values
		*accelAddr = DATA_X0;
		//Orr 0's to make it 8 bits with leading ones
		x0 = 0x00|*accelData;
		//gets part2 of X values
		*accelAddr = DATA_X1;
		x1 = 0x00|*accelData;
		//x1 is Most Significant Bit
		x1 &= ~(0xFC);
		alt_16 xTotal = (x1<<8)|(x0);
		//Inverted so servos will adjust based on tilt
		return 200 - signExt(xTotal);
	}
	//Return 0 if accelerometer is not enabled
	return 0;
}

//Gets accelerometer y-data
int getAccelY(){
	if(enableAccelerometer == 1){
		alt_8 y0 = 0;
		alt_8 y1 = 0;
		//Gets Part 1 of Y values
		*accelAddr = DATA_Y0;
		//Orr 0's to make it 8 bits with leading ones
		y0 = 0x00|*accelData;
		//gets part2 of X values
		*accelAddr = DATA_Y1;
		y1 = 0x00|*accelData;
		//y1 is Most Significant Bit
		y1 &= ~(0xFC);
		alt_16 yTotal = (y1<<8)|(y0);
		return signExt(yTotal);
	}
	//Return 0 if accelerometer is not enabled
	return 0;
}

//Gets acclereomter z-data
int getAccelZ(){
	if(enableAccelerometer == 1){
		alt_8 z0 = 0;
		alt_8 z1 = 0;
		//Gets Part 1 of X values
		*accelAddr = DATA_Z0;
		//Orr 0's to make it 8 bits with leading ones
		z0 = 0x00|*accelData;
		//gets part2 of Z values
		*accelAddr = DATA_Z1;
		z1 = 0x00|*accelData;
		//z1 is Most Significant Bit
		z1 &= ~(0xFC);
		alt_16 zTotal = (z1<<8)|(z0);
		return signExt(zTotal);
	}
	//Return 0 if accelerometer is not enabled
	return 0;
}

//Changes the accelerometer Data to a Servo Position
int accelToPos(int accelData){
	if(enableAccelerometer == 1){
		if(accelData < 0){
			accelData += 255;
			return (accelData * 200) / 512;
		} else {
		accelData += 256;
		return (accelData * 200) / 512;
		}
	} else {
		//accelerometer is not enabled
		return 0;
	}
}

//Helper Methods
//Sign extends the number if it is negative
int signExt(int num){
	if(num & (0b1 << 9) == 0b1){
		return (int)(num | 0xFE00);
	}
	return (int)num;
}
