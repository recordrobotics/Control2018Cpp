/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SetGrabber.h"

#include "../Robot.h"

#include "../Utils/Logger.h"

SetGrabber::SetGrabber(bool open) : m_open(open) {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::grabber);
}

// Called just before this Command runs the first time
void SetGrabber::Initialize() {
	if(m_open)
		Robot::grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kReverse);
	else
		Robot::grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kForward);
}

// Called repeatedly when this Command is scheduled to run
void SetGrabber::Execute() {
	if(m_open)
		Robot::grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kReverse);
	else
		Robot::grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kForward);

	Logger::log("SetGrabber execute");
}

// Make this return true when this Command no longer needs to run execute()
bool SetGrabber::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void SetGrabber::End() {
	//Robot::grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kOff);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetGrabber::Interrupted() {
	//Robot::grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kOff);
}
