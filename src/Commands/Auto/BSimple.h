/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/CommandGroup.h>

#include "../TurnAngle.h"
#include "../MoveDistance.h"
#include "../MoveTime.h"

class BSimple : public frc::CommandGroup {
public:
	BSimple(bool left);

private:
	TurnAngle m_turnAngle;
	MoveTime m_turnAngleSimple;
	MoveDistance m_moveDistance;
};

