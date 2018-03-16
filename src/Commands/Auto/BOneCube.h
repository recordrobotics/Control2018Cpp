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

class BOneCube : public frc::CommandGroup {
public:
	BOneCube(bool left);

private:
	SetGrabber m_closeGrabber;
	TurnAngle m_turnAngle;
	MoveTime m_turnAngleSimple;
	//MoveToTarget m_moveToTape;
	MoveTime m_moveToTapeSimple;
	MoveGrabber m_moveGrabberUp;
	TurnAngle m_turnAngle2;
	MoveTime m_turnAngleSimple2;
	SetGrabber m_openGrabber;
	SpinGrabberTime m_spinGrabber;
};

