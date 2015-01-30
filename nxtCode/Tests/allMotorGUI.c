#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S4,     IRSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,          A,             tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          B,             tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     armUp1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     armUp2,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorL,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     armFlip1,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     backArm,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorJ,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     Bucket,        tmotorTetrix, openLoop)

int values[8]; //7=increment,0-6= wheel times
int selection; //0-6 values, 7 run, 8 unrun, 9 increment
char selects[20]; //0-13 values, 14-15 run, 16-17 unrun, 18-19 increment
int lastrun =0;

void wheel(int l, int r, int t){
	int oldL = motor[motorL];
	int oldR = motor[motorR];
	int deltaL = l-oldL;//it's an "L"
	int deltaR = r-oldR;
	for (int i = 0; i < 10; ++i)
	{
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

	motor[A]=values[0];
	motor[B]=values[0];                                                      //nxt motors A&B
	motor[armUp1]=values[1];
	motor[armUp2]=values[1];
	motor[motorL]=values[2];
	motor[motorR]=values[3];
	motor[armFlip1]=values[4];
	motor[backArm]=values[5];
	motor[Bucket]=values[6];
	while(nNxtButtonPressed==3){
	}
	motor[A]=0;
	motor[B]=0;                                                      //nxt motors A&B
	motor[armUp1]=0;
	motor[armUp2]=0;
	motor[motorL]=0;
	motor[motorR]=0;
	motor[armFlip1]=0;
	motor[backArm]=0;
	motor[Bucket]=0;
	return;
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
	values[7]=10;
	values[0]=50;
	values[1]=50;
	values[2]=50;
	values[3]=50;
	values[4]=50;
	values[5]=50;
	values[6]=50;
	setSelects(7,false);
}

void refreshScreen(){
	nxtDisplayCenteredTextLine(1,"%cAB,%d%c   %cArm,%d%c",selects[0],values[0],selects[1],selects[2],values[1],selects[3]);
	nxtDisplayCenteredTextLine(2,"%cL,%d%c   %cR,%d%c",selects[4],values[2],selects[5],selects[6],values[3],selects[7]);
	nxtDisplayCenteredTextLine(3,"%cFlp,%d%c   %cBak,%d%c",selects[8],values[4],selects[9],selects[10],values[5],selects[11]);
	nxtDisplayCenteredTextLine(4,"%cBucket,%d%c",selects[12],values[6],selects[13]);
	nxtDisplayCenteredTextLine(5,"%cRUN!%c",selects[14],selects[15]);
	nxtDisplayCenteredTextLine(6,"%cUNRUN!%c",selects[16],selects[17]);
	nxtDisplayCenteredTextLine(7,"%cIncrement: %d%c",selects[18],values[7],selects[19]);
}

void tweakVal(){
	while(true){
		if(nNxtButtonPressed == 1){
			values[selection]+=values[7];
			if(values[selection]>100) values[selection]=100;
			refreshScreen();
			wait1Msec(300);
		}
		if(nNxtButtonPressed == 2){
			values[selection]-=values[7];
			if(values[selection]<1) values[selection]=1;
			refreshScreen();
			wait1Msec(300);
		}
		if(nNxtButtonPressed == 3) return;
	}
}

void tweakIncrement(){
	while(true){
		if(nNxtButtonPressed == 1){
			values[7]*=10;
			if(values[selection]>100) values[selection]=100;
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
			setSelects(selection,false);
			refreshScreen();
			wait1Msec(400);
		}
		if(nNxtButtonPressed == 3 & selection==9){
			setSelects(selection,true);
			tweakIncrement();
			setSelects(selection,false);
			refreshScreen();
			wait1Msec(400);
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

task main(){
	defaultsPlz();
	runTests();
}
