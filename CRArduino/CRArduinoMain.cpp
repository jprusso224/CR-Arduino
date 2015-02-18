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
	
	//Drive State
	crDriveState = CRDriveState();
	count = 0;
	//Range-finder
	rangeFinder.initRangeFinder(RANGE_RESOLUTION,RANGEFINDER_PIN);
	depth = 0;
	totalDepth = 0;
	startRappelFlag = true;
	distanceTraveled = 0; 
	
	//Encoders
	backLeftEncoder.initEncoder(BACK_LEFT_ENCODER_INT,ENCODER_RESOLUTION,BACK);
	//backRightEncoder.initEncoder(BACK_RIGHT_ENCODER_INT,ENCODER_RESOLUTION,BACK);
	//frontLeftEncoder.initEncoder(FRONT_LEFT_ENCODER_INT,ENCODER_RESOLUTION,FRONT);
	//frontLeftEncoder.initEncoder(FRONT_RIGHT_ENCODER_INT,ENCODER_RESOLUTION,FRONT);
	pinMode(21,INPUT);
	pinMode(40,INPUT);
	pinMode(22,OUTPUT);
	digitalWrite(22,LOW);
	
	  //DC motors
		leftMotor.initDCMotor(LEFT_MOTOR_PWM_PIN,LEFT_MOTOR_DIR_PIN,LEFT_MOTOR_EN_PIN,MOTOR_CCW);
		rightMotor.initDCMotor(RIGHT_MOTOR_PWM_PIN,RIGHT_MOTOR_DIR_PIN,RIGHT_MOTOR_EN_PIN,MOTOR_CW);	
		pinMode(7,OUTPUT);
		pinMode(30,OUTPUT);
	
	//Servos
	tiltServo.attach(TILT_SERVO_PIN);
	panServo.attach(PAN_SERVO_PIN);
	
	//setup LED
	pinMode(13,OUTPUT);
	inChar = 0;
	piInputString = "";
	piInputStringComplete = false;
	Serial.begin(115200);
}

void CRArduinoMain::loop()

{
	//delay(250);
	//Serial.println(backLeftEncoder.getDistanceTraveled());
	
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
	
	//Motor Test
}

void CRArduinoMain::parseCommand(){
	char commandType;
	Serial.println("Command Received");
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
	
	String targetString = "";
	int driveDistance = 0;
	long int startCount = 0L;
	long int targetCount = 0L;
	char fromCR = NULL;
	int frontDistanceAvg =0;
	int rearDistanceAvg =0;
	int targetDistance = 0;
	int relativeDistance = 0;
	int motorSpeed = 0;
	long currPulseCount = 0L;
	int startDistance = 0;
	
	/*Determine whether turning or driving*/
	char driveType;
	driveType = piInputString[2];
	
	switch (driveType)
	{
		case 'L':
		    break;
		case 'R':
			break;
		case 'B':
			break;
		default:
			
			rightMotor.setDirection(MOTOR_CW);
			leftMotor.setDirection(MOTOR_CCW);
			
			//Extract Command
			targetString = piInputString.substring(3,6);
		
			driveDistance = targetString.toInt();
			
			//Set Drive target	
			targetDistance = distanceTraveled + driveDistance*10; //Both need to be in mm.
			startDistance = distanceTraveled;
			
			while(distanceTraveled < targetDistance){
				delay(100);
				//Serial.println(distanceTraveled);
				currPulseCount = backRightEncoder.getPulseCount();
				//Serial.println(currPulseCount);
				//Get distance Traveled via average
				//rearDistanceAvg = (backLeftEncoder.getDistanceTraveled() + backRightEncoder.getDistanceTraveled())/2;
				//frontDistanceAvg = (frontLeftEncoder.getDistanceTraveled() + frontRightEncoder.getDistanceTraveled())/2;
				//distanceTraveled = rearDistanceAvg + frontDistanceAvg;
				distanceTraveled = backRightEncoder.getDistanceTraveled();
				relativeDistance = distanceTraveled - startDistance;
				Serial.println(relativeDistance);
				//Determine how fast to drive motor
				if(relativeDistance < 100){
					//ramp up
					motorSpeed =((relativeDistance*255)/100);
				}else if(targetDistance - distanceTraveled < 100){
					//ramp down
					motorSpeed = (((targetDistance - distanceTraveled)*255)/100) - 255;
				}else{
					//Serial.print("Max Speed!");
					motorSpeed = 255;
				}
				
				//Serial.println("Speed Set: " + String(motorSpeed));
				rightMotor.setSpeed(motorSpeed);
				leftMotor.setSpeed(motorSpeed);
			}
			
			rightMotor.setSpeed(0);
			leftMotor.setSpeed(0);
		    break;
	}
	Serial.print("$DP\n"); 
	Serial.flush();
}

void CRArduinoMain::processRappelCommand(){
	
	    //Declare variables
		int range;
		String depthStr;
		int rangeArray[] = {0, 0};
		
		//Read range-finder (may want an average for the beginning of rappel stage.)
		range = rangeFinder.readRange();
		if(startRappelFlag){
			//get average range
			rangeArray[0] = rangeFinder.readRange();
			rangeArray[1] = rangeFinder.readRange();
			totalDepth =  (range+rangeArray[0]+rangeArray[1])/3;
			startRappelFlag = false;
		}
		//Compute depth
		depth = totalDepth - range;
		if(depth < 0){depth = 0;}
		
		//Convert depth to string and send to serial port.
		depthStr = String(depth);
		if(depthStr.length() == 3){
		Serial.print("$RP"+depthStr+"\n");
		}else if(depthStr.length() == 2){
			Serial.print("$RP0"+depthStr+"\n");
		}else{
			Serial.print("$RP00"+depthStr+"\n");
		}
		Serial.flush();
		
}

void CRArduinoMain::processStatusRequest(){
		blinkLED(3);
		Serial.print("$SP\n");
		Serial.flush();
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

CRArduinoMain crArduinoMain;

