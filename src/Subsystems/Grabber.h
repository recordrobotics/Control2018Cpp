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

	frc::DoubleSolenoid grab_solenoid, push_solenoid;
	frc::DoubleSolenoid::Value grab_solenoid_value, push_solenoid_value;

	GrabberCommand default_command;

	RangeFinder rangeFinder;

public:
	Grabber();

	void setGrabSolenoid(frc::DoubleSolenoid::Value v);
	void toggleGrabSolenoid();

	void setPushSolenoid(frc::DoubleSolenoid::Value v);
	void togglePushSolenoid();

	void succ(double speed);
	void adjust(double speed, bool direction);

	void set(double left, double right);
	void stop();

	inline double getFinderDistance() const { return rangeFinder.getDistance(); }

	void InitDefaultCommand() override;
};
