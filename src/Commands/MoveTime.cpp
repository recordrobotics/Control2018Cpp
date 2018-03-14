/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "MoveTime.h"

#include "../Robot.h"

MoveTime::MoveTime(double left, double right, ms_t time) : m_left(left), m_right(right), m_time(time), startTime(0) {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::drivetrain);
}

// Called just before this Command runs the first time
void MoveTime::Initialize() {
	startTime = MsTimer::getMs();

	Robot::drivetrain.drive(m_left, m_right);

	Logger::log("MoveTime initialized");
}

// Called repeatedly when this Command is scheduled to run
void MoveTime::Execute() {
	Robot::drivetrain.drive(m_left, m_right);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveTime::IsFinished() {
	return (MsTimer::getMs() - startTime) > m_time;
}

// Called once after isFinished returns true
void MoveTime::End() {
	Robot::drivetrain.stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveTime::Interrupted() {
	Robot::drivetrain.stop();
}
