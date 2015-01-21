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
	
	if(digitalRead(40) == HIGH){
		pulseCount++; 
		digitalWrite(13,HIGH);
	}
	else{
		pulseCount--;
		digitalWrite(13,LOW);
	}
}

int Encoder::getDistanceTraveled(){
	int deg = (pulseCount*360)/ENCODER_RESOLUTION;
	return deg;
}

