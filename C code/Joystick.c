/*
 * Anthony Bartman
 * 4/6/19
 * Dr. Livingston
 * Function:
 * This class has all of the logic for many methods regarding
 * the joystick which controls on the camera shield
 */

#include "Joystick.h"

//Pointers to joystick
volatile alt_u32* joystickSequencer = (alt_u32*) JOYSTICK_ADC_SEQUENCER_CSR_BASE;
volatile alt_u32* joystickCH1 = (alt_u32*) CH1_SAMPLE;
volatile alt_u32* joystickCH2 = (alt_u32*) CH2_SAMPLE;
//File Variables
int enableJoystick = 0;
int data = 0;

//Eventually probably toggle it with button press maybe
void toggleJoystick(){
	if (enableJoystick == 0) { //Enable Joystick
		enableJoystick = 1;
		//Continuous Joystick Mode
		*joystickSequencer = 0x00;
		//Run sequence operation
		*joystickSequencer = 0b1;
	} else { //Disable Joystick
		enableJoystick = 0;
		//Disable Sequence operation Mode
		*joystickSequencer = 0b0;
	}
}

//Gets the X-position of Joystick
int getJoystickX(){
	if(enableJoystick == 1){
		data = *(joystickCH1);
		data &= ~(0xFFFFF000);
		return data;
	}
	return 255; //if Joystick is not enabled
}

//Gets the Y-position of Joystick
int getJoystickY(){
	if (enableJoystick == 1) {
		data = *(joystickCH2);
		data &= ~(0xFFFFF000);
		return data;
	}
	return 255; //If Joystick is not enabled
}

//Change a raw joystick value to a servo position value
int joystickToPos(int joystickData){
	if(enableJoystick == 1){
		return joystickData/20;
	}
	return 255; //If Joystick is not enabled
}
