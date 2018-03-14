/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ClimberCommand.h"
#include "../Robot.h"
#include "../RobotMap.h"

#include "../Utils/Logger.h"

ClimberCommand::ClimberCommand() {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::climber);
}

// Called just before this Command runs the first time
void ClimberCommand::Initialize() {
	Robot::climber.stopMotor();
}

// Called repeatedly when this Command is scheduled to run
void ClimberCommand::Execute() {
	bool butt = Robot::oi.getRightJoystick().GetRawButton(climberbuttonPort);
	bool butt_v2 = Robot::oi.getLeftJoystick().GetRawButton(climberbuttonPort);

	double climberMoveSpeed = 1.0;
	double move = climberMoveSpeed * (double)((int)butt - (int)butt_v2);

	if(move < 0.0 && !Robot::climber.getBottomSwitch())
		move = 0.0;
	if(move > 0.0 && !Robot::climber.getTopSwitch())
		move = 0.0;

	Logger::log("Climb: %f  bottom switch: %d  top switch: %d", move, Robot::climber.getBottomSwitch(), Robot::climber.getTopSwitch());

	Robot::climber.setMotor(move);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ClimberCommand::End() {
	Robot::climber.stopMotor();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberCommand::Interrupted() {
	Robot::climber.stopMotor();
}
