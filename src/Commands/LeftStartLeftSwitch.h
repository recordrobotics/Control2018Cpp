/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/CommandGroup.h>

#include "MoveGrabber.h"
#include "SmoothMove.h"
#include "SetGrabber.h"

class LeftStartLeftSwitch : public frc::CommandGroup {
public:
	LeftStartLeftSwitch();
private:
	SetGrabber m_openGrabber;
	SetGrabber m_closeGrabber;
	MoveGrabber m_moveGrabberUp;
	SmoothMove m_smoothMove;
};

