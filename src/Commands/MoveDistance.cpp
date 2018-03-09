/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "MoveDistance.h"

#include "../Robot.h"

#define sign(x)  ((x) < 0.0 ? -1.0 : ((x) == 0.0 ? 0.0 : 1.0))

MoveDistance::MoveDistance(double d) : m_d(d), finished(false), start_ang(0.0) {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::drivetrain);
}

// Called just before this Command runs the first time
void MoveDistance::Initialize() {
	Robot::drivetrain.stop();

	start_ang = Robot::drivetrain.getAngle();

	finished = false;
}

// Called repeatedly when this Command is scheduled to run
void MoveDistance::Execute() {
	// How close you have to be to be considered there
	double thresh = 0.5;
	// Proportional term for distance
	double d_p = 0.01;
	// Derivative term for distance
	double d_d = 0.01;
	// Maximum distance factor
	double d_m = 0.5;
	// Proportional term for angle
	double a_p = 0.01;
	// Derivative term for angle
	double a_d = 0.01;
	// Maximum angle factor
	double a_m = 0.2;

	double left_d = Robot::drivetrain.getLeftDistance();
	double right_d = Robot::drivetrain.getRightDistance();
	double left_r = Robot::drivetrain.getRightRate();
	double right_r = Robot::drivetrain.getLeftRate();
	double ang = Robot::drivetrain.getAngle();
	double ang_r = Robot::drivetrain.getAngleRate();

	// Linear distance factor
	double d_diff = m_d - 0.5 * (left_d + right_d);

	if(fabs(d_diff) < thresh) {
		finished = true;
		return;
	}

	double left = fabs(d_diff * d_p) - fabs(0.5 * (left_r + right_r) * d_d);

	if(left < 0.0)
		left = 0.0;
	else if(left > d_m)
		left = d_m;

	left *= sign(d_diff);

	double right = left;

	// Angle Factor
	double ang_f = fabs((ang - start_ang) * a_p) - fabs(ang_r * a_d);
	if(ang_f < 0.0)
		ang_f = 0.0;
	else if(ang_f > a_m)
		ang_f = a_m;

	ang_f *= sign(ang - start_ang);

	right += ang_f;
	left -= ang_f;

	Robot::drivetrain.drive(left, right);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveDistance::IsFinished() {
	return finished;
}

// Called once after isFinished returns true
void MoveDistance::End() {
	Robot::drivetrain.stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveDistance::Interrupted() {
	Robot::drivetrain.stop();
}
