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
//#include "../MoveToTarget.h"
#include "../MoveGrabber.h"
#include "../MoveTime.h"
#include "../SpinGrabberTime.h"

class SecondCube : public frc::CommandGroup {
public:
	SecondCube(bool left);

private:
	MoveTime m_moveBack;
	MoveGrabber m_moveGrabberDown;
	TurnAngle m_turnRightAngle;
	SpinGrabberTime m_spinGrabberLong;
	MoveTime m_moveForward;
	MoveTime m_moveBackLong;
	TurnAngle m_turnRightAngle2;
	MoveTime m_moveForwardShort;
	SpinGrabberTime m_spinGrabber2;
	MoveGrabber m_moveGrabberUp2;
	SetGrabber m_closeGrabber2;
	SetGrabber m_openGrabber2;
};

