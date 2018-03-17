/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/MoveGrabber.h>

#include "../Robot.h"

MoveGrabber::MoveGrabber(double v, bool dir, ms_t timeout) : m_dir(dir), startTime(0), m_timeout(timeout) {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::climber);

	double vel_abs = fabs(v);
	m_vel = m_dir ? vel_abs : -vel_abs;
}

// Called just before this Command runs the first time
void MoveGrabber::Initialize() {
	startTime = MsTimer::getMs();

	Robot::climber.setMotor(m_vel);

	Logger::log("MoveGrabber init");
}

// Called repeatedly when this Command is scheduled to run
void MoveGrabber::Execute() {
	Robot::climber.setMotor(m_vel);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveGrabber::IsFinished() {
	if((MsTimer::getMs() - startTime) > m_timeout)
		return true;
	else if(m_dir)
		return !Robot::climber.getTopSwitch();
	else
		return !Robot::climber.getBottomSwitch();
//	return false;
}

// Called once after isFinished returns true
void MoveGrabber::End() {
	Robot::climber.stopMotor();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveGrabber::Interrupted() {
	Robot::climber.stopMotor();
}
