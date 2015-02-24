/*
 * RangeFinder.h
 *
 * Created: 1/7/2015 
 * Author: John Russo
 */ 


#ifndef _RANGEFINDER_h
#define _RANGEFINDER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class RangeFinder{
 protected:
	int range;
	int _resolution;
	int _rangePin;

 public:
	void initRangeFinder(int resolution,int rangePin);
	int readRange();
	int readAnRange();
};

extern RangeFinder rangeFinder;

#endif

