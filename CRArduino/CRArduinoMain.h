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
#else
	#include "WProgram.h"
#endif

#include "Encoder.h"
#include "RangeFinder.h"

class CRArduinoMain
{
 private:
	int result;
	Encoder backLeftEncoder;
	Encoder backRightEncoder;
	Encoder frontLeftEncoder;
	Encoder frontRightEncoder;
    
	String piInputString;
	boolean piInputStringComplete;
	char inChar;
	
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
};

extern CRArduinoMain crArduinoMain;

#endif

