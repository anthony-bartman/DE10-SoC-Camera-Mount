/*
 * Anthony Bartman
 * 4/6/19
 * Dr. Livingston
 * Function:
 * This method will hold all the method and variables used in the
 * Joystick.h file
 */
#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <stdlib.h>
#include "alt_types.h"
#include "system.h"

//Constants
#define CH1_SAMPLE 0xFF200400
#define CH2_SAMPLE 0xFF200404

/*
 * This method will enable or disable the joystick
 * Sets ADC to continuous mode
 */
void toggleJoystick();

/*
 * This method will get the X-Value for the joystick
 * Returns a position value between 0-4000
 */
int getJoystickX();

/*
 * This method will get the Y-Values for the joystick
 * Returns a position value between 0-4000
 */
int getJoystickY();

/*
 * This method will take in a raw joystick value and
 * return a servo position value between 0 and 200.
 */
int joystickToPos(int joystickData);

#endif
