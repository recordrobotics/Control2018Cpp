/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "BL_BR.h"

#define ANGLE  30.0

BL_BR::BL_BR(bool left) : m_closeGrabber(false), m_turnAngle(left ? -ANGLE : ANGLE, ETA_FORWARD),
						  m_moveToTape(EVT_TAPE), m_moveGrabberUp(true), m_openGrabber(true)
{
	AddSequential(m_closeGrabber);
	AddSequential(m_turnAngle);
	AddParallel(m_moveToTape);
	AddSequential(m_moveGrabberUp);
	AddSequential(m_openGrabber);
}
