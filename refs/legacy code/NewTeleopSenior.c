#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     Touch1,         sensorTouch)
#pragma config(Sensor, S3,     Touch2,         sensorTouch)
#pragma config(Sensor, S4,     ,               sensorHiTechnicTouchMux)
#pragma config(Motor,  mtr_S1_C1_1,     motorArm,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFlag,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBucket,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorArmUp,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorDriveRight1, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorDriveRight2, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorDriveLeft1, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     motorDriveLeft2, tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                    - Tetrix Simple Tank Drive -                                        *|
|*                                          ROBOTC on Tetrix                                              *|
|*                                                                                                        *|
|*  This program allows you to drive a robot via remote control using the ROBOTC Debugger.                *|
|*  This particular method uses "Tank Drive" where each side is controlled individually like a tank.      *|
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*    NOTES:                                                                                              *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
|*    Port D                  motorD              12V                 Right motor                         *|
|*    Port E                  motorE              12V                 Left motor                          *|
\*--------------------------------------------------------------------------------------------------------*/

#include "JoystickDriver.c"
#define mux_button1 0x01
#define mux_button2 0x02
#define mux_button3 0x04
#define mux_button4 0x08

task main()
{
 while(true)                            // Infinite loop:
  {
 getJoystickSettings(joystick);



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

  motor[motorArm]=joystick.joy2_y1;
motor[motorArmUp] = joystick.joy2_y2/2;

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
     motor(motorBucket) = 50;
     wait1Msec(100);
     motor(motorBucket) = 0;
      }
   else
   {
     if(joy2Btn(6))          // If Button 6 is pressed:
      {
     motor(motorBucket) = -50;
     wait1Msec(100);
     motor(motorBucket) = 0;
       }
   }


   if(joy1Btn(5))
   {
     motor(motorFlag) = 50;
     wait1Msec(100);
     motor(motorFlag) = 0;
   // Motor E is assigned a power level equal to the left analog stick's Y-axis reading.
   }
   if(joy1Btn(6))
   {
     motor(motorFlag) = -50;
     wait1Msec(100);
     motor(motorFlag) = 0;
   // Motor E is assigned a power level equal to the left analog stick's Y-axis reading.
   }
}   // BUTTONS TO CONTOL SERVO ARM
    // Control arm via shoulder buttons, 5 and 6... 5=up, 6=down
}
