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
	int delay = pulseIn(_rangePin,HIGH);
	range = delay/_resolution;
	return range;
}

RangeFinder rangeFinder;

