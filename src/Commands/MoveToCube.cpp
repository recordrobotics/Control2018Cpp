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

void MoveToCube::setState(E_AUTO_STATE s) {
	state = s;
	lastStateChangeTime = MsTimer::getMs();
}

MoveToCube::MoveToCube() {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::drivetrain);
	setState(EAS_IDLE);
}

// Called just before this Command runs the first time
void MoveToCube::Initialize() {
	Robot::grabber.setPushSolenoid(frc::DoubleSolenoid::Value::kForward);
	Robot::grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kReverse);
	Robot::drivetrain.stop();

	setState(EAS_MOVE);
	Network::sendMode(ESM_CUBE, 10);
}

// Called repeatedly when this Command is scheduled to run
void MoveToCube::Execute() {
	if(state == EAS_IDLE || (!Network::leftSeesCube() && !Network::rightSeesCube())) {
		Robot::drivetrain.drive(0.0, 0.0);
		return;
	}

	double x = 0.0;
	double y = 0.0;

	if(Network::leftSeesCube()) {
		if(Network::rightSeesCube()) {
			x = 0.5 * (Network::getLeftCameraX() + Network::getRightCameraX());
			y = 0.5 * (Network::getLeftCameraY() + Network::getRightCameraY());
		}
		else {
			x = Network::getLeftCameraX() - 0.06;
			y = Network::getLeftCameraY();
		}
	}
	else {
		x = Network::getRightCameraX() + 0.06;
		y = Network::getRightCameraY();
	}

	double forward = 0.2;

	if(y < -0.85 && state == EAS_MOVE) {
		setState(EAS_PREGRAB);
		Robot::drivetrain.drive(-forward, -forward);
	}
	else if(state == EAS_PREGRAB && (MsTimer::getMs() - lastStateChangeTime) > PREGRAB_MOVE_TIME) {
		setState(EAS_GRAB);
		Robot::grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kForward);
		Robot::drivetrain.stop();
		Network::sendMode(ESM_TAPE, 10);
	}
	else if(state == EAS_MOVE) {
		double sens = 0.4;
		double d_sens = 0.2;
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
}

// Make this return true when this Command no longer needs to run execute()
bool MoveToCube::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void MoveToCube::End() {
	Robot::grabber.setPushSolenoid(frc::DoubleSolenoid::Value::kOff);
	Robot::grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kOff);
	Robot::drivetrain.stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveToCube::Interrupted() {
	Robot::grabber.setPushSolenoid(frc::DoubleSolenoid::Value::kOff);
	Robot::grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kOff);
	Robot::drivetrain.stop();
}
