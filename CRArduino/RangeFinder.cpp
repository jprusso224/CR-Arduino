/*
 * RangeFinder.cpp
 *
 * Created: 1/7/2015 
 * Author: John Russo
 */ 

#include "RangeFinder.h"

void RangeFinder::initRangeFinder(int resolution,int rangePin)
{
	_resolution = resolution;
	_rangePin = rangePin;
	pinMode(rangePin,INPUT);
	range = 0;
}

int RangeFinder::readRange(){
	int delayIn = pulseIn(_rangePin,HIGH);
	range = delayIn/_resolution;
	return range;
}

int RangeFinder::readAnRange(){
	int voltage = analogRead(A9);
	range = (voltage/49)*10;
	return range;
}

RangeFinder rangeFinder;

