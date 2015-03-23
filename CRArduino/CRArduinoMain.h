/*
 * CRArduinoMain.h
 *
 * Created: 1/7/2015 9:34:38 AM
 * Author: John Russo
 */ 

#ifndef _CRARDUINOMAIN_h
#define _CRARDUINOMAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
	#include "Servo.h"
	#include "PID_v1.h"
#else
	#include "WProgram.h"
#endif

#include "Encoder.h"
#include "RangeFinder.h"
#include "DCMotor.h"
#include "CRDriveState.h"
#include <string.h>


class CRArduinoMain
{
 private:
	
	CRDriveState crDriveState;
	
	int result;
	Encoder backLeftEncoder;
	Encoder backRightEncoder;
	Encoder frontLeftEncoder;
	Encoder frontRightEncoder;
	int count;
	
	DCMotor leftMotor;
	DCMotor rightMotor;
	
	Servo panServo;
	Servo tiltServo;
    
	String piInputString;
	boolean piInputStringComplete;
	char inChar;
	
	int depth;
	int totalDepth;
	boolean startRappelFlag;
	
	int distanceTraveled; 
	double orientation;
	
 public:
	void setup();
	void loop();
	void backLeftEncoderISR();
	void backRightEncoderISR();
	void frontLeftEncoderISR();
	void frontRightEncoderISR();
	void parseCommand();
	void processDriveCommand();
	void processRappelCommand();
	void processStatusRequest();
	void blinkLED(int num);
	void processImageCommand();
};

extern CRArduinoMain crArduinoMain;

#endif

