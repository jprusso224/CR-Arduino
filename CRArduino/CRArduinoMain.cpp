/*
 * CRArduinoMain.cpp
 *
 * Created: 1/7/2015 9:34:38 AM
 * Author: John Russo
 */ 

#include "CRArduinoMain.h"
#include "RangeFinder.h"

void CRArduinoMain::setup()
{
	rangeFinder.initRangeFinder(147,7);
	Serial.begin(115200);
}

void CRArduinoMain::loop()
{
	result = rangeFinder.readRange();
	Serial.println(result);
	delay(1000);
}

CRArduinoMain crArduinoMain;

