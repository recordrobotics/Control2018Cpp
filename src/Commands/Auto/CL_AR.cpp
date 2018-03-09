/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Auto/CL_AR.h>

CL_AR::CL_AR() : m_closeGrabber(false), m_moveToTape(EVT_TAPE), m_moveGrabberUp(true), m_openGrabber(true)
{
	AddSequential(m_closeGrabber);
	AddParallel(m_moveToTape);
	AddSequential(m_moveGrabberUp);
	AddSequential(m_openGrabber);
}
