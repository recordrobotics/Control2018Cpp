/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>

#include <Utils/MsTimer.h>

#include "../Utils/Network.h"

enum E_AUTO_STATE {
	EAS_MOVE = 0,
	EAS_COAST,
	EAS_IDLE,
	EAS_COUNT
};

#define COAST_MOVE_TIME  800
#define TIMEOUT_TIME     1000

class MoveToTarget : public frc::Command {
public:
	MoveToTarget(E_VISION_TARGET t);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	E_VISION_TARGET target;
	E_AUTO_STATE state;
	ms_t lastStateChangeTime;
	bool finished;

	void setState(E_AUTO_STATE s);
};

