#include "CRDriveState.h"
#include "DCMotor.h"
#include "Encoder.h"
#include "RangeFinder.h"
/*
 * CRArduino.ino
 *
 * Created: 1/7/2015 9:34:38 AM
 * Author: John Russo
 */ 

#include "CRArduinoMain.h"

void setup()
{
	crArduinoMain.setup();
	attachInterrupt(2,backLeftEncoderISR,HIGH);
	attachInterrupt(3,backLeftEncoderISR,HIGH);
	attachInterrupt(4,backLeftEncoderISR,HIGH);
	attachInterrupt(5,backLeftEncoderISR,HIGH);
}

void loop()
{
	crArduinoMain.loop();
}


/**
 * Encoder interrupt wrappers                                                    
 */
void backLeftEncoderISR(){
	crArduinoMain.backLeftEncoderISR();
}
void backRightEncoderISR(){
	crArduinoMain.backRightEncoderISR();
}
void frontLeftEncoderISR(){
	crArduinoMain.frontLeftEncoderISR();
}
void frontRightEncoderISR(){
	crArduinoMain.frontRightEncoderISR();
}