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
	enabled = true;
	pinMode(ePin,INPUT);
	digitalWrite(ePin,HIGH);
	pinMode(dirPin,INPUT);
	
	
}

void Encoder::encoderISR(){
	
	if(enabled){
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
	
}

int Encoder::getDistanceTraveled(){
	int distanceTraveled = 0;
	/*long mrad = long(pulseCount*10*2*PI)/_resolution; //(rad/1000)
	//Serial.print((String)mrad)
	if(_type == FRONT){
		mrad = mrad/GEAR_RATIO;
	}
    int distanceTraveled = int(mrad*WHEEL_RADIUS/10);*/
	float mrad = (pulseCount*2*PI)/(float)_resolution;
	if(_type == FRONT){
		mrad = mrad/GEAR_RATIO;
		distanceTraveled = (int)(mrad*WHEEL_RADIUS);
	}else{
		distanceTraveled = (int)(mrad*WHEEL_RADIUS);
	}
	return distanceTraveled;
}

int Encoder::getPulseCount(){
	return pulseCount;
}

void Encoder::enableEncoder(){
	enabled = true;
}
void Encoder::disableEncoder(){
	enabled = false;
}