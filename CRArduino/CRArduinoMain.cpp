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
	orientation = 0;
	
	//Encoders
	backLeftEncoder.initEncoder(BACK_LEFT_ENCODER_INT,ENCODER_RESOLUTION_REAR,BACK,LEFT,24,BACK_LEFT_ENCODER_PIN);
	backRightEncoder.initEncoder(BACK_RIGHT_ENCODER_INT,ENCODER_RESOLUTION_REAR,BACK,RIGHT,25,BACK_RIGHT_ENCODER_PIN);
	frontLeftEncoder.initEncoder(FRONT_LEFT_ENCODER_INT,ENCODER_RESOLUTION_FRONT,FRONT,LEFT,27,FRONT_LEFT_ENCODER_PIN);
	frontRightEncoder.initEncoder(FRONT_RIGHT_ENCODER_INT,ENCODER_RESOLUTION_FRONT,FRONT,RIGHT,26,FRONT_RIGHT_ENCODER_PIN);
	
	  //DC motors
		leftMotor.initDCMotor(LEFT_MOTOR_PWM_PIN,LEFT_MOTOR_DIR_PIN,LEFT_MOTOR_EN_PIN,MOTOR_CCW);
		rightMotor.initDCMotor(RIGHT_MOTOR_PWM_PIN,RIGHT_MOTOR_DIR_PIN,RIGHT_MOTOR_EN_PIN,MOTOR_CW);	
		pinMode(7,OUTPUT);
		pinMode(30,OUTPUT);
		pinMode(8,OUTPUT);
		pinMode(32,OUTPUT);
		digitalWrite(7,LOW);
		digitalWrite(8,LOW);
	
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
	delay(100); // Doesn't work without this. My guess is it gives the serial buffer time to fill if the message isn't complete.
	
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
	double driveAngle = 0;
	double targetAngle = 0;
	long int startCount = 0L;
	long int targetCount = 0L;
	char fromCR = NULL;
	int frontDistanceAvg =0;
	int rearDistanceAvg =0;
	int targetDistance = 0;
	int frontRightDistance = 0;
	int frontLeftDistance = 0;
	int backRightDistance = 0;
	int backLeftDistance = 0;
	int relativeDistance = 0;
	int motorSpeed = 0;
	long currPulseCount = 0L;
	int startDistance = 0;
	int turnDistance = 0;
	int deltaFrontLeftDistance = 0;
	int deltaFrontRightDistance = 0;
	double turnDistAvg = 0;
	double speedFL = 0;
	double speedFR = 0;
	double pwmFL = 0;
	double pwmFR = 0;
	unsigned long currTime = 0;
	unsigned long deltaTime = 0;
	double desiredSpeed = DRIVE_SPEED;
	int driveCounter = 0;
	
	/*Determine whether turning or driving*/
	char driveType;
	driveType = piInputString[2];
	
	switch (driveType)
	{
		case 'L': //turn left
			//turn off back encoders
			backLeftEncoder.disableEncoder();
			backRightEncoder.disableEncoder();
		    rightMotor.setDirection(MOTOR_CW);
		    leftMotor.setDirection(MOTOR_CW);
			
			//Extract command
			targetString = piInputString.substring(3,6);
			driveAngle = targetString.toInt();
			motorSpeed = 255;
			//Set Drive target
			targetAngle = orientation - ((double)driveAngle*1000.0*(PI/180.0)); //Both need to be in mm.
			Serial.println("DO: " + (String)driveAngle);
			Serial.println("TO: " + (String)targetAngle);
			
			//loop
			while(orientation > targetAngle){ 
				
				delay(25);
				frontLeftDistance = frontLeftEncoder.getDistanceTraveled();
				frontRightDistance = frontRightEncoder.getDistanceTraveled();
				Serial.println("FL: " + (String)frontLeftDistance);
				Serial.println("FR: " + (String)frontRightDistance);
				
				turnDistAvg = (frontLeftEncoder.getDistanceTraveled() - frontRightEncoder.getDistanceTraveled())/2.0;
				//convert distance (arc length) to angle using the radius to the wheels S = r*theta, solve for theta (rad)
				orientation = ((turnDistAvg*1000.0)/DRIVE_SHAFT_RADIUS/TURN_SCALE);
				
				Serial.println("O: " + (String)orientation);
				
				rightMotor.setSpeed(motorSpeed);
				leftMotor.setSpeed(motorSpeed);
			}
			rightMotor.setSpeed(0);
			leftMotor.setSpeed(0);
			delay(200);
			frontLeftDistance = frontLeftEncoder.getDistanceTraveled();
			frontRightDistance = frontRightEncoder.getDistanceTraveled();
			Serial.println("FL: " + (String)frontLeftDistance);
			Serial.println("FR: " + (String)frontRightDistance);
			turnDistAvg = (frontLeftEncoder.getDistanceTraveled() - frontRightEncoder.getDistanceTraveled())/2.0;
			orientation = ((turnDistAvg*1000.0)/DRIVE_SHAFT_RADIUS/TURN_SCALE);
			Serial.println("O: " + (String)orientation);
			//Turn on back encoders
			backLeftEncoder.enableEncoder();
			backRightEncoder.enableEncoder();
			break;
			
		case 'R': //turn right
			//turn off back encoders
			backLeftEncoder.disableEncoder();
			backRightEncoder.disableEncoder();
			rightMotor.setDirection(MOTOR_CCW);
			leftMotor.setDirection(MOTOR_CCW);
			
				//Extract command
				targetString = piInputString.substring(3,6);
				driveAngle = targetString.toInt();
				
				motorSpeed = 255;
				//Set Drive target
				targetAngle = orientation + ((double)driveAngle*1000.0*(PI/180.0)); //watch for overflow
				Serial.println("DO: " + (String)driveAngle);
				Serial.println("TO: " + (String)targetAngle);
				//loop
				while(orientation < targetAngle){
					
					delay(25);
						frontLeftDistance = frontLeftEncoder.getDistanceTraveled();
						frontRightDistance = frontRightEncoder.getDistanceTraveled();
						Serial.println("FL: " + (String)frontLeftDistance);
						Serial.println("FR: " + (String)frontRightDistance);
					
					turnDistAvg = (frontLeftEncoder.getDistanceTraveled() - frontRightEncoder.getDistanceTraveled())/2.0;
					//convert distance (arc length) to angle using the radius to the wheels S = r*theta, solve for theta (rad)
					orientation = ((turnDistAvg*1000.0)/DRIVE_SHAFT_RADIUS/TURN_SCALE);
					Serial.println("O: " + (String)orientation);
					rightMotor.setSpeed(motorSpeed);
					leftMotor.setSpeed(motorSpeed);
				}
				rightMotor.setSpeed(0);
				leftMotor.setSpeed(0);
				delay(200);
				frontLeftDistance = frontLeftEncoder.getDistanceTraveled();
				frontRightDistance = frontRightEncoder.getDistanceTraveled();
				Serial.println("FL: " + (String)frontLeftDistance);
				Serial.println("FR: " + (String)frontRightDistance);
				turnDistAvg = (frontLeftEncoder.getDistanceTraveled() - frontRightEncoder.getDistanceTraveled())/2.0;
				orientation = ((turnDistAvg*1000.0)/DRIVE_SHAFT_RADIUS/TURN_SCALE);
				Serial.println("O: " + (String)orientation);
				//Turn on back encoders
				backLeftEncoder.enableEncoder();
				backRightEncoder.enableEncoder();
				break;
			
		case 'B':
			break;
			
		default:
			
			//Declare
			PID pidFL(&speedFL,&pwmFL,&desiredSpeed,0.25,0.5,0.01,DIRECT);
			PID pidFR(&speedFR,&pwmFR,&desiredSpeed,0.25,0.5,0.01,DIRECT);
			pidFL.SetMode(AUTOMATIC);
			pidFR.SetMode(AUTOMATIC);
			rightMotor.setDirection(MOTOR_CW);
			leftMotor.setDirection(MOTOR_CCW);
			rightMotor.setSpeed(0);
			leftMotor.setSpeed(0);
			
			targetString = piInputString.substring(3,6);
		
			driveDistance = targetString.toInt();
			
			//Set Drive target	
			targetDistance = distanceTraveled + driveDistance*10; //Both need to be in mm.
			startDistance = distanceTraveled;
			
			while(distanceTraveled < targetDistance){
				delay(50);
				//Serial.println(distanceTraveled);
				//currPulseCount = frontLeftEncoder.getPulseCount();
				//Serial.println(currPulseCount);
				//Get distance Traveled via average
				backLeftDistance = backLeftEncoder.getDistanceTraveled();
				backRightDistance = backRightEncoder.getDistanceTraveled();
				rearDistanceAvg = (backLeftDistance + backRightDistance)/2;
				frontLeftDistance = frontLeftEncoder.getDistanceTraveled();
				frontRightDistance = frontRightEncoder.getDistanceTraveled();
				frontDistanceAvg = (frontLeftDistance + frontRightDistance)/2;
				distanceTraveled = rearDistanceAvg;// + frontDistanceAvg)/2;
			    //distanceTraveled = frontRightEncoder.getDistanceTraveled();
				relativeDistance = distanceTraveled - startDistance;
				//Serial.println("PL:" +  String(currPulseCount));
				currPulseCount = frontRightEncoder.getPulseCount();
				//Serial.println("PBL:" +  String(currPulseCount));
				if(driveCounter == 3){
				Serial.println("$DFLD:" +  String(frontLeftDistance));
				Serial.println("$DFRD:" +  String(frontRightDistance));
				Serial.println("$DBLD:" +  String(backLeftDistance));
				Serial.println("$DBRD:" +  String(backRightDistance));
				}
				//Serial.println("FR:" + String(frontRightDistance));
				//Serial.println(relativeDistance);
				
				
				/*
				//Determine how fast to drive motor
				if(relativeDistance < 50){
					//ramp up
					motorSpeed =((relativeDistance*50)/50) + 50;
				}else if(targetDistance - distanceTraveled < 50){
					//ramp down
					motorSpeed = ((((targetDistance - distanceTraveled)*50)/50) - 255) + 50;
				}else{
					//Serial.print("Max Speed!");
					motorSpeed = 85;
				}
				*/
				//motorSpeed = 50;
				//Serial.println("Speed Set: " + String(motorSpeed));
				
				
				//Speed correction algorithm here:
				deltaFrontLeftDistance = frontLeftDistance - crDriveState.getPrevFLEncoderDistance();
				deltaFrontRightDistance = frontRightDistance - crDriveState.getPrevFREncoderDistance();
				crDriveState.setPrevFREncoderDistance(frontRightDistance);
				crDriveState.setPrevFLEncoderDistance(frontLeftDistance);
				
				currTime = millis();
				deltaTime = currTime - crDriveState.getLastTime();
				crDriveState.setNewTime(currTime);
				
				//Serial.println("DT: " + (String)deltaTime);
				
				speedFL = ((deltaFrontLeftDistance*1000)/deltaTime);
				speedFR = ((deltaFrontRightDistance*1000)/deltaTime);
				
				if(driveCounter == 3){
					Serial.println("$DFLS: " + (String)(speedFL));
					Serial.println("$DFRS: " + (String)(speedFR));
					Serial.println("$DpwmL: " + (String)(pwmFL));
					Serial.println("$DpwmR: " + (String)(pwmFR));
				//	Serial.println("FLDD: " + (String)(deltaFrontLeftDistance));
				//	Serial.println("FRDD: " + (String)(deltaFrontRightDistance));
				//	Serial.println("DT: " +  (String)(deltaTime));
				
					driveCounter = 0;
					
				}
				
				/*
				if(speedFL < desiredSpeed){
					pwmFL = pwmFL + 5;
				}else if(speedFL > desiredSpeed){
					pwmFL = pwmFL - 5;
				}
				if(speedFR < desiredSpeed){
					pwmFR = pwmFR + 5;
				}else if(speedFR > desiredSpeed){
					pwmFR = pwmFR - 5;
				}*/
				
				pidFL.Compute();
				pidFR.Compute();
				
				//Don't let the CR attack Thomas.
				if(pwmFL > 250){
					pwmFL = 250;
				}
				if(pwmFR > 250){
					pwmFR = 250;
				}
				if(pwmFL < 0){
					pwmFL = 0;
				}
				if(pwmFR < 0){
					pwmFR = 0;
				}
			
			
				leftMotor.setSpeed(pwmFL);
				rightMotor.setSpeed(pwmFR);
				
				driveCounter++;
			}
			
			rightMotor.setSpeed(0);
			leftMotor.setSpeed(0);
		    break;
	}
	delay(200);

	Serial.print("$DP\n"); 
	Serial.flush();
}

void CRArduinoMain::processRappelCommand(){
	
		
	    //Declare variables
		int range = 0;
		String depthStr = "";
		int rangeArray[] = {0, 0};
		
		//Read range-finder (may want an average for the beginning of rappel stage.)
		range = rangeFinder.readRange();
		if(startRappelFlag){
			//get average range
			rangeArray[0] = rangeFinder.readRange();
			rangeArray[1] = rangeFinder.readRange();
			totalDepth =  (range+rangeArray[0]+rangeArray[1])/3  -  20;
			//range = totalDepth; // Force the initial calculated depth to be zero
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
	float pan = temp.toInt();
	temp = piInputString.substring(5,6);
	float tilt = temp.toInt();
	if (piInputString[2] == '+'){
		pan += 90;
	}
	// pan ranging from 0-180 but input 0 or +/-90 so 0 = 90 here
	// tilt ranging from 0-90
	tilt = 650+(885/90)*tilt;
	pan = 950+(47.5/90)*pan;
	panServo.write(pan);
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

