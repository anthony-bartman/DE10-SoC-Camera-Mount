/*
 * Sample Camera Shield API code
 *
 * Function:
 * This method will show an example of using methods from the Camera
 * Shield API.
 */

#include "Camera.h"
#include "Accelerometer.h"
#include "Joystick.h"
#include "Servo.h"
#include "SevenSegs.h"

//Main method runs the program
int main() {
	//Shows user a help menu
	helpScreen();

	//Begin a sample API console based application
	while(1){
		//Shows X or Y data on hex displays
		int switch0 = 0;
		//Joystick
		int joystickX = 0;
		int joystickY = 0;
		//Acceleromter
		int accelX = 0;
		int accelY = 0;
		//Camera
		int reg = 0; //Register to read or write
		int data = 0; //Data to be read or written
		int* dataPointer = data;
		int validReg = 0;
		int retVal = 0; //Determines if read or write was successful
		char userKey; //Handles what user types in

		//Prompts User
		printf("Enter a key command: ");
		scanf(" %c", &userKey);

		if (userKey == 'w') { //Write memory
			clearDisplay(); //Clear seven Segs displays
			toggleCamera(); //Activate Camera
			printf(" - Camera API Activated - \n");
			validReg = 0;
			while(!validReg){
				//Enter in data and register
				printf("Enter register value: ");
				scanf(" %d",&reg);
				//Checks if register is in the range
				if(reg <= 0x39 && reg >= 0){
					validReg = 1;
					printf("Enter data to be written: ");
					scanf(" %d",&data);
				} else {
					printf("Invalid register value\n");
					printf("Must be in between 0x00(0) and 0x39(57)\n\n");
				}

			}
			//Do a cam write
			retVal = camWrite(reg, data);
			if (retVal == 1) { //Failed to write
				printf("Error writing data\n");
			} else { //Successful write
				printf("Successfully wrote: %d to memory! \n", data);
			}
			toggleCamera(); //Deactivate Camera
			printf(" - Camera API Deactivated - \n");
		} else if(userKey == 'r'){	//Read memory
			clearDisplay(); //Clear seven Segs displays
			toggleCamera();
			printf(" - Camera API Activated - \n");
			validReg = 0;
			while(!validReg){
			//Enter in data and register
				printf("Enter register value: ");
				scanf(" %d",&reg);
			//Checks if register is in the range
				if(reg <= 0x39 && reg >= 0){
					validReg = 1;
					printf("Enter data to be read: ");
					scanf(" %d",&data);
				} else {
					printf("Invalid register value\n");
					printf("Must be in between 0x00 and 0x39\n");
				}
			}
			//Points to data wanted to be read
			*dataPointer = data;
			retVal = camRead(reg, *dataPointer);
			if (retVal >= 1) { //Failed to read
				printf("Error reading data\n");
			} else { //Successful Write
				printf("Successfully read: %d from memory! \n", data);
			}
			toggleCamera();
			printf(" - Camera API Deactivated - \n");
		} else if(userKey == 'a'){
			clearDisplay(); //Clear seven Segs displays
			toggleAccelerometer();
			toggleServo();
			printf(" - Accelerometer API Activated - \n");
			//Grabs Acceleromter Values
			accelX = accelToPos(getAccelX());
			accelY = accelToPos(getAccelY());

			//Set servo positions
			setPosition(top,accelX);
			setPosition(base,accelY);

			//Displays X or Y values to Hex displays based on switches
			switch0 = readSwitches();
			//Clears all bits except the first 2 bits
			switch0 &= ~(0xFFFE);
			if(switch0 == 0){ //X value
				setDisplay(1,5);
				displayNum(accelX);
			} else if(switch0 == 1){ //Y Value
				setDisplay(2,5);
				displayNum(accelY);
			}
			//Delay to see accelerometer values change on hex displays
			usleep(100000);
			toggleAccelerometer();
			toggleServo();
			printf(" - Accelerometer API Deactivated - \n");
		} else if(userKey == 'j'){
			clearDisplay(); //Clear seven Segs displays
			toggleJoystick();
			toggleServo();
			printf(" - Joystick API Activated - \n");
			//Gets raw joystick values
			joystickX = getJoystickX();
			joystickY = getJoystickY();

			//Sets servo position to move based on joystick orientation
			setPosition(top, joystickToPos(joystickY));
			setPosition(base, joystickToPos(joystickX));

			//Handles the displaying of actual values from ADC
			switch0 = readSwitches();
			switch0 &= ~(0xFFFE);
			if(switch0 == 0){ //Shows X values
				setDisplay(1,5); //Sets the number 1 to 7seg display #5
				displayNum(joystickX);
			} else { //Shows Y values
				setDisplay(2,5); //Sets the number 2 to 7seg display #5
				displayNum(joystickY);
			}
			//Delay to see ADC values change on hex displays
			usleep(100000);
			toggleJoystick();
			toggleServo();
			printf(" - Joystick API Deactivated - \n");
		} else if(userKey == 's'){
			clearDisplay(); //Clear seven Segs displays
			toggleServo();
			printf(" - Servo API Activated - \n");
			//Reset Servos to base position
			resetPos(both);
			usleep(100000);

			//Random Positions
			for(int i = 0; i<10;i++){
				randomPos(both);
				usleep(100000); //1 second delay
			}

			//Sets top servo to be looking forward
			setPosition(top, 30);
			resetPos(base);
			//Make a Panning motion with servos
			for (int i = 0; i < 9; i++) {
				rotate(10*i, right);
				usleep(100000); //1 second delay
			}

			toggleServo();
			printf(" - Servo API Deactivated - \n");
		} else if(userKey == 'h'){
			helpScreen();
		} else {
			printf("Invalid Entry\n");
		}
	}
	return 0;
}

//Helper Methods
//Used to show user all different key commands
void helpScreen(){
	printf("-----------------------------------\n");
	printf(" 'w' : Write to camera register\n");
	printf(" 'r' : Read from camera register\n");
	printf(" 'a' : Activate accelerometer\n");
	printf(" 'j' : Activate joystick\n");
	printf(" 's' : Activate servos\n");
	printf(" 'h' : Show help screen\n");
	printf("-----------------------------------\n");
}
