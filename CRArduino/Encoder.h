// Encoder.h

#ifndef _ENCODER_h
#define _ENCODER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "crconstants.h"

class Encoder
{
 protected:
	int _interruptNumber;
	int _resolution;
	long pulseCount;
	int _type;
	int _side;
	int _ePin;
	int _dirPin;
	boolean enabled;
	
 public:
	void initEncoder(int interruptNumber, int resolution, int type, int side, int dirPin,int ePin);
	int getDistanceTraveled();
	void encoderISR();
	int getPulseCount();
	void enableEncoder();
	void disableEncoder();
	void setPulseCount(int cnt);
};

#endif

