#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     touchmux,       sensorHiTechnicTouchMux)
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
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#define mux_button1 0x01
#define mux_button2 0x02
#define mux_button3 0x04
#define mux_button4 0x08

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
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
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  initializeRobot();

  waitForStart();   // wait for start of tele-op phase

  while (true)
  {


 if(joystick.joy1_y1>-10 && joystick.joy1_y1<10)
 {
	motor(motorDriveLeft1) = 0;
  motor(motorDriveLeft2) = 0;

 }
else
 {
	motor(motorDriveLeft1) = joystick.joy1_y1;
  	motor(motorDriveLeft2) = joystick.joy1_y1;
 }




 if(joystick.joy1_y2>-10 && joystick.joy1_y2<10)
 {
  motor(motorDriveRight1)=0;
    motor(motorDriveRight2)=0;

 }
 else
 {
	motor(motorDriveRight1) = joystick.joy1_y2;
	motor(motorDriveRight2) = joystick.joy1_y2;

 }


if(SensorValue(touchmux) & mux_button1)
{
	if(joystick.joy2_y1 >0)
	{
	   	motor[motorArm]=0;
  }
  else
  {
  	 motor[motorArm]=joystick.joy2_y1;
  }
}
else if(SensorValue(touchmux) & mux_button2)
{
	if(joystick.joy2_y1 <0)
	{
	motor[motorArm]=0;
  }
  else
  {
   motor[motorArm]=joystick.joy2_y1;
  }
}
else
{
	motor[motorArm]=joystick.joy2_y1;
}





 if(SensorValue(touchmux) & mux_button3)
 {
   if(joystick.joy2_y2 >0)
   {
  motor[motorArmUp] =0;
   }
   else
   {
  motor[motorArmUp] = joystick.joy2_y2/2;
    }
}
else if(SensorValue(touchmux) & mux_button4)
{
	if(joystick.joy2_y2 <0)
	{
	motor[motorArmUp]=0;
  }
  else
  {
   motor[motorArmUp]=joystick.joy2_y2;
  }
}
else
{
	motor[motorArmUp]=joystick.joy2_y2;
}



 /*if(joystick.joy2_y1<-10)
 {
    if(SensorValue(Touch1) == 1)
     {

     motor[motorArm]=0;
    }
   else
    {
    motor[motorArm] = joystick.joy2_y1;         // Motor D is assigned a power level equal to the right analog stick's Y-axis reading.

 }

 if(joystick.joy2_y1>10)
   {
   if(SensorValue(Touch2)== 1)
     {
	 motor[motorArm] = 0;

     }
   else
     {
     // Motor D is assigned a power level equal to the right analog stick's Y-axis reading.
   motor[motorArm] = joystick.joy2_y1;
     }
   }

 if(joystick.joy2_y1<10 && joystick.joy2_y1>-10)
  {
   motor[motorArm]=0;
  }*/





/*
if(joystick.joy2_y2>-10 && joystick.joy2_y2<10)
 {
	motor(motorArmUp) = 0;
 }
else
 {
	motor(motorArmUp) = joystick.joy2_y2/2 ;
 }*/




    if(joy2Btn(5))          // If Button 5 is pressed:
    {
     motor(motorBucket) = 100;
     wait1Msec(100);
     motor(motorBucket) = 0;
      }
   else
   {
     if(joy2Btn(6))          // If Button 6 is pressed:
      {
     motor(motorBucket) = -100;
     wait1Msec(100);
     motor(motorBucket) = 0;
       }
   }


   if(joy1Btn(5))
   {
     motor(motorFlag) = 100;
     wait1Msec(100);
     motor(motorFlag) = 0;
   // Motor E is assigned a power level equal to the left analog stick's Y-axis reading.
   }
   if(joy1Btn(6))
   {
     motor(motorFlag) = -100;
     wait1Msec(100);
     motor(motorFlag) = 0;
   // Motor E is assigned a power level equal to the left analog stick's Y-axis reading.
   }
}   // BUTTONS TO CONTOL SERVO ARM
    // Control arm via shoulder buttons, 5 and 6... 5=up, 6=down
}