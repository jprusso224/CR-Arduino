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

class CRArduinoMain
{
 private:
	int result;

 public:
	void setup();
	void loop();
};

extern CRArduinoMain crArduinoMain;

#endif

