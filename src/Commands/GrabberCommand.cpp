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

GrabberCommand::GrabberCommand() : /*last_push_toggle(false),*/ last_grab_toggle(false) {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::grabber);
}

// Called just before this Command runs the first time
void GrabberCommand::Initialize() {
	Robot::grabber.stopMotors();
	Robot::grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kOff);
	//Robot::grabber.setPushSolenoid(frc::DoubleSolenoid::Value::kOff);
}

// Called repeatedly when this Command is scheduled to run
void GrabberCommand::Execute() {
	double maxGrabberMotorSpeed = 1.0;

	/*bool left_motor_left = false;
	bool left_motor_right = false;
	bool right_motor_left = false;
	bool right_motor_right = false;*/

	int left_pov = Robot::oi.getLeftJoystick().GetPOV(0);
	//int right_pov = Robot::oi.getRightJoystick().GetPOV(0);
	//Logger::log("pov: %d", left_pov);

	double left = 0.0, right = 0.0;

	if(left_pov == 0) {
		left = maxGrabberMotorSpeed;
		right = -maxGrabberMotorSpeed;
	}
	else if(left_pov == 180) {
		left = -maxGrabberMotorSpeed;
		right = maxGrabberMotorSpeed;
	}
	else if(left_pov  == 90) {
		left = maxGrabberMotorSpeed;
		right = maxGrabberMotorSpeed;
	}
	else if(left_pov  == 270) {
		left = -maxGrabberMotorSpeed;
		right = -maxGrabberMotorSpeed;
	}

//	if(left_pov != -1 && (left_pov >= 315 || left_pov <= 45)) {
//		left = maxGrabberMotorSpeed;
//		right = -maxGrabberMotorSpeed;
//	}
//	else if(left_pov >= 135 && left_pov <= 225) {
//		left = -maxGrabberMotorSpeed;
//		right = maxGrabberMotorSpeed;
//	}

	/*if(right_pov >= 45 && right_pov <= 135)
		right = -maxGrabberMotorSpeed;
	else if(right_pov >= 225 && right_pov <= 315)
		right = maxGrabberMotorSpeed;*/

	//double right = maxGrabberMotorSpeed * Robot::oi.getRightJoystick().GetZ();

	//bool open = Robot::oi.getRightJoystick().GetRawButton(opengrabberbuttonPort);
	//bool close = Robot::oi.getLeftJoystick().GetRawButton(closegrabberbuttonPort);

	bool extend_toggle = Robot::oi.getLeftJoystick().GetRawButton(toggleextendbuttonPort);
	bool grab_toggle = Robot::oi.getRightJoystick().GetRawButton(togglegrabberbuttonPort);

	//Logger::log("Push joystick: %d", push_toggle);

	if(extend_toggle && !last_extend_toggle) {
		Robot::grabber.toggleExtendSolenoid();

		/*if(v) {
			spin_push = 1;
			Robot::grabber.setMotors(-maxGrabberMotorSpeed, -maxGrabberMotorSpeed);
		}
		else {

		}*/
	}

	if(grab_toggle && !last_grab_toggle)
		Robot::grabber.toggleGrabSolenoid();

	last_extend_toggle = extend_toggle;
	last_grab_toggle = grab_toggle;

	//Logger::log("grabber: %f %f", left, right);
	Robot::grabber.setMotors(left, right);

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
	Robot::grabber.stopMotors();
	Robot::grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kOff);
	//Robot::grabber.setPushSolenoid(frc::DoubleSolenoid::Value::kOff);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GrabberCommand::Interrupted() {
	Robot::grabber.stopMotors();
	Robot::grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kOff);
	//Robot::grabber.setPushSolenoid(frc::DoubleSolenoid::Value::kOff);
}
