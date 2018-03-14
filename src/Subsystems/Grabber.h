#pragma once

#include <Spark.h>
#include <Commands/Subsystem.h>
#include <Encoder.h>
#include <DoubleSolenoid.h>

#include "../Commands/GrabberCommand.h"
#include "../RangeFinder.h"

class Grabber : public frc::Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	frc::Spark left_motor, right_motor;

	frc::DoubleSolenoid grab_solenoid, extend_solenoid;
	frc::DoubleSolenoid::Value grab_solenoid_value, extend_solenoid_value;

	GrabberCommand default_command;

	//RangeFinder rangeFinder;

public:
	Grabber();

	void setGrabSolenoid(frc::DoubleSolenoid::Value v);
	void toggleGrabSolenoid();

	void setExtendSolenoid(frc::DoubleSolenoid::Value v);
	void toggleExtendSolenoid();

	void succ(double speed);
	void adjust(double speed, bool direction);

	void setMotors(double left, double right);
	void stopMotors();

	//inline double getFinderDistance() const { return rangeFinder.getDistance(); }

	void InitDefaultCommand() override;
};
