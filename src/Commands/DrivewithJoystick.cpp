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

#include <Joystick.h>

DrivewithJoystick::DrivewithJoystick() {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::drivetrain);
}

// Called just before this Command runs the first time
void DrivewithJoystick::Initialize() {
	Robot::drivetrain.stop();
}

// Called repeatedly when this Command is scheduled to run
void DrivewithJoystick::Execute() {
	double left = Robot::oi.getLeftJoystick().GetRawAxis(forward_axis);
	double right = Robot::oi.getRightJoystick().GetRawAxis(forward_axis);
	Robot::drivetrain.drive(left, right);
	//Logger::log(){printf("%f %f\n", forward, turn);};
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
