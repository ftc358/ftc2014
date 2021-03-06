#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorUsed,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

int threshold = 3;                                           //threshold
float power = 2.25;
void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}
int MotorValue(float joyInput){                              //exponential function
	float tInputV = abs(joyInput);
	float tMotorValue = pow(tInputV, power);
	tMotorValue *= (128/pow(128, power));
	return tMotorValue;
}
task main()
{
	initializeRobot();
	waitForStart();															//get joystick settings
	while(true){
		getJoystickSettings(joystick);
			if(abs(joystick.joy1_y1) > threshold){
				if(joystick.joy1_y1 > 0){
					motor[motorUsed] = MotorValue(joystick.joy1_y1);
				}else{
					motor[motorUsed] = -MotorValue(joystick.joy1_y1);
				}
			}else{
				motor[motorUsed] = 0;
			}
  }
}
