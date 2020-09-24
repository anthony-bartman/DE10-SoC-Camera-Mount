/*
 * Anthony Bartman
 * 4/6/19
 * Dr. Livingston
 * Function:
 * This class has all of the logic for many methods regarding
 * the two servos on the camera shield
 */

#include "Servo.h"

//Pointers to servos
//Top Servo
volatile alt_u32* servoTop = (alt_u32*) SERVO1_BASE;
//Bottom Servo
volatile alt_u32* servoBase = (alt_u32*) SERVO2_BASE;
int enableServos = 0;
Direction direction = off;

//File static methods
static int degreesToPos(int degrees);

//Rotates a camera shield a direction and a degree amount
void rotate(int degrees, Direction direction) {
	if (enableServos != 0) {
		//Only between 0 and 90 degrees
		if (degrees <= 90 && degrees >= 0) {
			switch (direction) {
			case up:
				*servoTop = (200 - degreesToPos(degrees));
				break;
			case down:
				*servoTop = (degreesToPos(degrees));
				break;
			case left:
				*servoBase = (degreesToPos(degrees));
				break;
			case right:
				*servoBase = (200 - degreesToPos(degrees));
				break;
			default:
				break;
			}
		}
	}
}

//Sets servo position
void setPosition(Servo servoSel, int pos) {
	if (enableServos != 0) {
		//Position between 0 and 200
		if (pos <= 200 && pos >= 0) {
			switch (servoSel) {
			case both:
				*servoTop = pos;
				*servoBase = pos;
				break;
			case top:
				*servoTop = pos;
				break;
			case base:
				*servoBase = pos;
				break;
			default:
				break;
			}
		}
	}
}

//Resets a servo's position to a position
void resetPos(Servo servoSel){
	if(enableServos != 0){
		//Make sure you are selecting the correct number for servos
		if(servoSel >= 0 && servoSel <= 2){
			switch (servoSel) {
			case both:
				*servoTop = SERVO1_RESETPOS;
				*servoBase = SERVO2_RESETPOS;
				break;
			case top:
				*servoTop = SERVO1_RESETPOS;
				break;
			case base:
				*servoBase = SERVO2_RESETPOS;
				break;
			default:
				break;
			}
			direction = off;
		}
	}
}

//Sets a servo to a random position
void randomPos(Servo servoSel) {
	if (enableServos != 0) {
		//Random pos between 0-200
		if (servoSel >= 0 && servoSel <= 2) {
			int pos = 201;
			switch(servoSel){
			case both:
				pos = rand() % 200 + 0;
				*servoTop = pos;
				pos = rand() % 200 + 0;
				*servoBase = pos;
				break;
			case top:
				pos = rand() % 200 + 0;
				*servoTop = pos;
				break;
			case base:
				pos = rand() % 200 + 0;
				*servoBase = pos;
				break;
			default:
				break;
			}
		}
	}
}

//Enable's Servo methods
void toggleServo() {
	if (enableServos == 0) { //Enable Servos to move
		enableServos = 1;
		resetPos(0);
	} else { //Disable Servos
		resetPos(0); //Places servos to the starting position
		enableServos = 0;
		*servoTop = 201;
		*servoBase = 201;
		direction = off;
	}
}


//Helper Methods
//Change rotation in degrees to position
int degreesToPos(int degrees) {
	return (degrees * 200) / (90);
}
