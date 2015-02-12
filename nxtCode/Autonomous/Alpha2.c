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
#pragma config(Motor,  mtr_S1_C3_1,      ,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     armFlip,       tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    backArm,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#define COMPILED_OFFLINE "Yup" //comment out on the field

//#include "../Drivers/Includes/MainIncludes.h"
#include "../Drivers/hitechnic-superpro.h"
#include "JoystickDriver.c"


int values[8]; //7=increment,0-6= wheel times
int selection; //0-6 values, 7 run, 8 unrun, 9 increment
char selects[20]; //0-13 values, 14-15 run, 16-17 unrun, 18-19 increment
int lastrun =0;
int gOffset,value=0;
float multiplier=2162.0/1573.0;
float wheelCircumference=4.0*2.54*3.1415926;

bool readLims(int x){
	ubyte mask=0b00000001<<x;
	return(HTSPBreadIO(HTSPB, mask)!=0);
}

void progressBar(int l,int x, int y){
	char aa=' ',bb=' ',cc=' ',dd=' ',ee=' ',ff=' ',gg=' ',hh=' ',ii=' ',jj=' ',kk=' ',ll=' ',mm=' ',nn=' ',oo=' ';
	int prog = x*16/y;
	switch(prog){
		case 16:
		case 15:
			oo='=';
		case 14:
			nn='=';
		case 13:
			mm='=';
		case 12:
			ll='=';
		case 11:
			kk='=';
		case 10:
			jj='=';
		case 9:
			ii='=';
		case 8:
			hh='=';
		case 7:
			gg='=';
		case 6:
			ff='=';
		case 5:
			ee='=';
		case 4:
			dd='=';
		case 3:
			cc='=';
		case 2:
			bb='=';
		case 1:
			aa='=';
	}
	nxtDisplayTextLine(l,"|%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c|",aa,bb,cc,dd,ee,ff,gg,hh,ii,jj,kk,ll,mm,nn,oo);
}

void calibrateGyro(int samples){
	nxtDisplayTextLine(2,"-----------------",);
	nxtDisplayTextLine(5,"-----------------",);
	nxtDisplayCenteredTextLine(3,"Calibrating...");
	gOffset=0;
	for(int i=0; i<samples; i++){
		gOffset+=SensorValue[Gyro];
		wait1Msec(4);
		progressBar(4,i,samples);
	}
	gOffset/=samples;
}

void resetGyro(){
	clearTimer(T4);
	calibrateGyro(512);
}

void wheel(int l, int r, int t, bool accelerate=true){
	int oldL = motor[motorL];
	int oldR = motor[motorR];
	int deltaL = l-oldL;//it's an "L"
	int deltaR = r-oldR;
	for (int i = 0; i < 10; ++i)
	{
		if(!accelerate)break;
		oldL+=(deltaL/10);
		oldR+=(deltaR/10);
		motor[motorL]=oldL/1;//it's an "L"
		motor[motorR]=oldR/1;
		wait1Msec(20);
	}
	motor[motorL]=l;//it's an "L"
	motor[motorR]=r;
	wait1Msec(t);
	return;
}

void encoder(float d, int v){//in cms
	int target=(int)(d*1440.0/wheelCircumference)
	nMotorEncoder[motorR] = 0;
	long lastTime2=time1[T4];
	for(int i=0;i<3;i++){
		wheel(v,v,0)
		if(v>0)while(nMotorEncoder[motorR]<target&(time1[T4]-lastTime2)<4000){}
		if(v<0)while(nMotorEncoder[motorR]>target&(time1[T4]-lastTime2)<4000){}
		motor[motorR] = 0;
		motor[motorL] = 0;
		//wheel(0,0,0);
		wait1Msec(150);
		writeDebugStreamLine("%d", nMotorEncoder[motorR]);
		v=v*-4/7;
		lastTime2=time1[T4]
	}
}

/*void mturn(int x,int v){
	int old=SensorValue[Compass];
	int circles=x/360;
	if(x<0){
		wheel(-v,v,0);
		}else if(x>0){
		wheel(v,-v,0);
		}else{
		return;
	}
	old=(old+x)%360;
	if(old<0)old+=360;
	while(SensorValue[Compass]>(old+5)|SensorValue[Compass]<(old-5)|circles!=0){
		nxtDisplayCenteredBigTextLine(0,"%d",SensorValue[Compass]);
		nxtDisplayCenteredBigTextLine(2,"%d",old);
		if(SensorValue[Compass]>(old+5)|SensorValue[Compass]<(old-5)){
			circles--;
			while(SensorValue[Compass]<(old+5)&SensorValue[Compass]>(old-5)){}
		}
	}
	return;
}*/

void gturn(int x,int v){
	float turned=0;
	long lastTime=0;
	if(x<0){
		wheel(-v,v,0,false);
		}else if(x>0){
		wheel(v,-v,0,false);
		}else{
		return;
	}
	clearTimer(T4);
	while(abs(turned)<abs(x)){
		value = SensorValue[Gyro];
		if(abs(value)<2)value=-gOffset;
		turned+=(float)(value-gOffset)*720.0*(float)(time1(T4)-lastTime)*multiplier/1023000.0;
		lastTime=time1(T4);
		nxtDisplayCenteredBigTextLine(0,"%d",value);
		nxtDisplayCenteredBigTextLine(2,"%d",(value-gOffset));
		nxtDisplayCenteredBigTextLine(4,"%d",turned);
		wait1Msec(5);
	}
	wheel(0,0,0,false);
	return;
}

void gturn2(int x,int v){
	float turned=0;
	long lastTime=0;
	clearTimer(T4);
	long lastTime2=time1[T4];
	if(x<0){
		wheel(-v,v,0,false);
		}else if(x>0){
		wheel(v,-v,0,false);
		}else{
		return;
	}
	int p=1;
	for(int i=0;i<3;i++){
		while(((p*abs(turned))<(p*abs(x)))&((time1[T4]-lastTime2)<4000)) {
			value = SensorValue[Gyro];
			if(abs(value)<2)value=-gOffset;
			turned+=(float)(value-gOffset)*720.0*(float)(time1(T4)-lastTime)*multiplier/1023000.0;
			lastTime=time1(T4);
			nxtDisplayCenteredBigTextLine(0,"%d",value);
			nxtDisplayCenteredBigTextLine(2,"%d",(value-gOffset));
			nxtDisplayCenteredBigTextLine(4,"%d",turned);
			wait1Msec(5);
		}
		wheel(0,0,0,false);
		wait1Msec(200);
		p*=-1;
		v=v*-4/7;
		lastTime2=time1[T4];
	}
	return;
}

int determinePos(){
	wait1Msec(1000);
	while(true){
		if(SensorValue[IRSeeker]==0|SensorValue[IRSeeker]==7){
			return 1;
			}else if(SensorValue[IRSeeker]==5){
			return 2;
		}
	}
}

void kickStand(int x){
	if(x==1){
		wheel(30,30,values[0]);
		gturn(1440,100);
		//wheel(-90,90,values[1]);
		}else if(x==2){
		wheel(30,30,values[2]);
		gturn(90,70);
		//wheel(70,-70,values[3]);
		wheel(30,30,values[4]);
		gturn(-90,70);
		//wheel(-70,70,values[5]);
		wheel(50,50,values[6]);
	}
}

void unKickStand(){
	wait1Msec(1000);
	wheel(-75,-75,values[6]);
	wheel(70,-70,values[5]);
	wheel(-30,-30,values[4]);
	wheel(-70,70,values[3]);
	wheel(-30,-30,values[2]);
}

void setSelects(int x,bool y){
	x*=2; //selections are zero indexed!!!
	for(int i=0;i<18;i++){
		selects[i]=' ';
		if(y){
			if(i==x)selects[i]='>';
			if(i==x+1)selects[i]='<';
			}else{
			if(i==x)selects[i]='[';
			if(i==x+1)selects[i]=']';
		}
	}
	wait1Msec(300);
}

void defaultsPlz(){
	values[7]=100;
	values[0]=500;
	values[1]=800;
	values[2]=500;
	values[3]=2000;
	values[4]=600;
	values[5]=1000;
	values[6]=1600;
	setSelects(7,false);
}

void refreshScreen(){
	nxtDisplayCenteredTextLine(1,"%c3,%d%c   %c-+9,%d%c",selects[0],values[0],selects[1],selects[2],values[1],selects[3]);
	nxtDisplayCenteredTextLine(2,"%c3,%d%c   %c+-7,%d%c",selects[4],values[2],selects[5],selects[6],values[3],selects[7]);
	nxtDisplayCenteredTextLine(3,"%c3,%d%c   %c+-7,%d%c",selects[8],values[4],selects[9],selects[10],values[5],selects[11]);
	nxtDisplayCenteredTextLine(4,"%c7,%d%c",selects[12],values[6],selects[13]);
	nxtDisplayCenteredTextLine(5,"%cRUN!%c",selects[14],selects[15]);
	nxtDisplayCenteredTextLine(6,"%cUNRUN!%c",selects[16],selects[17]);
	nxtDisplayCenteredTextLine(7,"%cIncrement: %d%c",selects[18],values[7],selects[19]);
}

void tweakVal(){
	while(true){
		if(nNxtButtonPressed == 1) values[selection]+=values[7];
		if(nNxtButtonPressed == 2) values[selection]-=values[7];
		if(values[selection]>1000000) values[selection]=1000000;
		if(values[selection]<1) values[selection]=1;
		refreshScreen();
		wait1Msec(300);
		if(nNxtButtonPressed == 3) return;
	}
}

void tweakIncrement(){
	while(true){
		if(nNxtButtonPressed == 1){
			values[7]*=10;
			if(values[selection]>100000) values[selection]=100000;
			refreshScreen();
			wait1Msec(300);
		}
		if(nNxtButtonPressed == 2){
			values[7]/=10;
			if(values[selection]<1) values[selection]=1;
			refreshScreen();
			wait1Msec(300);
		}
		if(nNxtButtonPressed == 3) return;
	}
}

void runTests(){
	refreshScreen();
	while(true){
		nxtDisplayCenteredTextLine(0,"IR Value = %d",SensorValue[IRSeeker]);
		if(nNxtButtonPressed == 3 & selection==7){
			lastrun=determinePos();
			kickStand(lastrun);
		}
		if(nNxtButtonPressed == 3 & selection==8){
			unKickStand();
		}
		if(nNxtButtonPressed == 3 & selection<7 & selection>=0){
			setSelects(selection,true);
			tweakVal();
		}
		if(nNxtButtonPressed == 3 & selection==9){
			tweakIncrement();
		}
		if(nNxtButtonPressed == 1){
			selection++;
			if(selection>9)selection=0;
			setSelects(selection,false);
			refreshScreen();
			wait1Msec(300);
		}
		if(nNxtButtonPressed == 2){
			selection--;
			if(selection<0)selection=9;
			setSelects(selection,false);
			refreshScreen();
			wait1Msec(300);
		}
	}
}

void startfromramp(){
	wheel(50,50,5000);
	motor[armFlip]=50;
	wait1Msec(2000);
	motor[backArm]=50;
	wait1Msec(2000);
	wheel(-50,-60,1000);
	wheel(-80,-80,3000);
}

void reach(int x){ //input actual height: 30, 60, 90, 120
	switch(x){
		case 120:
			motor[armUp1]=100; //hard coding ftw
			motor[armUp2]=100;
			wait1Msec(2000);
			motor[armUp1]=0;
			motor[armUp2]=0;
			motor[armFlip]=20;
			while(!readLims(0)){}
			motor[armFlip]=0;
			wait1Msec(3000);
			motor[armFlip]=-20;
			wait1Msec(1000);
			motor[armFlip]=0;
			break;
		case 90:
		case 60:
		case 30:
		default:
			break;
	}
	return;
}

void score(int x){
	if(x==1){
		encoder(58,100);
		gturn(90,80);
		encoder(80,100);
		gturn(-90,80);
		encoder(86,100);
		gturn(-90,80);
		encoder(18,50);
		reach(120);
		encoder(-18,-50);
		gturn(90,80);
		encoder(80,100);
		gturn(-135,80);
		encoder(-60,-100);
		servo[backArm]=127;
		wait1Msec(1500);
		encoder(60,100);
		gturn(-45,80);
		encoder(126,100);
		gturn(90,80);
		encoder(85,100);
		gturn(-90,80);
		encoder(97,100);
		gturn(90,80);
	}else if(x==2){
		encoder(72,100);
		reach(120);
		encoder(-41,-100);
		gturn(90,80);
		encoder(51,100);
		gturn(-90,80);
		encoder(170,100);
		gturn(-135,80);
		encoder(-83,-50);
		servo[backArm]=127;
		wait1Msec(1500);
		encoder(83,100);
		gturn(-45,80);
		encoder(199,100);
		gturn(90,80);
		encoder(58,100);
	}
}

void initializeRobot()//9096679161,444
{
	calibrateGyro(256);
	for(int i=0;i<10;i++){
		nxtDisplayCenteredBigTextLine(0,"%d",value);
		nxtDisplayCenteredBigTextLine(2,"%d",(value-gOffset));
		wait1Msec(100);
	}
	servo[backArm]=-95;
	return;
}

task main(){
	initializeRobot();
	waitForStart();
	score(determinePos());
}
