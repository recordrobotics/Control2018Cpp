/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Spark.h>
#include <Commands/Subsystem.h>
#include "../Commands/DrivewithJoystick.h"

class Drivetrain : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	frc::Spark left_motor1, left_motor2, right_motor1, right_motor2;

	double m_left, m_right;

	DrivewithJoystick default_command;

public:
	Drivetrain();
	~Drivetrain();
	void InitDefaultCommand() override;
	void drive(double left, double right);

	double getLeft() { return m_left; }
	double getRight() { return m_right; }
};

