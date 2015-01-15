/*
 * CRArduinoMain.cpp
 *
 * Created: 1/7/2015 9:34:38 AM
 * Author: John Russo
 */ 

#include "CRArduinoMain.h"
#include "Encoder.h"
#include "RangeFinder.h"
#include "crconstants.h"

void CRArduinoMain::setup()
{
	//rangeFinder.initRangeFinder(147,7);
	backLeftEncoder.initEncoder(0,ENCODER_RESOLUTION);
	backRightEncoder.initEncoder(1,ENCODER_RESOLUTION);
	frontLeftEncoder.initEncoder(2,ENCODER_RESOLUTION);
	frontLeftEncoder.initEncoder(3,ENCODER_RESOLUTION);
}

void CRArduinoMain::loop()
{
	//result = rangeFinder.readRange();
	//Serial.println(result);
	//delay(1000);
}


/**
 * Encoder interrupt handlers                                                    
 */
void CRArduinoMain::backLeftEncoderISR(){
	backLeftEncoder.encoderISR();
}

void CRArduinoMain::backRightEncoderISR(){
	backRightEncoder.encoderISR();
}

void CRArduinoMain::frontLeftEncoderISR(){
	frontLeftEncoder.encoderISR();
}

void CRArduinoMain::frontRightEncoderISR(){
	frontRightEncoder.encoderISR();
}

CRArduinoMain crArduinoMain;

