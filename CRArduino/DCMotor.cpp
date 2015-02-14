// 
// 
// 

#include "DCMotor.h"
#include "crconstants.h"

void DCMotor::initDCMotor(int pwmPin, int directionPin, int enablePin, int direction)
{
	_pwmPin = pwmPin;
	_directionPin = directionPin;
	_enablePin = enablePin;
	_speed = 0;
	enabled = false;
	_direction = direction;
}

void DCMotor::setSpeed(int pwmValue){
	//_speed = speed;
	//int pwmValue = speed/(MAX_RPM/255);
	analogWrite(_pwmPin,pwmValue);
}

int DCMotor::getSpeed(){
	return _speed;
}

void DCMotor::setDirection(int direction){
	_direction = direction;
	digitalWrite(_directionPin,_direction);
}

int DCMotor::getDirection(){
	return _direction;
}

void DCMotor::enable(){
	enabled = true;
	digitalWrite(_enablePin,HIGH);
}

void DCMotor::disable(){
	enabled = false;
	digitalWrite(_enablePin,LOW);
}

