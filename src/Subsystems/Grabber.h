#pragma once

class Grabber : frc::Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	frc::Spark left_motor, right_motor;

public:
	Grabber();
	~Grabber();

	void succ(double speed);
	void adjust(double speed);

};