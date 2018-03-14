/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Auto/CL_AR.h>

CL_AR::CL_AR(bool left) : m_closeGrabber(false), m_moveToTape(EVT_TAPE), m_moveToTapeSimple(0.4, 0.4, 3000), m_moveGrabberUp(1.0, true, 3000),
			     m_spinGrabber(1.0, -1.0, 2000), m_openGrabber(true),
				 m_moveBack(-0.3, -0.3, 300), m_moveGrabberDown(1.0, false, 3000),
				 m_turnRightAngle(left ? 85.0 : -85.0, -0.05, ETA_SPOT, 3000), m_spinGrabberLong(-1.0, 1.0, 2000),
				 m_moveForward(0.4, 0.4, 2000), m_moveBackLong(-0.4, -0.4, 2000),
				 m_turnRightAngle2(left ? -90.0 : 90.0, 0.05, ETA_SPOT, 1000),
				 m_moveForwardShort(0.3, 0.3, 300), m_spinGrabber2(1.0, -1.0, 2000),
				 m_moveGrabberUp2(1.0, true, 3000), m_closeGrabber2(false), m_openGrabber2(true)
{
	AddSequential(&m_closeGrabber);
	//AddParallel(&m_moveToTape);
	AddParallel(&m_moveToTapeSimple);
	AddSequential(&m_moveGrabberUp);
	AddSequential(&m_openGrabber);
	AddSequential(&m_spinGrabber);
	AddSequential(&m_moveBack);
	AddParallel(&m_turnRightAngle);
	AddSequential(&m_moveGrabberDown);
	AddParallel(&m_spinGrabberLong);
	AddSequential(&m_moveForward);
	AddSequential(&m_closeGrabber2);
	AddParallel(&m_moveGrabberUp2);
	AddSequential(&m_moveBackLong);
	AddSequential(&m_turnRightAngle2);
	AddSequential(&m_moveForwardShort);
	AddSequential(&m_openGrabber2);
	AddSequential(&m_spinGrabber2);
}
