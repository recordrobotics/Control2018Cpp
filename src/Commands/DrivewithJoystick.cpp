/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DrivewithJoystick.h"

#include "../Robot.h"
#include "../Utils/Logger.h"
#include "../RobotMap.h"
#include "../Utils/Logger.h"

#include <Joystick.h>

DrivewithJoystick::DrivewithJoystick() {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::drivetrain);
}

// Called just before this Command runs the first time
void DrivewithJoystick::Initialize() {
	Robot::drivetrain.stop();
}

double DrivewithJoystick::smooth(double x) {
	return (x * x * x);
}

// Called repeatedly when this Command is scheduled to run
void DrivewithJoystick::Execute() {
	/*double left = Robot::oi.getLeftJoystick().GetY();
	double right = Robot::oi.getRightJoystick().GetY();

	left = smooth(left);
	right = smooth(right);

	if(left < 0.0 && right > 0.0) {
		left = -(-left + right) * 0.5;
		right = (-left + right) * 0.5;
	}
	else if(left > 0.0 && right < 0.0) {
		left = (left - right) * 0.5;
		right = -(left - right) * 0.5;
	}*/

	Logger::log("Joy: %f %f", Robot::oi.getLeftJoystick().GetY(), Robot::oi.getRightJoystick().GetY());

	double forward = 0.5 * (Robot::oi.getLeftJoystick().GetY() + Robot::oi.getRightJoystick().GetY());
	double turn = 0.5 * (Robot::oi.getLeftJoystick().GetZ() + Robot::oi.getRightJoystick().GetZ());

	Logger::log("forward: %f turn: %f", forward, turn);

	forward = smooth(forward);
	turn = smooth(turn);

	Robot::drivetrain.driveCheesy(forward, turn, -0.5);
	//Logger::log("driving: %f %f", left, right);
}

// Make this return true when this Command no longer needs to run execute()
bool DrivewithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DrivewithJoystick::End() {
	Robot::drivetrain.stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DrivewithJoystick::Interrupted() {
	Robot::drivetrain.stop();
}
