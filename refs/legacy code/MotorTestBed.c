#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     TouchSensor1,   sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(true)
	{
	if(SensorValue (TouchSensor1) == 1)
	{
		motor [motorD] = 100;
	}
	else
	{
		motor(motorD)=0;
}
}

	//wait1Msec (1000);

}
