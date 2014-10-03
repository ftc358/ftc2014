#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     Touch1,         sensorHiTechnicTouchMux)
#pragma config(Sensor, S3,     Touch2,         sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     motorArm,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFlag,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBucket,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorArmUp,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorDriveRight1, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorDriveRight2, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorDriveLeft1, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorDriveLeft2, tmotorTetrix, openLoop)
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

void moveArm(int x, int t)
{
ClearTimer(T1);
while(time1[t1]< t)
	{
		motor(motorArm) =x;
  }
  motor(motorArm) =0;
  wait1Msec(100);
}


void moveBucket(int x, int t)
{

	motor[Bucket] = x;
	wait1Msec(t);
	motor[Bucket]= 0;
	wait1Msec(100);
}


task main()
{

  moveArm(50,1000);
  move(50,50,1000);
  moveBucket(50,300);
  move(50,-50,1000);
  move(50,50,1000);
  moveArm(-50,1000);
  move(-50,50,1000);
  move(50,50,1000);

}
