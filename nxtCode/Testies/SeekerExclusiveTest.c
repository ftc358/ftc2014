#pragma config(Sensor, S1,     seeker1,        sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S2,     seeker2,        sensorHiTechnicIRSeeker1200)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(true){
		nxtDisplayCenteredTextLine(3, "%d, %d", SensorValue[S1], SensorValue[S2]);
		wait1Msec(1000);
	}
}
