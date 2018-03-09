/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>

enum E_TURN_ANGLE {
	ETA_FORWARD = 0,
	ETA_BACKWARD,
	ETA_SPOT,
	ETA_COUNT
};

class TurnAngle : public frc::Command {
public:
	TurnAngle(double ang, E_TURN_ANGLE t);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	E_TURN_ANGLE type;
	double m_ang;
	double start_ang;
	double end_ang;
	bool finished;
};

