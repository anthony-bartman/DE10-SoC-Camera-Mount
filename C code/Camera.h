/*
 * Anthony Bartman
 * 5/15/19
 * Dr. Livingston
 * Function:
 * This method will hold all the method and variables used in the
 * Camera.h file
 */
#ifndef CAMERA_H_
#define CAMERA_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "alt_types.h"
#include "system.h"
//Hardware Abstraction Layer Library
#include "altera_avalon_i2c.h"

//Constants
#define CAMERA_ADDR 0xFF2000C0
#define CAMERA_DATA 0xFF2000C1

/*
 * This method will enable or disable the camera if the correct directory
 * can be found. To actually initialize the camera, this method uses the
 * hardware abstraction layer.
 */
int toggleCamera();

/*
 * This method will write to a specific register in the camera memory by
 * using altera's hardware abstraction layer.
 */
int camWrite(alt_u8 addr, alt_u8 data);

/*
 * This method will read from a specific register in the camera memory by
 * using altera's hardware abstraction layer.
 */
int camRead(alt_u8 addr,alt_u8* data);

#endif
