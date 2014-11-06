#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IRseeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorR,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#include "C:\Users\dhou\Desktop\rdpartyrobotcdr-3.3.1\drivers\common.h"
//#include "C:\Users\dhou\Desktop\rdpartyrobotcdr-3.3.1\drivers\hitechnic-irseeker-v2.h"
int mode = 1;
int dcS1, dcS2, dcS3, dcS4, dcS5 = 0;
string messagelol="going straight...";
int recording[1024];
int indexNum = 0;
int sampleRate = 100; //in ms

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
		wait1Msec(20);
	}
	motor[motorL]=l;//it's an "L"
	motor[motorR]=r;
	return;
}

void record(int t){
	int samples = t/sampleRate;
	for(int i=0; i<samples;i++){
		recording[indexNum]=Sensorvalue[IRseeker];
		indexNum++;
		wait1Msec(sampleRate);
	}
}

int getOffRamp(){
	wheel(20,20);
	record(2750);
	wheel(-10,10);
	record(1500);
	wheel(20,20);
	record(1500);
	return 0;
}

void homeInOnBeacon(){
	int angle=5;
	while(true){
		//HTIRS2readAllDCStrength(IRseeker, dcS1, dcS2, dcS3, dcS4, dcS5);
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
		/*if(dcS3 > 170){
			wheel(0,0);
			return 0;
		}*/
		nxtDisplayCenteredTextLine(3,"%d, %s",angle,messagelol);
		//nxtDisplayCenteredTextLine(4,"%s, %d","Channel 3:",dcS3);
	}
}

void reportData(){
	while(true){
		if(nNxtButtonPressed>-1){
			int lineNum = 1;
			int x,y;
			for(int i=0; i<=indexNum; i++){

				if(
			}
		}
	}
}

task main(){
	getOffRamp();
	reportData();
}
