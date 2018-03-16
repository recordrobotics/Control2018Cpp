/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/CommandGroup.h>

#include "../SetGrabber.h"
//#include "../MoveToTarget.h"
#include "../MoveGrabber.h"
#include "../MoveTime.h"
#include "../SpinGrabberTime.h"

class A_COneCube : public frc::CommandGroup {
public:
	A_COneCube();

private:
	SetGrabber m_closeGrabber;
	//MoveToTarget m_moveToTape;
	MoveTime m_moveToTapeSimple;
	MoveGrabber m_moveGrabberUp;
	SpinGrabberTime m_spinGrabber;
	SetGrabber m_openGrabber;
};

