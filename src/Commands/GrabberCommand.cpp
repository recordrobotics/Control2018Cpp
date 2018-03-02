/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "GrabberCommand.h"
#include "../Robot.h"

#include "../RobotMap.h"

#include "../Utils/Logger.h"

GrabberCommand::GrabberCommand() : last_push_toggle(false), last_grab_toggle(false) {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::grabber);
}

// Called just before this Command runs the first time
void GrabberCommand::Initialize() {
	Robot::grabber.stop();
	Robot::grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kOff);
	Robot::grabber.setPushSolenoid(frc::DoubleSolenoid::Value::kOff);
}

// Called repeatedly when this Command is scheduled to run
void GrabberCommand::Execute() {
	double maxGrabberMotorSpeed = 0.5;

	bool left_motor_left = false;
	bool left_motor_right = false;
	bool right_motor_left = false;
	bool right_motor_right = false;

	Logger::log("pov: %d", Robot::oi.getLeftJoystick().GetPOV(0));

	double left = 0.0, right = 0.0;

	if(left_motor_left && !left_motor_right)
		left = maxGrabberMotorSpeed;
	else if(left_motor_right && !left_motor_left)
		left = maxGrabberMotorSpeed;

	if(right_motor_left && !right_motor_right)
		right = maxGrabberMotorSpeed;
	else if(right_motor_right && !right_motor_left)
		right = maxGrabberMotorSpeed;

	//double right = maxGrabberMotorSpeed * Robot::oi.getRightJoystick().GetZ();

	//bool open = Robot::oi.getRightJoystick().GetRawButton(opengrabberbuttonPort);
	//bool close = Robot::oi.getLeftJoystick().GetRawButton(closegrabberbuttonPort);

	bool push_toggle = Robot::oi.getLeftJoystick().GetRawButton(togglegrabberbuttonPort);
	bool grab_toggle = Robot::oi.getRightJoystick().GetRawButton(togglegrabberbuttonPort);

	Logger::log("Push joystick: %d", push_toggle);

	if(push_toggle && !last_push_toggle)
		Robot::grabber.togglePushSolenoid();

	if(grab_toggle && !last_grab_toggle)
		Robot::grabber.toggleGrabSolenoid();

	last_push_toggle = push_toggle;
	last_grab_toggle = grab_toggle;

	//Logger::log("grabber: %f %f", left, right);
	Robot::grabber.set(left, right);

	/*if(open && !close)
		Robot::grabber.setSolenoid(frc::DoubleSolenoid::Value::kForward);
	else if(close && !open)
		Robot::grabber.setSolenoid(frc::DoubleSolenoid::Value::kReverse);
	else
		Robot::grabber.setSolenoid(frc::DoubleSolenoid::Value::kOff);*/
}

// Make this return true when this Command no longer needs to run execute()
bool GrabberCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void GrabberCommand::End() {
	Robot::grabber.stop();
	Robot::grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kOff);
	Robot::grabber.setPushSolenoid(frc::DoubleSolenoid::Value::kOff);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GrabberCommand::Interrupted() {
	Robot::grabber.stop();
	Robot::grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kOff);
	Robot::grabber.setPushSolenoid(frc::DoubleSolenoid::Value::kOff);
}
