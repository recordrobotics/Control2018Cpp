/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <cmath>

#include "../Utils/Logger.h"

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
	if(!Network::seesCube()) {
		Robot::drivetrain.drive(0.0, 0.0);
		return;
	}

	double x = Network::getCameraX();

	double sens = 1.0;
	double d_sens = 1.0;
	double max = 0.3;
	double v = 0.0;
	double e = 0.001;

	if(x > e || x < -e)
		v = x * sens + d_sens * Robot::drivetrain.getLeft() * x / fabs(x);

	if(v > max)
		v = max;
	else if(v < -max)
		v = -max;

	Logger::log("v1: %f, v2: %f", x * sens, d_sens * Robot::drivetrain.getLeft() * x / fabs(x));

	Robot::drivetrain.drive(-v, v);
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
