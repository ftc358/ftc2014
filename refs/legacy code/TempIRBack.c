#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     IRseek,         sensorHiTechnicIRSeeker600)
#pragma config(Motor,  motorC,          motorIRarm,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorArm,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFlag,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBucket,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorArmUp,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     motorDriveRight1, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorDriveRight2, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorDriveLeft1, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     motorDriveLeft2, tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////


void move(int x, int y, int t)
{
	motor[motorDriveLeft1] = x;
	motor[motorDriveLeft2] = x;
	motor[motorDriveRight1] = y;
	motor[motorDriveRight2] = y;
	wait1Msec(t);
	motor[motorDriveLeft1] = 0;
	motor[motorDriveLeft2] = 0;
	motor[motorDriveRight1] = 0;
	motor[motorDriveRight2] = 0;
  wait1Msec(100);
}



void move2(int x, int y, int t)
{
	motor[motorDriveLeft1] = x;
	motor[motorDriveLeft2] = x;
	motor[motorDriveRight1] = y;
	motor[motorDriveRight2] = y;
	motor[motorArm]=-100;
	wait1Msec(t);
	motor[motorDriveLeft1] = 0;
	motor[motorDriveLeft2] = 0;
	motor[motorDriveRight1] = 0;
	motor[motorDriveRight2] = 0;
	motor[motorArm]=0;
  wait1Msec(100);
}

void moveArm(int x, int t)
{
	motor(motorArm)=x;
	wait1Msec(t);
	motor(motorArm)=0;
  wait1Msec(100);
}

void moveArmUp(int x, int t)
{
	motor(motorArmUp)=x;
	wait1Msec(t);
  	motor(motorArmUp)=0;
  wait1Msec(100);

}


void moveBucket(int x, int t)
{

	motor[motorBucket] = x;
	wait1Msec(t);
	motor[motorBucket]= 0;
	wait1Msec(100);
}

task main()
{
  initializeRobot();

  waitForStart(); // Wait for the beginning of autonomous phase.
 ClearTimer(T1);
	while(SensorValue[IRseek]!= 5)
	{
	motor[motorDriveLeft1] = -100;
	motor[motorDriveLeft2] = -100;
	motor[motorDriveRight1] = -70;
	motor[motorDriveRight2] = -70;
	}

	  int z = time1(T1);
   	move(0,0,400);
   	//move(35,35,200);
   	 	if(z>2000)
   	{
   		move(35,35,200);
   	}
    else if(z>1300)
  {
  	move(35,35,200);
  }
   	else
  {
  	move(-35,-35,200);
  }
    move(0,0,300);
   	motor(motorIRarm)= -100;
   	wait1Msec(650);
   	motor(motorIRarm)= 100;
    wait1Msec(800);
    motor(motorIRarm)= 0;
    wait1Msec(200);
		move(100,70,z-50);
	  move(0,0, 400);
    move(90,-90,550);
    move(100,100,1500);
    move(90,-90,750);
    move(100,100,2100);


  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  ////                                                   ////
  ////    Add your robot specific autonomous code here.  ////
  ////                                                   ////
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////

  while (true)
  {}
}
