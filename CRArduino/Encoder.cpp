// 
// 
// 

#include "Encoder.h"

void Encoder::initEncoder(int interruptNumber, int resolution){
	_interruptNumber = interruptNumber;
	_resolution = resolution;
	pulseCount = 0L;
}

void Encoder::encoderISR(){
	pulseCount++;
}

int Encoder::getDistanceTraveled(){
	return 0; //Convert pulseCount to distance in cm
}

