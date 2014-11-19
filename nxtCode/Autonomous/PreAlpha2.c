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

int a1,a2,b1,b2,b3,b4,b5 = 0;

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
	if(x==1){
		wheel(30,30,a1);
		wheel(-90,90,a2);
	}else if(x==2){
		wheel(30,30,b1);
		wheel(70,-70,b2);
		wheel(30,30,b3);
		wheel(-70,70,b4);
		wheel(75,75,b5);
	}
}

void defaultsPlz(){
	a1=500;
	a2=800;
	b1=500;
	b2=2000;
	b3=600;
	b4=1000;
	b5=1600;
}

void runTests(){

}

task main(){
	defaultsPlz();
	runTests();
	kickStand(determinePos());
}
