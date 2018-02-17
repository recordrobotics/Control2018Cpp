#pragma once

#include <Spark.h>
#include <Commands/Subsystem.h>

class Grabber : public frc::Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	frc::Spark left_motor, right_motor;

public:
	Grabber();

	void succ(double speed);
	void adjust(double speed, bool direction);

	void set(double left, double right);
	void stop();
};
