/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>

#include "../Utils/MsTimer.h"

class SpinGrabberTime : public frc::Command {
public:
	SpinGrabberTime(double left, double right, ms_t time);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	double m_left;
	double m_right;
	ms_t m_time;
	ms_t startTime;
};

