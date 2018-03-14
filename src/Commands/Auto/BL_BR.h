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
#include "../MoveTime.h"
#include "../SpinGrabberTime.h"

class BL_BR : public frc::CommandGroup {
public:
	BL_BR(bool left);

private:
	SetGrabber m_closeGrabber;
	TurnAngle m_turnAngle;
	MoveTime m_turnAngleSimple;
	MoveTime m_moveToTapeSimple;
	MoveGrabber m_moveGrabberUp;
	SetGrabber m_openGrabber;
	MoveToTarget m_moveToTape;
	SpinGrabberTime m_spinGrabber;
	MoveTime m_turnAngleSimple2;
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
	TurnAngle m_turnAngle2;
};

