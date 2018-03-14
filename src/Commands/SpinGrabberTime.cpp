/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SpinGrabberTime.h"

#include "../Robot.h"

SpinGrabberTime::SpinGrabberTime(double left, double right, ms_t time) : m_left(left), m_right(right), m_time(time), startTime(0) {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::grabber);
}

// Called just before this Command runs the first time
void SpinGrabberTime::Initialize() {
	startTime = MsTimer::getMs();

	Robot::grabber.setMotors(m_left, m_right);

	Logger::log("SpinGrabber init");
}

// Called repeatedly when this Command is scheduled to run
void SpinGrabberTime::Execute() {
	Robot::grabber.setMotors(m_left, m_right);
	Logger::log("Spingrabber: %f %f", m_left, m_right);

}

// Make this return true when this Command no longer needs to run execute()
bool SpinGrabberTime::IsFinished() {
	return ((MsTimer::getMs() - startTime) > m_time);
}

// Called once after isFinished returns true
void SpinGrabberTime::End() {
	Robot::grabber.stopMotors();

	Logger::log("SpinGrabber end");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpinGrabberTime::Interrupted() {
	Robot::grabber.stopMotors();
}
