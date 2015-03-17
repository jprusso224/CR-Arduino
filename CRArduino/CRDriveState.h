// CRDriveState.h
//
// Author: John Paul Russo
// Date Created: 2/15/15

#ifndef _CRDRIVESTATE_h
#define _CRDRIVESTATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class CRDriveState
{
	
 protected:
 
    int _state;
	int _prevFrontLeftDistance;
	int _prevFrontRightDistance;
	int _prevBackLeftDistance;
	int _prevBackRightDistance;
	unsigned long _time;

 public:
 
	/**
	 * Default Constructor                                                    
	 */
	CRDriveState();
	
	/**
	 * get drive state   
	 *
	 * @param frontLeftDistance
	 * @param frontRightDistance
	 * @param backLeftDistance
	 * @param backRightDistance 
	 *
	 * @returns current drive state                                                 
	 */
	int getCRDriveState(int frontLeftDistance, int frontRightDistance, int backLeftDistance, int backRightDistance);
	
	/**
	 * set drive state    
	 *
	 * @param state Desired drive state.                                            
	 */
	void setCRDriveState(int state);
	int getOrientation();
	int getPrevFREncoderDistance();
	int getPrevFLEncoderDistance();
	int getPrevBREncoderDistance();
	int getPrevBLEncoderDistance();
	void setPrevFREncoderDistance(int distance);
	void setPrevFLEncoderDistance(int distance);
	void setPrevBREncoderDistance(int distance);
	void setPrevBLEncoderDistance(int distance);
	void setNewTime(unsigned long time);
	unsigned long getLastTime();
	
	
};


#endif

