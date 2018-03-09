/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "TurnAngle.h"

#include "../Robot.h"

TurnAngle::TurnAngle(double ang, E_TURN_ANGLE t) : type(t), m_ang(ang), start_ang(0.0), end_ang(ang), finished(false) {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot.drivetrain);
}

// Called just before this Command runs the first time
void TurnAngle::Initialize() {
	Robot::drivetrain.stop();

	start_ang = Robot.drivetrain.getAngle();
	end_ang = start_ang + ang;

	finished = false;
}

// Called repeatedly when this Command is scheduled to run
void TurnAngle::Execute() {
	double ang = Robot::drivetrain.getAngle();
	double ang_r = Robot::drivetain.getAngleRate();

	double a_p = 0.01;
	double a_d = 0.005;
	double a_m = 0.2;
	double thresh = 4.0;

	if(fabs(ang - end_ang) < thresh) {
		finished = true;
		return;
	}

	double ang_f = fabs((ang - end_ang) * a_p) - fabs(ang_r * a_d);
	if(ang_f < 0.0)
		ang_f = 0.0;
	else if(ang_f > a_m)
		ang_f = a_m;

	ang_f *= sign(ang - end_ang);

	double left = 0.0;
	double right = 0.0;

	if(type == ETA_FORWARD) {
		if(ang_f > 0.0)
			right = ang_f;
		else
			left = -ang_f;
	}
	else if(type == ETA_BACKWARD) {
		if(ang_f > 0.0)
			left = -ang_f;
		else
			right = ang_f;
	}
	else {
		right = ang_f;
		left = -ang_f;
	}

	Robot::drivetrain.drive(left, right);
}

// Make this return true when this Command no longer needs to run execute()
bool TurnAngle::IsFinished() {
	return finished;
}

// Called once after isFinished returns true
void TurnAngle::End() {
	Robot::drivetrain.stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnAngle::Interrupted() {
	Robot::drivetrain.stop();
}
