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
	//attachInterrupt(2,backLeftEncoderISR,FALLING); //pin 21
	//attachInterrupt(3,backRightEncoderISR,FALLING); //pin 20
	//attachInterrupt(5,frontLeftEncoderISR,FALLING); //pin 19
	//attachInterrupt(4,frontRightEncoderISR,FALLING); //pin 18
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