// 
// 
// 

#include "CRDriveState.h"

CRDriveState::CRDriveState()
{
	_state = 1;
	_prevFrontLeftDistance = 0;
	_prevFrontRightDistance = 0;
	_prevBackLeftDistance = 0;
	_prevBackRightDistance = 0;
	_time = micros();
}

int CRDriveState::getCRDriveState(int frontLeftDistance, int frontRightDistance, int backLeftDistance, int backRightDistance){
	//return 1
	return 1;
}

void CRDriveState::setCRDriveState(int state){
	_state = state;
}

int CRDriveState::getPrevBLEncoderDistance(){
	return _prevBackLeftDistance;
}

int CRDriveState::getPrevFLEncoderDistance(){
	return _prevFrontLeftDistance;
}

int CRDriveState::getPrevBREncoderDistance(){
	return _prevBackRightDistance;
}

int CRDriveState::getPrevFREncoderDistance(){
	return _prevFrontRightDistance;
}

void CRDriveState::setPrevBLEncoderDistance(int distance){
	_prevBackLeftDistance = distance;
}

void CRDriveState::setPrevFLEncoderDistance(int distance){
	_prevFrontLeftDistance = distance;
}

void CRDriveState::setPrevBREncoderDistance(int distance){
	_prevBackRightDistance = distance;
}

void CRDriveState::setPrevFREncoderDistance(int distance){
	_prevFrontRightDistance = distance;
}

//May be simply enough to call micros/millis here
void CRDriveState::setNewTime(unsigned long time){
	_time = time;
	
}

unsigned long CRDriveState::getLastTime(){
	return _time;
}