#ifndef __FirmwareVersion_
#define __FirmwareVersion_

//
// 23 Nov 2013
// 2014 Feb 14
//
#define kLastCompatibleVersionFirmware	(1027)
#define kLastCompatibleVersionIDE				(427)

#define kFirmwareVersion  			(1027)
#define pzFirmwareVersion				"1027" 								// Used in building default file name

#define kRobotCVersion					"4.27"
#define kRobotCVersionNumeric		427										// Used as numeric in a preprocessor "#define" symbol created by the ROBOTC Compiler.

#define kLatestVEX_PIC_MasterFirmwareVersion					10

#define kLatestVEX_Cortex_MasterFirmwareVersion				((4 << 8) | ( 23 << 0))		// 4.23
#define kLatestVEX_Joystick_FirmwareVersion						((4 << 8) | ( 23 << 0))		// 4.23

#define kLatestVexIqBrain_FirmwareVersion							((1 << 8) | ( 13 << 0))		// 1.13  // Update this when brain firmware is upgraded
#define kLatestVexIqController_FirmwareVersion				((1 << 8) | ( 4 << 0))		// 1.04

#if defined(_WINDOWS)
	#define sLatestVexNet_1_5FirmwareFile								"WIFI_MASTER_V"		"13_1"		".BIN"
	#define sLatestVEX_Cortex_MasterFirmwareVersion			"CORTEX_V"    		"4_23"		".BIN"
	#define sLatestVEX_Joystick_FirmwareVersion					"JOY_V"						"4_23"		".BIN"
	#define	sLatestEV3Kernel_FimrwareVersion						"106X"
#endif

#endif
