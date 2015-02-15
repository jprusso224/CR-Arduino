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
	long int prevFrontLeftDistance;
	long int prevFrontRightDistance;
	long int prevBackLeftDistance;
	long int prevBackRightDistance;

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
	
};


#endif

