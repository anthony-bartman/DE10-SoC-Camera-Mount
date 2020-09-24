/*
 * Anthony Bartman
 * 3/8/19
 * Dr. Livingston
 * Function:
 * This method will hold all the method and variables used in the
 * SevenSegs.c file
 */
#ifndef SEVENSEGS_H_
#define SEVENSEGS_H_

#include "alt_types.h"
#include "system.h"

/*
 * This method will read the value of which switches are enabled or
 * not
 */
int readSwitches();

/*
 * This method will clear the 7seg display
 */
void clearDisplay();

/*
 * This method will set a number between 0-9 to one of the 6 hex
 * displays
 */
void setDisplay(int num,int hexDisplay);

/*
 * This method will display a number ranging from 0-999999 on
 * the 7seg displays
 */
void displayNum(int num);

/*
 * This method will check if a button is pressed or not
 */
int checkKey();

#endif
