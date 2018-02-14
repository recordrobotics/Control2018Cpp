/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "MoveToCube.h"

#include "../Robot.h"

#include "Utils/Network.h"

MoveToCube::MoveToCube() {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::drivetrain);
}

// Called just before this Command runs the first time
void MoveToCube::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void MoveToCube::Execute() {
	double x = Network::getCameraX();

	double sens = 0.3;
	double max = 0.2;
	double v = x * sens;

	if(v > max)
		v = max;
	else if(v < -max)
		v = -max;

	Robot::drivetrain.drive(v, -v);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveToCube::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void MoveToCube::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveToCube::Interrupted() {

}
