/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/CommandGroup.h>

#include "A_COneCube.h"
#include "SecondCube.h"

class A_CTwoCube : public frc::CommandGroup {
public:
	A_CTwoCube(bool left);
private:
	A_COneCube m_oneCube;
	SecondCube m_secondCube;
};

