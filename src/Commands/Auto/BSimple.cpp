/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Auto/BSimple.h>

#define ANGLE     30.0
#define DISTANCE  6.0

BSimple::BSimple(bool left) : m_turnAngle(left ? -ANGLE: ANGLE, 0.0, ETA_FORWARD, 1000), m_moveDistance(DISTANCE),
							  m_turnAngleSimple(left ? 0.0 : 0.5, left ? 0.5 : 0.0, 300)
{
	AddSequential(&m_turnAngle);
	//AddSequential(&m_turnAngleSimple);
	AddSequential(&m_moveDistance);
}
