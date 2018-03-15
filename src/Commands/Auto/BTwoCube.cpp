/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Auto/BTwoCube.h>

BTwoCube::BTwoCube(bool left) : m_oneCube(left), m_secondCube(left)
{
	AddSequential(&m_oneCube);
	AddSequential(&m_secondCube);
}
