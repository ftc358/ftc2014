/*------------------------------------------*\
|*	Natural Language for EV3 Virtual Worlds *|
\*------------------------------------------*/

#pragma once
#pragma systemFile            	// eliminates warning for "unreferenced" functions

#include "JoystickDriver.c"

/*
--------------- Enumerations and Defines ----------------------
*/

#define noMotorOnPort ((tMotor) -1)
#define nMaxJoyScaleValue 100

typedef enum tEV3LCDLine
{
	line1				= 0,
	line2				= 1,
	line3				= 2,
	line4				= 3,
	line5				= 4,
	line6				= 5,
	line7				= 6,
	line8				= 7
} tEV3LCDLine;

// enum for units
typedef enum tMovementUnits
{
	degrees							= 0,
	rotations						= 1,
	milliseconds				= 2,
	seconds							= 3,
	minutes							= 4
} tMovementUnits;

bool bPopulatedMotorDriveSides = false;
TMotorList leftMotors;
TMotorList rightMotors;
short nGlobalJoyScaledValue = nMaxJoyScaleValue;

/*
------------------- Utility Commands --------------------------
*/

void setJoystickScale(short nScaledPercentage = nMaxJoyScaleValue)
{
	if(nScaledPercentage > nMaxJoyScaleValue)
	{
		nGlobalJoyScaledValue = nMaxJoyScaleValue;
	}
	else if(nScaledPercentage < 0)
	{
		nGlobalJoyScaledValue = 0;
	}
	else
	{
		nGlobalJoyScaledValue = nScaledPercentage;
	}
}

void updateMotorDriveTrain()
{
	if(!bPopulatedMotorDriveSides)
	{
		getMotorsWithDriveSideType(driveRight, rightMotors);
		getMotorsWithDriveSideType(driveLeft,	 leftMotors);
		bPopulatedMotorDriveSides = true;
	}
}


void displayMotorValues(tEV3LCDLine lineNumber = line1, const tMotor nDeviceIndex = motorA)
{
	string sOutputString;
	sprintf(sOutputString, "Motor(%d) %d deg", nDeviceIndex + 1 , getMotorEncoder((tMotor)nDeviceIndex));
	int nLineNumber = lineNumber;
	displayTextLine(nLineNumber, sOutputString);
}

void displaySensorValues(tEV3LCDLine lineNumber = line1, const tSensors nDeviceIndex = S1)
{
	string sOutputString;

	switch(SensorType[nDeviceIndex])
	{
		case sensorTouch:							sprintf(sOutputString, "Touch(%d) %s", nDeviceIndex + 1, 			SensorValue(nDeviceIndex) ? "Pressed" : "Released"); 	break;

		case sensorLightActive:
		case sensorLightInactive:			sprintf(sOutputString, "Light(%d) %d%%", nDeviceIndex + 1, 		SensorValue(nDeviceIndex)); 	break;

		case sensorSoundDB:
		case sensorSoundDBA:					sprintf(sOutputString, "Sound(%d) %d%%", nDeviceIndex + 1, 		SensorValue(nDeviceIndex)); 	break;

		case sensorColorNxtFULL:
		case sensorColorNxtRED:
		case sensorColorNxtGREEN:
		case sensorColorNxtBLUE:			sprintf(sOutputString, "Color(%d) %d", nDeviceIndex + 1, 			SensorValue(nDeviceIndex)); 	break;

		case sensorSONAR:							sprintf(sOutputString, "Sonar(%d) %d cm", nDeviceIndex + 1, 	SensorValue(nDeviceIndex)); 	break;

		case sensorI2CLegoTempC:			sprintf(sOutputString, "Temp(%d) %dC", nDeviceIndex + 1, 			SensorValue(nDeviceIndex)); 	break;
		case sensorI2CLegoTempF:			sprintf(sOutputString, "Temp(%d) %dF", nDeviceIndex + 1, 			SensorValue(nDeviceIndex)); 	break;

		case sensorEV3_Touch:					sprintf(sOutputString, "Touch(%d) %s", nDeviceIndex + 1, 			getTouchValue(nDeviceIndex) ? "Pressed" : "Released"); 	break;
		case sensorEV3_Color:					sprintf(sOutputString, "Color(%d) %d", nDeviceIndex + 1, 			getColorHue(nDeviceIndex)); 	break;
		case sensorEV3_Ultrasonic:		sprintf(sOutputString, "US(%d) %d cm", nDeviceIndex + 1, 			getUSDistance(nDeviceIndex)); 	break;
		case sensorEV3_Gyro:					sprintf(sOutputString, "Gyro(%d) %d deg", nDeviceIndex + 1, 	getGyroDegrees(nDeviceIndex)); 	break;
		case sensorEV3_IRSensor:			sprintf(sOutputString, "IR(%d) %d", nDeviceIndex + 1, 				getIRDistance(nDeviceIndex)); 	break;
	}

	int nLineNumber = lineNumber;
	displayTextLine(nLineNumber, sOutputString);
}


/*
------------------- Low Level Commands ------------------------
*/

void lowLevelMoveDistance(const float quantity, short nLeftSpeed, short nRightSpeed, const tMovementUnits nUnitType)
{
	long nConvertedUnitsLeft = 0;
	long nConvertedUnitsRight = 0;

	if(nUnitType == degrees)
	{
		nConvertedUnitsLeft = quantity;
		nConvertedUnitsRight = quantity;
	}
	else if(nUnitType == rotations)
	{
		nConvertedUnitsLeft = quantity * 360.0;
		nConvertedUnitsRight = quantity * 360.0;
	}
	else
	{
		return;
	}

	updateMotorDriveTrain();

	if(nLeftSpeed < 0)
		nConvertedUnitsLeft *= -1;

	if(nRightSpeed < 0)
		nConvertedUnitsRight *= -1;

	if(leftMotors[0] != noMotorOnPort)	moveMotorTarget(leftMotors[0], nConvertedUnitsLeft, nLeftSpeed);
	if(leftMotors[1] != noMotorOnPort)	moveMotorTarget(leftMotors[1], nConvertedUnitsLeft, nLeftSpeed);
	if(leftMotors[2] != noMotorOnPort)	moveMotorTarget(leftMotors[2], nConvertedUnitsLeft, nLeftSpeed);
	if(leftMotors[3] != noMotorOnPort)	moveMotorTarget(leftMotors[3], nConvertedUnitsLeft, nLeftSpeed);

	if(rightMotors[0] != noMotorOnPort)	moveMotorTarget(rightMotors[0], nConvertedUnitsRight, nRightSpeed);
	if(rightMotors[1] != noMotorOnPort)	moveMotorTarget(rightMotors[1], nConvertedUnitsRight, nRightSpeed);
	if(rightMotors[2] != noMotorOnPort)	moveMotorTarget(rightMotors[2], nConvertedUnitsRight, nRightSpeed);
	if(rightMotors[3] != noMotorOnPort)	moveMotorTarget(rightMotors[3], nConvertedUnitsRight, nRightSpeed);

	sleep(100);

	while(getMotorDriveTrainMoving())
		sleep(5);

	sleep(25);
}

void lowLevelMoveTiming(float quantity, const short nLeftSpeed, const short nRightSpeed, const tMovementUnits nUnitType)
{
	updateMotorDriveTrain();

	if(leftMotors[0] != noMotorOnPort)	setMotorSpeed(leftMotors[0], nLeftSpeed);
	if(leftMotors[1] != noMotorOnPort)	setMotorSpeed(leftMotors[1], nLeftSpeed);
	if(leftMotors[2] != noMotorOnPort)	setMotorSpeed(leftMotors[2], nLeftSpeed);
	if(leftMotors[3] != noMotorOnPort)	setMotorSpeed(leftMotors[3], nLeftSpeed);

	if(rightMotors[0] != noMotorOnPort)	setMotorSpeed(rightMotors[0], nRightSpeed);
	if(rightMotors[1] != noMotorOnPort)	setMotorSpeed(rightMotors[1], nRightSpeed);
	if(rightMotors[2] != noMotorOnPort)	setMotorSpeed(rightMotors[2], nRightSpeed);
	if(rightMotors[3] != noMotorOnPort)	setMotorSpeed(rightMotors[3], nRightSpeed);

	if(nUnitType == milliseconds)
		sleep(quantity);
	else if(nUnitType == seconds)
		sleep(quantity * 1000);
	else if(nUnitType == minutes)
		sleep(quantity * 1000 * 60);
	else
		sleep(5);

	if(leftMotors[0] != noMotorOnPort)	setMotorSpeed(leftMotors[0], 0);
	if(leftMotors[1] != noMotorOnPort)	setMotorSpeed(leftMotors[1], 0);
	if(leftMotors[2] != noMotorOnPort)	setMotorSpeed(leftMotors[2], 0);
	if(leftMotors[3] != noMotorOnPort)	setMotorSpeed(leftMotors[3], 0);

	if(rightMotors[0] != noMotorOnPort)	setMotorSpeed(rightMotors[0], 0);
	if(rightMotors[1] != noMotorOnPort)	setMotorSpeed(rightMotors[1], 0);
	if(rightMotors[2] != noMotorOnPort)	setMotorSpeed(rightMotors[2], 0);
	if(rightMotors[3] != noMotorOnPort)	setMotorSpeed(rightMotors[3], 0);

	sleep(25);
}

/*
------------------- Wait Commands -------------------------
*/
void wait(const float quantity = 1.0, const tMovementUnits unitType = seconds)
{
	if(unitType == seconds)
		sleep(quantity * 1000.0);
	else if(unitType == minutes)
		sleep(quantity * 1000.0 * 60.0);
	else if(unitType == milliseconds)
		sleep(quantity);
}

#define waitUntil(condition) while(!(condition)) sleep(5)

/*
------------------- Discrete Movement -------------------------
*/

void forward(const float quantity = 1.0, const tMovementUnits unitType = rotations, const short speed = 50)
{
	short adjustedSpeed = abs(speed);
	float adjustedQuantity = abs(quantity);

	switch(unitType)
	{
	case rotations:
	case degrees:
		lowLevelMoveDistance(adjustedQuantity, adjustedSpeed, adjustedSpeed, unitType);
		break;

	case milliseconds:
	case seconds:
	case minutes:
		lowLevelMoveTiming(adjustedQuantity, adjustedSpeed, adjustedSpeed, unitType);
		break;
	}
}

void backward(const float quantity = 1.0, const tMovementUnits unitType = rotations, const short speed = 50)
{
	short adjustedSpeed = abs(speed) * -1;
	float adjustedQuantity = abs(quantity);

	switch(unitType)
	{
	case rotations:
	case degrees:
		lowLevelMoveDistance(adjustedQuantity, adjustedSpeed, adjustedSpeed, unitType);
		break;

	case milliseconds:
	case seconds:
	case minutes:
		lowLevelMoveTiming(adjustedQuantity, adjustedSpeed, adjustedSpeed, unitType);
		break;
	}
}

void turnLeft(const float quantity = 1.0, const tMovementUnits unitType = rotations, const short speed = 50)
{
	short adjustedSpeed = abs(speed);
	float adjustedQuantity = abs(quantity);

	switch(unitType)
	{
	case rotations:
	case degrees:
		lowLevelMoveDistance(adjustedQuantity, -adjustedSpeed, adjustedSpeed, unitType);
		break;

	case milliseconds:
	case seconds:
	case minutes:
		lowLevelMoveTiming(adjustedQuantity, -adjustedSpeed, adjustedSpeed, unitType);
		break;
	}
}

void turnRight(const float quantity = 1.0, const tMovementUnits unitType = rotations, const short speed = 50)
{
	short adjustedSpeed = abs(speed);
	float adjustedQuantity = abs(quantity);

	switch(unitType)
	{
	case rotations:
	case degrees:
		lowLevelMoveDistance(adjustedQuantity, adjustedSpeed, -adjustedSpeed, unitType);
		break;

	case milliseconds:
	case seconds:
	case minutes:
		lowLevelMoveTiming(adjustedQuantity, adjustedSpeed, -adjustedSpeed, unitType);
		break;
	}
}

void moveMotor(const tMotor motorPort = motorA, const float quantity = 1.0, const tMovementUnits unitType = rotations, const short speed = 50)
{
	short adjustedSpeed = abs(speed);
	float adjustedQuantity = abs(quantity);

	switch(unitType)
	{
	//Rotations - moves in reverse if speed and/or quantity are set negative
	case rotations:
		if(speed < 0 || quantity < 0)
			moveMotorTarget(motorPort, -(adjustedQuantity * 360.0), -adjustedSpeed);
		else
			moveMotorTarget(motorPort, (adjustedQuantity * 360.0), adjustedSpeed);
		waitUntilMotorStop(motorPort);
		break;

	//Degrees - moves in reverse if speed and/or quantity are set negative
	case degrees:
		if(speed < 0 || quantity < 0)
			moveMotorTarget(motorPort, -adjustedQuantity, -adjustedSpeed);
		else
			moveMotorTarget(motorPort, adjustedQuantity, adjustedSpeed);
		waitUntilMotorStop(motorPort);
		break;

	//Milliseconds
	case milliseconds:
		setMotorSpeed(motorPort, speed);
		sleep(adjustedQuantity);
		setMotorSpeed(motorPort, 0);
		break;

	//Seconds
	case seconds:
		setMotorSpeed(motorPort, speed);
		sleep(adjustedQuantity * 1000.0);
		setMotorSpeed(motorPort, 0);
		break;

	//Minutes
	case minutes:
		setMotorSpeed(motorPort, speed);
		sleep(adjustedQuantity * 1000.0 * 60.0);
		setMotorSpeed(motorPort, 0);
		break;
	}

	sleep(25);
}

/*
------------------- Constant Movements -------------------------
*/

void setMotor(const tMotor motorPort = motorA, const short speed = 50)
{
	setMotorSpeed(motorPort, speed);
}

void stopMotor(const tMotor motorPort = motorA)
{
	setMotorSpeed(motorPort, 0);
}

void stopAllMotors()
{
	for(short i = 0; i < kNumbOfRealMotors; i++)
	{
		setMotorSpeed((tMotor) i, 0);
	}
}

void setMultipleMotors(const short speed = 50, const tMotor firstMotor = motorA, const tMotor secondMotor = noMotorOnPort,const tMotor thirdMotor = noMotorOnPort,const tMotor fourthMotor = noMotorOnPort)
{
	if(firstMotor != noMotorOnPort) 		setMotorSpeed(firstMotor, speed);
	if(secondMotor != noMotorOnPort) 		setMotorSpeed(secondMotor, speed);
	if(thirdMotor != noMotorOnPort) 		setMotorSpeed(thirdMotor, speed);
	if(fourthMotor != noMotorOnPort) 		setMotorSpeed(fourthMotor, speed);
}

void stopMultipleMotors(const tMotor firstMotor = motorA, const tMotor secondMotor = noMotorOnPort,const tMotor thirdMotor = noMotorOnPort,const tMotor fourthMotor = noMotorOnPort)
{
	if(firstMotor != noMotorOnPort) 		setMotorSpeed(firstMotor, 0);
	if(secondMotor != noMotorOnPort) 		setMotorSpeed(secondMotor, 0);
	if(thirdMotor != noMotorOnPort) 		setMotorSpeed(thirdMotor, 0);
	if(fourthMotor != noMotorOnPort) 		setMotorSpeed(fourthMotor, 0);
}

/*
------------------- Line Tracking Movements -------------------------
*/

void lineTrackLeft(const tSensors sensorName = S1, const short threshold = 50, const short speedPrimary = 50, const short speedSecondary = 0)
{
	updateMotorDriveTrain();

	if(SensorValue[sensorName] > threshold)
	{
		if(leftMotors[0] != noMotorOnPort)	setMotorSpeed(leftMotors[0], speedPrimary);
		if(leftMotors[1] != noMotorOnPort)	setMotorSpeed(leftMotors[1], speedPrimary);
		if(leftMotors[2] != noMotorOnPort)	setMotorSpeed(leftMotors[2], speedPrimary);
		if(leftMotors[3] != noMotorOnPort)	setMotorSpeed(leftMotors[3], speedPrimary);

		if(rightMotors[0] != noMotorOnPort)	setMotorSpeed(rightMotors[0], speedSecondary);
		if(rightMotors[1] != noMotorOnPort)	setMotorSpeed(rightMotors[1], speedSecondary);
		if(rightMotors[2] != noMotorOnPort)	setMotorSpeed(rightMotors[2], speedSecondary);
		if(rightMotors[3] != noMotorOnPort)	setMotorSpeed(rightMotors[3], speedSecondary);
	}
	else
	{
		if(leftMotors[0] != noMotorOnPort)	setMotorSpeed(leftMotors[0], speedSecondary);
		if(leftMotors[1] != noMotorOnPort)	setMotorSpeed(leftMotors[1], speedSecondary);
		if(leftMotors[2] != noMotorOnPort)	setMotorSpeed(leftMotors[2], speedSecondary);
		if(leftMotors[3] != noMotorOnPort)	setMotorSpeed(leftMotors[3], speedSecondary);

		if(rightMotors[0] != noMotorOnPort)	setMotorSpeed(rightMotors[0], speedPrimary);
		if(rightMotors[1] != noMotorOnPort)	setMotorSpeed(rightMotors[1], speedPrimary);
		if(rightMotors[2] != noMotorOnPort)	setMotorSpeed(rightMotors[2], speedPrimary);
		if(rightMotors[3] != noMotorOnPort)	setMotorSpeed(rightMotors[3], speedPrimary);
	}
}

void lineTrackRight(const tSensors sensorName = S1, const short threshold = 50, const short speedPrimary = 50, const short speedSecondary = 0)
{
	updateMotorDriveTrain();

	if(SensorValue[sensorName] < threshold)
	{
		if(leftMotors[0] != noMotorOnPort)	setMotorSpeed(leftMotors[0], speedPrimary);
		if(leftMotors[1] != noMotorOnPort)	setMotorSpeed(leftMotors[1], speedPrimary);
		if(leftMotors[2] != noMotorOnPort)	setMotorSpeed(leftMotors[2], speedPrimary);
		if(leftMotors[3] != noMotorOnPort)	setMotorSpeed(leftMotors[3], speedPrimary);

		if(rightMotors[0] != noMotorOnPort)	setMotorSpeed(rightMotors[0], speedSecondary);
		if(rightMotors[1] != noMotorOnPort)	setMotorSpeed(rightMotors[1], speedSecondary);
		if(rightMotors[2] != noMotorOnPort)	setMotorSpeed(rightMotors[2], speedSecondary);
		if(rightMotors[3] != noMotorOnPort)	setMotorSpeed(rightMotors[3], speedSecondary);
	}
	else
	{
		if(leftMotors[0] != noMotorOnPort)	setMotorSpeed(leftMotors[0], speedSecondary);
		if(leftMotors[1] != noMotorOnPort)	setMotorSpeed(leftMotors[1], speedSecondary);
		if(leftMotors[2] != noMotorOnPort)	setMotorSpeed(leftMotors[2], speedSecondary);
		if(leftMotors[3] != noMotorOnPort)	setMotorSpeed(leftMotors[3], speedSecondary);

		if(rightMotors[0] != noMotorOnPort)	setMotorSpeed(rightMotors[0], speedPrimary);
		if(rightMotors[1] != noMotorOnPort)	setMotorSpeed(rightMotors[1], speedPrimary);
		if(rightMotors[2] != noMotorOnPort)	setMotorSpeed(rightMotors[2], speedPrimary);
		if(rightMotors[3] != noMotorOnPort)	setMotorSpeed(rightMotors[3], speedPrimary);
	}
}

/*
------------------- Timer Commands -------------------------
*/

void resetTimer(TTimers currentTimer = T1)
{
	clearTimer(currentTimer);
}

float getTimer(TTimers currentTimer = T1, const tMovementUnits unitType = seconds)
{
	if(unitType == milliseconds)
		return (time1[currentTimer]);
	else if(unitType == seconds)
		return ((float)time1[currentTimer] / 1000.0);
	else if(unitType == minutes)
		return (((float)time1[currentTimer] / 1000.0) / 60.0);

	return 0.0;
}

/*
------------------- Remote Control Movements -------------------------
*/

void tankControl(TJoystickAxis rightJoystick = JoyY2, TJoystickAxis leftJoystick = JoyY1, short threshold = 10)
{
	short nVirtualRightJoystick = 0;
	short nVirtualLeftJoystick = 0;
	getJoystickSettings(joystick);
	updateMotorDriveTrain();

	switch(rightJoystick)
	{
		case JoyX1:    nVirtualRightJoystick = (joystick.joy1_x1 * 100) / 127;     break;
		case JoyY1:    nVirtualRightJoystick = (joystick.joy1_y1 * 100) / 127;     break;
    case JoyX2:    nVirtualRightJoystick = (joystick.joy1_x2 * 100) / 127;     break;
    case JoyY2:    nVirtualRightJoystick = (joystick.joy1_y2 * 100) / 127;     break;
		default:       nVirtualRightJoystick = 0;
	}

	switch(leftJoystick)
	{
		case JoyX1:    nVirtualLeftJoystick = (joystick.joy1_x1 * 100) / 127;      break;
		case JoyY1:    nVirtualLeftJoystick = (joystick.joy1_y1 * 100) / 127;      break;
    case JoyX2:    nVirtualLeftJoystick = (joystick.joy1_x2 * 100) / 127;      break;
    case JoyY2:    nVirtualLeftJoystick = (joystick.joy1_y2 * 100) / 127;      break;
		default:	     nVirtualLeftJoystick = 0;
	}

	if(nGlobalJoyScaledValue != nMaxJoyScaleValue)
	{
		nVirtualRightJoystick = nVirtualRightJoystick * (nGlobalJoyScaledValue / 100.0);
		nVirtualLeftJoystick  = nVirtualLeftJoystick * (nGlobalJoyScaledValue / 100.0);
	}

	if(abs(nVirtualRightJoystick) <= abs(threshold))
	{
		if(rightMotors[0] != noMotorOnPort)	setMotorSpeed(rightMotors[0], 0);
		if(rightMotors[1] != noMotorOnPort)	setMotorSpeed(rightMotors[1], 0);
		if(rightMotors[2] != noMotorOnPort)	setMotorSpeed(rightMotors[2], 0);
		if(rightMotors[3] != noMotorOnPort)	setMotorSpeed(rightMotors[3], 0);
	}
	else
	{
		if(rightMotors[0] != noMotorOnPort)	setMotorSpeed(rightMotors[0], nVirtualRightJoystick);
		if(rightMotors[1] != noMotorOnPort)	setMotorSpeed(rightMotors[1], nVirtualRightJoystick);
		if(rightMotors[2] != noMotorOnPort)	setMotorSpeed(rightMotors[2], nVirtualRightJoystick);
		if(rightMotors[3] != noMotorOnPort)	setMotorSpeed(rightMotors[3], nVirtualRightJoystick);
	}

	if(abs(nVirtualLeftJoystick) <= abs(threshold))
	{
		if(leftMotors[0] != noMotorOnPort)	setMotorSpeed(leftMotors[0], 0);
		if(leftMotors[1] != noMotorOnPort)	setMotorSpeed(leftMotors[1], 0);
		if(leftMotors[2] != noMotorOnPort)	setMotorSpeed(leftMotors[2], 0);
		if(leftMotors[3] != noMotorOnPort)	setMotorSpeed(leftMotors[3], 0);
	}
	else
	{
		if(leftMotors[0] != noMotorOnPort)	setMotorSpeed(leftMotors[0], nVirtualLeftJoystick);
		if(leftMotors[1] != noMotorOnPort)	setMotorSpeed(leftMotors[1], nVirtualLeftJoystick);
		if(leftMotors[2] != noMotorOnPort)	setMotorSpeed(leftMotors[2], nVirtualLeftJoystick);
		if(leftMotors[3] != noMotorOnPort)	setMotorSpeed(leftMotors[3], nVirtualLeftJoystick);
	}
}

void arcadeControl(TJoystickAxis verticalJoystick = JoyY2, TJoystickAxis horizontalJoystick = JoyX2, short threshold = 10)
{
	short nVirtualVerticalJoystick = 0;
	short nVirtualHorizontalJoystick = 0;
	short nRightSideSpeed = 0;
	short nLeftSideSpeed = 0;

	updateMotorDriveTrain();
	getJoystickSettings(joystick);

	switch(verticalJoystick)
	{
		case JoyX1:    nVirtualVerticalJoystick = (joystick.joy1_x1 * 100) / 127;     break;
		case JoyY1:    nVirtualVerticalJoystick = (joystick.joy1_y1 * 100) / 127;	    break;
    case JoyX2:    nVirtualVerticalJoystick = (joystick.joy1_x2 * 100) / 127;     break;
    case JoyY2:    nVirtualVerticalJoystick = (joystick.joy1_y2 * 100) / 127;     break;
		default:       nVirtualVerticalJoystick = 0;
	}

	switch(horizontalJoystick)
	{
		case JoyX1:    nVirtualHorizontalJoystick = (joystick.joy1_x1 * 100) / 127;   break;
		case JoyY1:    nVirtualHorizontalJoystick = (joystick.joy1_y1 * 100) / 127;   break;
    case JoyX2:    nVirtualHorizontalJoystick = (joystick.joy1_x2 * 100) / 127;   break;
    case JoyY2:    nVirtualHorizontalJoystick = (joystick.joy1_y2 * 100) / 127;   break;
		default:       nVirtualHorizontalJoystick = 0;
	}

	for(short i = 0; i < kNumbOfRealMotors; i++)
	{
		if(abs(nVirtualVerticalJoystick) <= abs(threshold) && abs(nVirtualHorizontalJoystick) <= abs(threshold))
		{
			if(rightMotors[0] != noMotorOnPort)	setMotorSpeed(rightMotors[0], 0);
			if(rightMotors[1] != noMotorOnPort)	setMotorSpeed(rightMotors[1], 0);
			if(rightMotors[2] != noMotorOnPort)	setMotorSpeed(rightMotors[2], 0);
			if(rightMotors[3] != noMotorOnPort)	setMotorSpeed(rightMotors[3], 0);

			if(leftMotors[0] != noMotorOnPort)	setMotorSpeed(leftMotors[0], 0);
			if(leftMotors[1] != noMotorOnPort)	setMotorSpeed(leftMotors[1], 0);
			if(leftMotors[2] != noMotorOnPort)	setMotorSpeed(leftMotors[2], 0);
			if(leftMotors[3] != noMotorOnPort)	setMotorSpeed(leftMotors[3], 0);
		}
		else
		{
		 	nRightSideSpeed = ((nVirtualVerticalJoystick - nVirtualHorizontalJoystick)/2);
 			nLeftSideSpeed = ((nVirtualVerticalJoystick + nVirtualHorizontalJoystick)/2);

 			if(nGlobalJoyScaledValue != nMaxJoyScaleValue)
			{
				nRightSideSpeed = nRightSideSpeed * (nGlobalJoyScaledValue / 100.0);
				nLeftSideSpeed 	= nLeftSideSpeed * (nGlobalJoyScaledValue / 100.0);
			}

			if(rightMotors[0] != noMotorOnPort)	setMotorSpeed(rightMotors[0], nRightSideSpeed);
			if(rightMotors[1] != noMotorOnPort)	setMotorSpeed(rightMotors[1], nRightSideSpeed);
			if(rightMotors[2] != noMotorOnPort)	setMotorSpeed(rightMotors[2], nRightSideSpeed);
			if(rightMotors[3] != noMotorOnPort)	setMotorSpeed(rightMotors[3], nRightSideSpeed);

			if(leftMotors[0] != noMotorOnPort)	setMotorSpeed(leftMotors[0], nLeftSideSpeed);
			if(leftMotors[1] != noMotorOnPort)	setMotorSpeed(leftMotors[1], nLeftSideSpeed);
			if(leftMotors[2] != noMotorOnPort)	setMotorSpeed(leftMotors[2], nLeftSideSpeed);
			if(leftMotors[3] != noMotorOnPort)	setMotorSpeed(leftMotors[3], nLeftSideSpeed);
		}
	}
}

void armControl(tMotor armMotorPort = motorA, TJoystickButtons upButton = Btn5, TJoystickButtons downButton = Btn7, short armSpeed = 75)
{
	short nVirtualUpButton = 0;
	short nVirtualDownButton = 0;
	getJoystickSettings(joystick);

	switch(upButton)
	{
		case Btn1:     nVirtualUpButton = joy1Btn(1);     break;
		case Btn2:     nVirtualUpButton = joy1Btn(2);     break;
		case Btn3:     nVirtualUpButton = joy1Btn(3);     break;
		case Btn4:     nVirtualUpButton = joy1Btn(4);     break;
		case Btn5:     nVirtualUpButton = joy1Btn(5);     break;
		case Btn6:     nVirtualUpButton = joy1Btn(6);     break;
		case Btn7:     nVirtualUpButton = joy1Btn(7);     break;
		case Btn8:     nVirtualUpButton = joy1Btn(8);     break;
		case Btn9:     nVirtualUpButton = joy1Btn(9);     break;
		case Btn10:     nVirtualUpButton = joy1Btn(10);    break;

		case Pov0:		 if(joystick.joy1_TopHat == 0)	nVirtualUpButton = 1;  	break;
		case Pov1:     if(joystick.joy1_TopHat == 1)	nVirtualUpButton = 1;  	break;
		case Pov2:     if(joystick.joy1_TopHat == 2)	nVirtualUpButton = 1;  	break;
		case Pov3:     if(joystick.joy1_TopHat == 3)	nVirtualUpButton = 1;  	break;
		case Pov4:     if(joystick.joy1_TopHat == 4)	nVirtualUpButton = 1;  	break;
		case Pov5:     if(joystick.joy1_TopHat == 5)	nVirtualUpButton = 1;		break;
		case Pov6:     if(joystick.joy1_TopHat == 6)	nVirtualUpButton = 1;   break;
		case Pov7:     if(joystick.joy1_TopHat == 7)	nVirtualUpButton = 1;   break;
		default:       nVirtualUpButton = 0;
	}

	switch(downButton)
	{
		case Btn1:     nVirtualDownButton = joy1Btn(1);     break;
		case Btn2:     nVirtualDownButton = joy1Btn(2);     break;
		case Btn3:     nVirtualDownButton = joy1Btn(3);     break;
		case Btn4:     nVirtualDownButton = joy1Btn(4);     break;
		case Btn5:     nVirtualDownButton = joy1Btn(5);     break;
		case Btn6:     nVirtualDownButton = joy1Btn(6);     break;
		case Btn7:     nVirtualDownButton = joy1Btn(7);     break;
		case Btn8:     nVirtualDownButton = joy1Btn(8);     break;
		case Btn9:     nVirtualDownButton = joy1Btn(9);     break;
		case Btn10:     nVirtualDownButton = joy1Btn(10);    break;

		case Pov0:		 if(joystick.joy1_TopHat == 0)	nVirtualDownButton = 1;  	break;
		case Pov1:     if(joystick.joy1_TopHat == 1)	nVirtualDownButton = 1;  	break;
		case Pov2:     if(joystick.joy1_TopHat == 2)	nVirtualDownButton = 1;  	break;
		case Pov3:     if(joystick.joy1_TopHat == 3)	nVirtualDownButton = 1;  	break;
		case Pov4:     if(joystick.joy1_TopHat == 4)	nVirtualDownButton = 1;  	break;
		case Pov5:     if(joystick.joy1_TopHat == 5)	nVirtualDownButton = 1;		break;
		case Pov6:     if(joystick.joy1_TopHat == 6)	nVirtualDownButton = 1;   break;
		case Pov7:     if(joystick.joy1_TopHat == 7)	nVirtualDownButton = 1;   break;
		default:       nVirtualDownButton = 0;
	}

	if(nVirtualUpButton)
	{
		setMotorSpeed(armMotorPort, armSpeed);
	}
	else if(nVirtualDownButton)
	{
		setMotorSpeed(armMotorPort, -armSpeed);
	}
	else
	{
		setMotorSpeed(armMotorPort, 0);
	}
}
