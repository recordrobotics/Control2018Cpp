/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>

#include <Utils/MsTimer.h>

enum E_AUTO_STATE {
	EAS_MOVE = 0,
	EAS_PREGRAB,
	EAS_GRAB,
	EAS_IDLE,
	EAS_COUNT
};

#define PREGRAB_MOVE_TIME  800

class MoveToCube : public frc::Command {
public:
	MoveToCube();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	E_AUTO_STATE state;
	ms_t lastStateChangeTime;

	void setState(E_AUTO_STATE s);
};

