#pragma config(Sensor, S1,     Compass,        sensorI2CHiTechnicCompass)
#pragma config(Sensor, S2,     Sonar,          sensorSONAR)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(true){
		writeDebugStreamLine("%d, %d",SensorValue[S1],SensorValue[S2]);
		wait1Msec(50);
	}
}
