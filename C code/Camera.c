/*
 * Anthony Bartman
 * 5/15/19
 * Dr. Livingston
 * Function:
 * This class has all of the logic for many methods regarding
 * the reading and writing to registers for the camera on the
 * DE-10 board
 */

#include "Camera.h"

//Pointers for reading and writing to camera registers
ALT_AVALON_I2C_DEV_t *i2c_dev;
ALT_AVALON_I2C_STATUS_CODE status;
int enableCamera = 0;

//This method will toggle the accelerometer's default settings and enable other methods
int toggleCamera() {
	if(enableCamera == 0){ //Enables Camera
		enableCamera = 1;
		i2c_dev = alt_avalon_i2c_open("/dev/i2c_0");
		//If i2c_dev is NULL, that means it could not find the correct director for i2c
		if(NULL == i2c_dev){
			printf("Error: Cannot find /dev/i2c_0\n");
			return 1;
		}
		//set the address of the device using
		alt_avalon_i2c_master_target_set(i2c_dev,0x21);
		return 0;
	} else {  		//Disables Camera
		enableCamera = 0;
		return 0;
	}
}

//This method will perform a 3-phase transmission cycle by taking in a
//register and a value to be written to a camera register. The hardware
//abstraction layer will be used to write to camera registers
int camWrite(alt_u8 addr, alt_u8 data){
	int status; //Holds whether the write will be successful or not
	alt_u8 txbuf[2]; //Holds the transmit buffer in order to write to a camera register
	txbuf[0]= addr;
	txbuf[1]= data;

	//Altera method to write data to the camera register indicated by the user
	status = alt_avalon_i2c_master_tx(i2c_dev,txbuf, 2, ALT_AVALON_I2C_NO_INTERRUPTS);
	if (status!=ALT_AVALON_I2C_SUCCESS){
		return 1; //FAIL
	}
	//Success
	return 0;
}

//This method will perform a 2-phase write cycle and then a 2-phase read cycle
//by taking in a register and a data pointer to verify that this value is at
//the indicated register. This is performed by a method from altera's hardware
//abstraction layer.
int camRead(alt_u8 addr, alt_u8* data){
	//Holds whether the camera was written or read from successfully
	int status;
	//Try to set up a transmission/write data to camera
	status = alt_avalon_i2c_master_tx(i2c_dev, &addr, 1, ALT_AVALON_I2C_NO_INTERRUPTS);
	if (status!=ALT_AVALON_I2C_SUCCESS){
		return 1; //FAIL
	}
	//Try to read the data from the camera
	status = alt_avalon_i2c_master_rx(i2c_dev, *data, 1, ALT_AVALON_I2C_NO_INTERRUPTS);
	if (status!=ALT_AVALON_I2C_SUCCESS){
		return 2; //FAIL
	}
	//Success
	return 0;
}
