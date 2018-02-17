/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Subsystem.h>
#include <Spark.h>
#include <VictorSP.h>
#include <DigitalInput.h>
#include "../Commands/ClimberCommand.h"

class Climber : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	DigitalInput bottom_switch, top_switch;

	frc::VictorSP motor;

	ClimberCommand default_command;

public:
	Climber();
	void InitDefaultCommand() override;

	bool getBottomSwitch() const { return bottom_switch.Get(); }
	bool getTopSwitch() const { return top_switch.Get(); }

	void setMotor(double v) { motor.Set(v); }
	void stopMotor() { motor.Set(0.0); }
};

