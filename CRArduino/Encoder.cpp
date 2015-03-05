// 
// 
// 

#include "Encoder.h"

void Encoder::initEncoder(int interruptNumber, int resolution, int type, int side,int dirPin,int ePin){
	_interruptNumber = interruptNumber;
	_resolution = resolution;
	_type = type;
	_side = side;
	_dirPin = dirPin;
	_ePin = ePin;
	pulseCount = 0L;
	pinMode(ePin,INPUT);
	digitalWrite(ePin,HIGH);
	pinMode(dirPin,INPUT);
	
}

void Encoder::encoderISR(){
	
	if(_side == LEFT){
		if(digitalRead(_dirPin) == HIGH){
			pulseCount--;
		}
		else{
			pulseCount++;
		}
	}else{
		if(digitalRead(_dirPin) == HIGH){
			pulseCount++;
		}
		else{
			pulseCount--;
		}
	}
	
}

int Encoder::getDistanceTraveled(){
	
	long mrad = long(pulseCount*10*2*PI)/_resolution; //(rad/1000)
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