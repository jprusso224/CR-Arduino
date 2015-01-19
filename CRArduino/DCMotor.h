// DCMotor.h

#ifndef _DCMOTOR_h
#define _DCMOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class DCMotor
{
 private:
	int _pwmPin;
	int _directionPin;
	int _enablePin;
	int _speed;
	int _direction;
	boolean enabled;

 public:
	void initDCMotor(int pwmPin, int directionPin, int enablePin, int direction);
	void setSpeed(int speed);
	int getSpeed();
	void setDirection(int direction);
	int getDirection();
	void enable();
	void disable();
};

#endif

