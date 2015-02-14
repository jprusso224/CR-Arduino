// 
// 
// 

#include "Encoder.h"

void Encoder::initEncoder(int interruptNumber, int resolution, int type){
	_interruptNumber = interruptNumber;
	_resolution = resolution;
	_type = type;
	pulseCount = 0L;
}

void Encoder::encoderISR(){
	
	if(digitalRead(40) == HIGH){
		pulseCount++; 
	}
	else{
		pulseCount--;
	}
}

int Encoder::getDistanceTraveled(){
	long mrad = long(pulseCount*1000*2*PI)/ENCODER_RESOLUTION; //(rad/1000)
	if(_type == FRONT){
		mrad = mrad/GEAR_RATIO;
	}
    int distanceTraveled = (mrad*WHEEL_RADIUS)/1000; 
	return distanceTraveled;
}

