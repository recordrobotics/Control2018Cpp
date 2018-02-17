/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DrivewithJoystick.h"

#include "../Robot.h"
#include "../Utils/Logger.h"

DrivewithJoystick::DrivewithJoystick() {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::drivetrain);
}

// Called just before this Command runs the first time
void DrivewithJoystick::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DrivewithJoystick::Execute() {
	frc::Joystick = OI::getJoystick();
	double forward = j.getRawAxis(forward_axis);
	double turn = j.getRawAxis(turn_axis);
	Robot::drivetrain.driveCheesy(forward, turn);
	Logger::log(){printf("%f %f\n", forward, turn);};
}

// Make this return true when this Command no longer needs to run execute()
bool DrivewithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DrivewithJoystick::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DrivewithJoystick::Interrupted() {

}
