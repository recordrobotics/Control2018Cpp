/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Auto/BSimple.h>

#define ANGLE     30.0
#define DISTANCE  6.0

BSimple::BSimple() : m_turnAngle(ANGLE, ETA_FORWARD), m_moveDistance(DISTANCE) {
	AddSequential(m_turnAngle);
	AddSequential(m_moveDistance);
}
