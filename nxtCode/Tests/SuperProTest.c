#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IRSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     HTSPB,          sensorI2CCustom9V)
#pragma config(Motor,  motorA,          A,             tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          B,             tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        tmotorTetrix, openLoop, reversed, driveLeft, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorR,        tmotorTetrix, openLoop, driveRight, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     armUp1,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     armUp2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     armFlip,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    backArm,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "../Drivers/hitechnic-superpro.h"

bool readLims(int x){
	ubyte mask=0b00000001<<x;
	return(HTSPBreadIO(HTSPB, mask)!=0);
}

task main(){
	motor[armFlip]=20;
	while(true){
		writeDebugStreamLine("%d",readLims(0));
		wait1Msec(100);
	}
}
