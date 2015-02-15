// 
// 
// 

#include "CRDriveState.h"

CRDriveState::CRDriveState()
{
	_state = 1;
	prevFrontLeftDistance = 0;
	prevFrontRightDistance = 0;
	prevBackLeftDistance = 0;
	prevBackRightDistance = 0;
}

int CRDriveState::getCRDriveState(int frontLeftDistance, int frontRightDistance, int backLeftDistance, int backRightDistance){
	//return 1
	return 1;
}

void CRDriveState::setCRDriveState(int state){
	_state = state;
}