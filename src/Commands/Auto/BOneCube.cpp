/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Auto/BOneCube.h>

#define ANGLE  30.0

BOneCube::BOneCube(bool left) :  m_closeGrabber(false), m_turnAngle(left ? -ANGLE : ANGLE, 0.0, ETA_FORWARD, 1000),
						m_turnAngleSimple(left ? 0.0 : 0.3, left ? 0.3 : 0.0, 1800), m_moveGrabberUp(1.0, true, 3000),
						m_moveToTape(EVT_TAPE), m_moveToTapeSimple(0.4, 0.4, 3000), m_turnAngle2(left ? ANGLE : -ANGLE, 0.0, ETA_FORWARD, 1000),
						m_turnAngleSimple2(left ? 0.3 : 0.0, left ? 0.0 : 0.3, 1000), m_openGrabber(true), m_spinGrabber(1.0, -1.0, 2000)
{
	AddSequential(&m_closeGrabber);
	AddSequential(&m_turnAngle);
	//AddSequential(&m_turnAngleSimple);
	AddParallel(&m_moveGrabberUp);
	//AddSequential(&m_moveToTape);
	AddSequential(&m_moveToTapeSimple);
	AddSequential(&m_turnAngle2);
	//AddSequential(&m_turnAngleSimple2);
	AddSequential(&m_openGrabber);
	AddSequential(&m_spinGrabber);
}
