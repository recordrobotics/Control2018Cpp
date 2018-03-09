/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/CommandGroup.h>

#include "../SetGrabber.h"
#include "../TurnAngle.h"
#include "../MoveToTarget.h"
#include "../MoveGrabber.h"

class BL_BR : public frc::CommandGroup {
public:
	BL_BR(bool left);

private:
	SetGrabber m_closeGrabber;
	TurnAngle m_turnAngle;
	MoveToTarget m_moveToTape;
	MoveGrabber m_moveGrabberUp;
	SetGrabber m_openGrabber;
};

