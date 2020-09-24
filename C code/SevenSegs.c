/*
 * Anthony Bartman
 * 4/6/19
 * Dr. Livingston
 * Function:
 * This method will deal with all physical inputs on the
 * DE-10 lite board. This file can display numbers to the
 * 7 segdisplay, based on switches or a number and can tell
 * if a button is pressed or not
 */

#include "SevenSegs.h"

//7 Segment Displays  GOES from HEX6 -> HEX0
volatile alt_u32* hex03 = (alt_u32*) HEX3_HEX0_BASE;
volatile alt_u32* hex45 = (alt_u32*) HEX5_HEX4_BASE;
//Switches
volatile alt_u16* switch09 = (alt_u16*) SLIDER_SWITCHES_BASE;
//PushButtons
volatile alt_u8* key12 = (alt_u8*) PUSHBUTTONS_BASE;
//Array to store all numbers on 7seg
alt_u8 nums[10] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
		0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111 };

//This method will read the number switches that are enabled
int readSwitches() {
	*switch09 &= ~(0xFC00);
	return *switch09;
}

//Clears the 7seg displays
void clearDisplay() {
	*hex03 = 0;
	*hex45 = 0;
}

//Sets a display to a number between 0-9
void setDisplay(int num,int hexDisplay){
	if(num >= 0 && num <= 9){
		if(hexDisplay == 0){
			*hex03 = nums[num];
		} else if(hexDisplay == 1){
			*hex03 = nums[num] << 8;
		} else if(hexDisplay == 2){
			*hex03 = nums[num] << 16;
		} else if(hexDisplay == 3){
			*hex03 = nums[num] << 24;
		} else if(hexDisplay == 4){
			*hex45 = nums[num];
		} else if(hexDisplay == 5){
			*hex45 = nums[num] << 8;
		}
	}
}

//Checks if one of the buttons are pressed
int checkKey() {
	return (*key12 &= ~(0xFC));
}

//This will display a number from 0-999999 to the screen
void displayNum(int num) {
	int initialNum = num;
	//Number to send to 7seg display
	int endnum = 0;
	//Using hex45
	int hthous = nums[num/100000];
	if (hthous != nums[0]) {
		endnum |= (hthous << 8);
	}
	num -= (num / 100000) * 100000;
	int tthous = nums[num/10000];
	if (tthous == nums[0] && hthous != nums[0]|| tthous != nums[0]) {
		endnum |= (tthous);
	}
	num -= (num / 10000) * 10000;
	//Checks if number is bigger than 9999, to not clear out the hex45
	if(initialNum > 9999){
	//Display Numbers
	*hex45 = endnum;
	}
	//Using hex03
	endnum = 0;
	int thous = nums[num / 1000];
	if ((thous == nums[0] && tthous == nums[0] && hthous != nums[0]) ||
			(thous == nums[0] && tthous != nums[0]) || thous != nums[0]) {
		endnum |= (thous << 24);
	}
	num -= (num / 1000) * 1000;
	int hund = nums[num / 100];
	if (hund == nums[0] && thous == nums[0] && tthous == nums[0] && hthous != nums[0] ||
			hund == nums[0] && thous == nums[0] && tthous != nums[0] ||
			hund == nums[0] && thous != nums[0] || hund != nums[0]) {
		endnum |= (hund << 16);
	}
	num -= (num / 100) * 100;
	int tens = nums[num / 10];
	if (tens == nums[0] && hund == nums[0] && thous == nums[0] && tthous == nums[0] && hthous != nums[0] ||
			tens == nums[0] && hund == nums[0] && thous == nums[0] && tthous != nums[0] ||
			tens == nums[0] && hund == nums[0] && thous != nums[0] ||
			tens == nums[0] && hund != nums[0] || tens != nums[0]) {
		endnum |= (tens << 8);
	}
	num -= (num / 10) * 10;
	endnum |= nums[num];
	//Display Numbers
	*hex03 = endnum;
}
