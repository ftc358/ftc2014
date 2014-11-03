#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S2,     IRseeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorR,        tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int state=0b00000000;
int mode = 1;
int dcS1, dcS2, dcS3, dcS4, dcS5 = 0;
string messagelol="going straight...";
#include "C:\Users\dhou\Desktop\rdpartyrobotcdr-3.3.1\drivers\hitechnic-irseeker-v2.h"

void wheel(int l, int r){
	int oldL = motor[motorL];
	int oldR = motor[motorR];
	int deltaL = l-oldL;//it's an "L"
	int deltaR = r-oldR;
	for (int i = 0; i < 10; ++i)
	{
		oldL+=(deltaL/10);
		oldR+=(deltaR/10);
		motor[motorL]=oldL;//it's an "L"
		motor[motorR]=oldR;
		wait(20);
	}
	motor[motorL]=l;//it's an "L"
	motor[motorR]=r;
	return;
}

int getOffRamp(){
	wheel(50,50);
	wait(1500);
	wheel(-20,20);
	wait(500);
	wheel(50,50);
	wait(700);
	return;
}

int homeInOnBeacon(){
	int angle=5;
	while(true){
		HTIRS2readAllDCStrength(IRseeker, dcS1, dcS2, dcS3, dcS4, dcS5);
		angle=Sensorvalue[IRseeker];
		if(angle < 5 & angle > 0){
			messagelol="turning left...";
			wheel(0,20);
		}
		if(angle == 5){
			messagelol="going straight.";
			wheel(10,10);
		}
		if(angle > 5){
			messagelol="turning right.";
			wheel(20,0);
		}
		if(angle == 0){
			messagelol="No signal detected.";
			wheel(-10,10);
		}
		if(dcS3 > 170){
			wheel(0,0);
			return 0;
		}
		nxtDisplayCenteredTextLine(3,"%d, %s",angle,messagelol);
		nxtDisplayCenteredTextLine(4,"%s, %d","Channel 3:",dcS3);
	}
}

task main(){
	wait(1000);
	getOffRamp();
	homeInOnBeacon();
}
