#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     armUp1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     armUp2,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     armFlip1,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     armFlip2,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     backArm,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     Bucket,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

int threshold = 3;                                           //threshold
float power = 2.25;
int a=0;

int MotorValue(float joyInput){                              //exponential function
	float tInputV = abs(joyInput);
	float tMotorValue = pow(tInputV, power);
	tMotorValue *= (128/pow(128, power));
	return tMotorValue;
}

task main()
{	getJoystickSettings(joystick);                             //get joystick settings

	while(true){

//////////////////////////////////////////
//////////////////driving/////////////////
//////////////////////////////////////////


	  if(joy1Btn(1)==1)                                        //inverse driving button
	  	a++;
	  	if (a%2==0){
		if(abs(joystick.joy1_y1) > threshold){                   //normal driving
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
	  else {                                                    //inversed driving
	  	if(abs(joystick.joy1_y2) > threshold){
			if(joystick.joy1_y2 > 0){
				motor[motorL] = -MotorValue(joystick.joy1_y2);
			}else{
				motor[motorL] = MotorValue(joystick.joy1_y2);
			}
		}else{
			motor[motorL] = 0;
		}
		if(abs(joystick.joy1_y1) > threshold){
			if(joystick.joy1_y1 > 0){
				motor[motorR] = -MotorValue(joystick.joy1_y1);
			}else{
				motor[motorR] = MotorValue(joystick.joy1_y1);
			}
		}else{
			motor[motorR] = 0;
	  	}
	  }
	  /////////////////////////////////////////
	  ///////////arm UP&Down///////////////////
	  /////////////////////////////////////////
	  if(abs(joystick.joy2_y1) > threshold){
			if(joystick.joy2_y1 > 0){
				motor[armUp1] = MotorValue(joystick.joy2_y1);
				motor[armUp2] = MotorValue(joystick.joy2_y1);
			}else{
				motor[armUp1] = -MotorValue(joystick.joy2_y1);
				motor[armUp2] = -MotorValue(joystick.joy2_y1);
			}
			}else{
				motor[armUp1] = 0;                                    //stop arm from moving
				motor[armUp2] = 0;
		}

		//////////////////////////////////////////
		////////////Bucket Flip///////////////////
		//////////////////////////////////////////

	 	  if(abs(joystick.joy2_y2) > threshold){
			if(joystick.joy2_y2 > 0){
				motor[armFlip1] = MotorValue(joystick.joy2_y2);
				motor[armFlip2] = MotorValue(joystick.joy2_y2);
			}else{
				motor[armFlip1] = -MotorValue(joystick.joy2_y2);
				motor[armFlip2] = -MotorValue(joystick.joy2_y2);
			}
			}else{                                                  //stop arm from moving
				motor[armFlip1] = 0;
				motor[armFlip2] = 0;
		}

		///////////////////////////////////////////
		////////////Back Arm///////////////////////
		///////////////////////////////////////////

		while(joy2btn(5)==1){                                     //put backarm up
			motor[backArm]=100;
		}
		while(joy2btn(6)==1){
			motor[backArm]=-100;                                    //put backarm down
		}

		///////////////////////////////////////////
		//////////Bucket Intake&Output/////////////
		///////////////////////////////////////////

		while(joy2btn(1)==1){                                     //intake balls
			motor[Bucket]=100;
		}
		while(joy2btn(2)==1){                                     //output balls
			motor[Bucket]=-100;
		}


	}

}
