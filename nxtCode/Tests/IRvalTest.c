#pragma config(Sensor, S1,     IRSeeker,       sensorHiTechnicIRSeeker1200)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(true){
nxtDisplayCenteredBigTextLine(3,"%d",SensorValue[IRSeeker]);
}}
