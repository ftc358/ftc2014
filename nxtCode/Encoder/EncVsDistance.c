#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorR,        tmotorTetrix, openLoop)

float tpr = 1024;
float wheelDiam = 12;
float wheelCirc = 0;
int speed = 50;
float pi = 3.1415926;

void init(){
	wheelCirc=wheelDiam*pi;
}

void goDistance(float distance){
	nMotorEncoder[motorR]=0;
	while(nMotorEncoder[motorR]<(distance/wheelDiam*tpr)){
		nxtDisplayCenteredTextLine(3,"%d	,%d",nMotorEncoder[motorR],(nMotorEncoder[motorR]/tpr*wheelDiam));
		motor[motorR]=speed;
	}
	motor[motorR]=0;
}

task main(){
	init();
	goDistance(100);
}
