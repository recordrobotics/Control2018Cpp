#include "Grabber.h"

#include "../RobotMap.h"

Grabber::Grabber() : Subsystem("Grabber"), left_motor(leftgrabberPort), right_motor(rightgrabberPort),
					 grab_solenoid(grabsolenoidmodulePort, grabsolenoidforwardPort, grabsolenoidbackwardPort),
					 push_solenoid(pushsolenoidmodulePort, pushsolenoidforwardPort, pushsolenoidbackwardPort),
					 //encoder(grabberencoderAPort, grabberencoderBPort, false, frc::Encoder::EncodingType::k1X)
					 grab_solenoid_value(frc::DoubleSolenoid::Value::kReverse), push_solenoid_value(frc::DoubleSolenoid::Value::kReverse)
					 //rangeFinder(rangeFinderPort)
{
	/*encoder.Reset();
	encoder.SetSamplesToAverage(9);
	encoder.SetDistancePerPulse(20);
	encoder.SetMaxPeriod(0.05);*/
	setGrabSolenoid(grab_solenoid_value);
	setGrabSolenoid(frc::DoubleSolenoid::Value::kOff);
	setPushSolenoid(push_solenoid_value);
	setPushSolenoid(frc::DoubleSolenoid::Value::kOff);
}

void Grabber::setGrabSolenoid(frc::DoubleSolenoid::Value v)
{
	grab_solenoid.Set(v);

	if(v != frc::DoubleSolenoid::Value::kOff)
		grab_solenoid_value = v;
}

void Grabber::setPushSolenoid(frc::DoubleSolenoid::Value v)
{
	push_solenoid.Set(v);

	if(v != frc::DoubleSolenoid::Value::kOff)
		push_solenoid_value = v;
}

void Grabber::toggleGrabSolenoid()
{
	if(grab_solenoid_value == frc::DoubleSolenoid::Value::kReverse)
		setGrabSolenoid(frc::DoubleSolenoid::Value::kForward);
	else
		setGrabSolenoid(frc::DoubleSolenoid::Value::kReverse);
}

void Grabber::togglePushSolenoid()
{
	if(push_solenoid_value == frc::DoubleSolenoid::Value::kReverse)
		setPushSolenoid(frc::DoubleSolenoid::Value::kForward);
	else
		setPushSolenoid(frc::DoubleSolenoid::Value::kReverse);
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

void Grabber::InitDefaultCommand()
{
	SetDefaultCommand(&default_command);
}
