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

	double forward = 0.2;
	double sens = 0.4;
	double d_sens = 1.8;
	double max = 0.17;

	double v1 = x * sens;
	double v2 = d_sens * Robot::drivetrain.getLeft() * fabs(x);
	double vb = v1 + v2;

	if(v1 > 0.0 && vb < 0.0)
		vb = 0.0;
	else if(v1 < 0.0 && vb > 0.0)
		vb = 0.0;


	if(vb > max)
		vb = max;
	else if(vb < -max)
		vb = -max;

	Logger::log("v1: %f, v2: %f", v1, v2);

	Robot::drivetrain.drive(-forward - vb, -forward + vb);
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
