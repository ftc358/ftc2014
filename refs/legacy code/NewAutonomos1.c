#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorArmLeft,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorArmRight, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorDriveRight, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorDriveLeft, tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	motor(motorDriveRight) =50;
	motor(motorDriveLeft)  =50;
 wait1Msec(1000);

}
