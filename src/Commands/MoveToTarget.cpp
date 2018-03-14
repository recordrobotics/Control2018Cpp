/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/MoveToTarget.h>
#include <cmath>

#include "../Utils/Logger.h"

#include "../Robot.h"

void MoveToTarget::setState(E_AUTO_STATE s) {
	state = s;
	lastStateChangeTime = MsTimer::getMs();
}

MoveToTarget::MoveToTarget(E_VISION_TARGET t) : target(t), finished(false) {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::drivetrain);
	setState(EAS_IDLE);
}

// Called just before this Command runs the first time
void MoveToTarget::Initialize() {
	Robot::drivetrain.stop();

	setState(EAS_MOVE);

	if(target == EVT_CUBE)
		Network::sendTarget(EVT_CUBE, 10);
	else {
		Network::sendTarget(EVT_TAPE, 10);
		Robot::drivetrain.setLights(true);
	}

	finished = false;
}

// Called repeatedly when this Command is scheduled to run
void MoveToTarget::Execute() {
	bool seesleft = Network::leftSeesTarget();
	bool seesright = Network::rightSeesTarget();

	if(state == EAS_IDLE || (!seesleft && !seesright)) {
		Robot::drivetrain.stop();
		if((MsTimer::getMs() - lastStateChangeTime) > TIMEOUT_TIME)
			finished = true;
		return;
	}

	double x = 0.0;
	double y = 0.0;

	if(Network::leftSeesTarget()) {
		if(Network::rightSeesTarget()) {
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

	if(state == EAS_COAST && (MsTimer::getMs() - lastStateChangeTime) > COAST_MOVE_TIME) {
		setState(EAS_IDLE);
		Robot::drivetrain.stop();
		finished = true;
	}
	else if(state == EAS_MOVE) {
		if(target == EVT_CUBE && y < -0.85) {
			setState(EAS_COAST);
			Robot::drivetrain.drive(-forward, -forward);
			return;
		}
		else if(target == EVT_TAPE) {
			if(seesleft && seesright) {
				if(fabs(Network::getRightCameraX() - Network::getLeftCameraX()) > 0.5) {
					setState(EAS_COAST);
					Robot::drivetrain.drive(-forward, -forward);
					return;
				}
			}
			else if(y < -0.5) {
				setState(EAS_COAST);
				Robot::drivetrain.drive(-forward, -forward);
				return;
			}
		}

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
bool MoveToTarget::IsFinished() {
	return finished;
}

// Called once after isFinished returns true
void MoveToTarget::End() {
	Robot::drivetrain.stop();
	Robot::drivetrain.setLights(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveToTarget::Interrupted() {
	Robot::drivetrain.stop();
	Robot::drivetrain.setLights(false);
}
