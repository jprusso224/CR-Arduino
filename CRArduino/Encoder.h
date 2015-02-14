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
	volatile long pulseCount;
	int _type;
	
 public:
	void initEncoder(int interruptNumber, int resolution, int type);
	int getDistanceTraveled();
	void encoderISR();
};

#endif

