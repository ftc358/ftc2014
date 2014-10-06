#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorR,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

int threshold = 3;
int armThreshold = 3;
float power = 2.25;

int MotorValue(float joyInput){
	float tInputV = abs(joyInput);
	float tMotorValue = pow(tInputV, power);
	tMotorValue *= (128/pow(128, power));
	return tMotorValue;
}

task main()
{
	getJoystickSettings(joystick);

	while(true){

		//Wheels
		if(abs(joystick.joy1_y1) > threshold){
			if(joystick.joy1_y1 > 0){
				motor[motorL] = MotorValue(joystick.joy1_y1);
			}else{
				motor[motorL] = -MotorValue(joystick.joy1_y1);
			}
		}else{
			motor[motorL] = 0;
		}
		if(abs(joystick.joy1_y2) > threshold){
			if(joystick.joy1_y2 > 0){
				motor[motorR] = MotorValue(joystick.joy1_y2);
			}else{
				motor[motorR] = -MotorValue(joystick.joy1_y2);
			}
		}else{
			motor[motorR] = 0;
		}
	}
}
