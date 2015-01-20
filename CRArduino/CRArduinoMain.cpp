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
	backLeftEncoder.initEncoder(2,ENCODER_RESOLUTION);
	backRightEncoder.initEncoder(3,ENCODER_RESOLUTION);
	frontLeftEncoder.initEncoder(4,ENCODER_RESOLUTION);
	frontLeftEncoder.initEncoder(5,ENCODER_RESOLUTION);
	
	//DC motors
	leftMotor.initDCMotor(7,30,31,0);
	rightMotor.initDCMotor(8,32,33,1);	
	
	//Servos
	panServo.attach(9);
	tiltServo.attach(10);
	
	//setup LED
	pinMode(13,OUTPUT);
	inChar = 0;
	piInputString = "";
	piInputStringComplete = false;
	Serial.begin(115200);
}

void CRArduinoMain::loop()
{
	
	while (Serial.available() > 0) {
		// get the new byte
		inChar = (char)Serial.read();
		// add it to the inputString
		piInputString += inChar;
		// if the incoming character is a newline, set a flag (end of command)
		if (inChar == '\n') {
			piInputStringComplete = true;
		}
	}
	delay(250); // Doesn't work without this. My guess is it gives the serial buffer time to fill if the message isn't complete.
	
	if(piInputStringComplete){
		//if its a command
		if(piInputString[0] == '$'){
		//	TIMSK3 |= (0 << TOIE3); //disable overflow interrupt
			parseCommand();
		//	TIMSK3 |= (1 << TOIE3); //enable overflow interrupt
			piInputString = "";
			piInputStringComplete = false;
		}
	}
	
	//result = rangeFinder.readRange();
	//Serial.println(result);
	//delay(1000);
}

void CRArduinoMain::parseCommand(){
	char commandType;
	commandType = piInputString[1];
	switch(commandType){
		case 'R':
		processRappelCommand();
		break;
		case 'D':
		processDriveCommand();
		break;
		case 'I':
		processImageCommand();
		break;
		default:
		processStatusRequest();
		break;
	}
}

void CRArduinoMain::processDriveCommand(){
	blinkLED(5);
	Serial.print("$DP\n");
	Serial.flush();
}

void CRArduinoMain::processRappelCommand(){
		blinkLED(4);
		Serial.print("$RP\n");
		Serial.flush();
}

void CRArduinoMain::processStatusRequest(){
		blinkLED(3);
		Serial.print("$SP\n");
		Serial.flush();
}

/**
 * Blink LED n number of times.                                                    
 */
void CRArduinoMain::blinkLED(int num){
	delay(500);
	for(int i = 0;i<num;i++){
		digitalWrite(13,LOW);
		delay(250);
		digitalWrite(13,HIGH);
		delay(250);
		digitalWrite(13,LOW);
		delay(250);
	}
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

void CRArduinoMain::processImageCommand(){
	String temp = piInputString.substring(3,4);
	int pan = temp.toInt();
	temp = piInputString.substring(5,6);
	int tilt = temp.toInt();
	if (piInputString[2] == '+'){
		pan += 90;
	}
	panServo.write(pan); //These values are in angle under 200 but we want to change to ms (1000-2000) for 0-180 deg eventually to be more precise
	delay(15);
	tiltServo.write(tilt);
	delay(15);
	Serial.print("$IP\n");
	Serial.flush();
}

CRArduinoMain crArduinoMain;

