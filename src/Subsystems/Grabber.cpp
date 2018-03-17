#include "Grabber.h"

#include "../RobotMap.h"

Grabber::Grabber() : Subsystem("Grabber"), left_motor(leftgrabberPort), right_motor(rightgrabberPort),
					 grab_solenoid(grabsolenoidmodulePort, grabsolenoidforwardPort, grabsolenoidbackwardPort),
					 extend_solenoid(extendsolenoidmodulePort, extendsolenoidforwardPort, extendsolenoidbackwardPort),
					 //encoder(grabberencoderAPort, grabberencoderBPort, false, frc::Encoder::EncodingType::k1X)
					 grab_solenoid_value(frc::DoubleSolenoid::Value::kOff)
					 //rangeFinder(rangeFinderPort)
{
	/*encoder.Reset();
	encoder.SetSamplesToAverage(9);
	encoder.SetDistancePerPulse(20);
	encoder.SetMaxPeriod(0.05);*/
	setGrabSolenoid(grab_solenoid_value);
	setExtendSolenoid(frc::DoubleSolenoid::Value::kOff);
}

void Grabber::setGrabSolenoid(frc::DoubleSolenoid::Value v)
{
	grab_solenoid.Set(v);

	if(v != frc::DoubleSolenoid::Value::kOff)
		grab_solenoid_value = v;

	if(v == frc::DoubleSolenoid::Value::kForward)
		Logger::log("forward");
	else
		Logger::log("reverse");
}

void Grabber::setExtendSolenoid(frc::DoubleSolenoid::Value v)
{
	extend_solenoid.Set(v);

	if(v != frc::DoubleSolenoid::Value::kOff)
		extend_solenoid_value = v;

	if(v == frc::DoubleSolenoid::Value::kForward)
		Logger::log("extend forward");
	else
		Logger::log("extend reverse");
}

void Grabber::toggleGrabSolenoid()
{
	if(grab_solenoid_value == frc::DoubleSolenoid::Value::kReverse)
		setGrabSolenoid(frc::DoubleSolenoid::Value::kForward);
	else
		setGrabSolenoid(frc::DoubleSolenoid::Value::kReverse);
}

void Grabber::toggleExtendSolenoid()
{
	if(extend_solenoid_value == frc::DoubleSolenoid::Value::kReverse)
		setExtendSolenoid(frc::DoubleSolenoid::Value::kForward);
	else
		setExtendSolenoid(frc::DoubleSolenoid::Value::kReverse);
}

void Grabber::succ(double speed)
{
	setMotors(speed, -speed);
}

void Grabber::adjust(double speed, bool direction)
{
	if (direction)
	{
		setMotors(speed, speed);
	}
	else
	{
		setMotors(-speed, -speed);
	}
}

// 1.0, -1.0 is to eject the cube,
// -1.0, 1.0 is to succ in the cube
void Grabber::setMotors(double left, double right)
{
	left_motor.Set(left);
	right_motor.Set(right);
}

void Grabber::stopMotors()
{
	left_motor.Set(0.0);
	right_motor.Set(0.0);
}

void Grabber::InitDefaultCommand()
{
	SetDefaultCommand(&default_command);
}
