/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "LeftStartLeftSwitch.h"

LeftStartLeftSwitch::LeftStartLeftSwitch() : m_openGrabber(true), m_closeGrabber(false), m_moveGrabberUp(0.7, true),
											 m_smoothMove("leftstartleftswitch.txt", "/log/constants.txt", 0.01, 5.0, 10.0, 20.0)
{
	AddParallel(&m_openGrabber);
	AddSequential(&m_smoothMove);
	AddSequential(&m_closeGrabber);
	AddSequential(&m_moveGrabberUp);
}
