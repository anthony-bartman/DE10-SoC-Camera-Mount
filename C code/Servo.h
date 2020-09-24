/*
 * Anthony Bartman
 * 3/30/19
 * Dr. Livingston
 * Function:
 * This method will hold all the method and variables used in the
 * Servo.h file
 */
#ifndef SERVO_H_
#define SERVO_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "alt_types.h";
#include "system.h";

//Used to make programmer tell which direction to move the motors
typedef enum {off = 0, up = 1, down = 2, right = 3, left = 4} Direction;
//Used to make programmer tell which servo to move
typedef enum {both = 0, top = 1, base = 2} Servo;
//Constants
#define SERVO1_RESETPOS 30	//Top Servo
#define SERVO2_RESETPOS 100 //Bottom Servo

/*
 * This method will allow the programmer to rotate the camera a
 * certain number of degrees based on the direction it is given
 */
void rotate(int degrees, Direction direction);

/*
 * This method will allow the programmer to set the position of
 * an individual motor if desired
 */
void setPosition(Servo servoSel, int pos);

/*
 *  This method will allow the programmer to reset the current
 * position of the one or all the servos
 */
void resetPos(Servo servoSel);

/*
 * This method will allow the user to make a selected servo go
 * to a random position
 */
void randomPos(Servo servoSel);

/*
 * This method enables or disables the servos
 */
void toggleServo();

#endif
