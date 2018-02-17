/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "GrabberCommand.h"

#include "../Robot.h"

#include "../RobotMap.h"

GrabberCommand::GrabberCommand() {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::grabber);
}

// Called just before this Command runs the first time
void GrabberCommand::Initialize() {
	Robot::grabber.stop();
}

// Called repeatedly when this Command is scheduled to run
void GrabberCommand::Execute() {
	double left = Robot::oi.getLeftJoystick().GetRawAxis(grabber_axis);
	double right = Robot::oi.getRightJoystick().GetRawAxis(grabber_axis);
	Robot::grabber.set(left, right);
}

// Make this return true when this Command no longer needs to run execute()
bool GrabberCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void GrabberCommand::End() {
	Robot::grabber.stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GrabberCommand::Interrupted() {
	Robot::grabber.stop();
}
