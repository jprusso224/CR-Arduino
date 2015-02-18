// 
// 
// 

#include "Encoder.h"

void Encoder::initEncoder(int interruptNumber, int resolution, int type){
	_interruptNumber = interruptNumber;
	_resolution = resolution;
	_type = type;
	pulseCount = 0L;
	pinMode(BACK_RIGHT_ENCODER_PIN,INPUT);
	digitalWrite(BACK_RIGHT_ENCODER_PIN,HIGH);
	
}

void Encoder::encoderISR(){
	
	if(digitalRead(24) == HIGH){
		pulseCount++; 
	}
	else{
		pulseCount--;
	}
}

int Encoder::getDistanceTraveled(){
	long mrad = long(pulseCount*1000*2*PI)/ENCODER_RESOLUTION; //(rad/1000)
	//Serial.print((String)mrad)
	if(_type == FRONT){
		mrad = mrad/GEAR_RATIO;
	}
    int distanceTraveled = int(mrad*WHEEL_RADIUS/10); 
	return distanceTraveled;
}

int Encoder::getPulseCount(){
	return pulseCount;
}