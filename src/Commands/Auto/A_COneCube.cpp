/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Auto/A_COneCube.h>

A_COneCube::A_COneCube() : m_closeGrabber(false), /*m_moveToTape(EVT_TAPE),*/ m_moveToTapeSimple(0.4, 0.4, 3000), m_moveGrabberUp(1.0, true, 3000),
						   m_spinGrabber(1.0, -1.0, 2000), m_openGrabber(true)
{
	AddSequential(&m_closeGrabber);
	//AddParallel(&m_moveToTape);
	AddParallel(&m_moveToTapeSimple);
	AddSequential(&m_moveGrabberUp);
	AddSequential(&m_openGrabber);
	AddSequential(&m_spinGrabber);
}
