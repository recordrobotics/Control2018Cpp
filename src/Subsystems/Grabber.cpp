#include "Grabber.h"

#include "../RobotMap.h"

Grabber::Grabber() : Subsystem("Grabber"), left_motor(leftgrabberPort), right_motor(rightgrabberPort)
{

}

void Grabber::succ(double speed)
{
	set(speed, -speed);
}

void Grabber::adjust(double speed, bool direction)
{
	if (direction)
	{
		set(speed, speed);
	}
	else
	{
		set(-speed, -speed);
	}
}

void Grabber::set(double left, double right)
{
	left_motor.Set(left);
	right_motor.Set(right);
}

void Grabber::stop()
{
	left_motor.Set(0.0);
	right_motor.Set(0.0);
}
