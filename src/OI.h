/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Joystick.h>

class OI {
public:
	OI();
	inline const frc::Joystick& getLeftJoystick() const { return left_joystick; };
	inline const frc::Joystick& getRightJoystick() const { return right_joystick; }
private:
	frc::Joystick left_joystick;
	frc::Joystick right_joystick;
};


