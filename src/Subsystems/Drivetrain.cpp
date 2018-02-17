/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivetrain.h"
#include "../RobotMap.h"
#include "../Commands/DrivewithJoystick.h"

#include "../Utils/Logger.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain"), left_motor1(leftmotor1Port),
		left_motor2(leftmotor2Port), right_motor1(rightmotor1Port), right_motor2(rightmotor2Port),
		default_command(), m_left(0.0), m_right(0.0)
{

}

Drivetrain::~Drivetrain() {
}

void Drivetrain::drive(double left, double right) {
	m_left = left;
	m_right = right;

	Logger::log("motors: %f %f", m_left, m_right);

	left_motor1.Set(-m_left);
	left_motor2.Set(-m_left);
	right_motor1.Set(m_right);
	right_motor2.Set(m_right);
}

void Drivetrain::stop() {
	left_motor1.Set(0);
	left_motor2.Set(0);
	right_motor1.Set(0);
	right_motor2.Set(0);
}

void DriveTrain::driveCheesy(double throttle, double turn, double sensitivity)
{
	double left, right;

	throttle = throttle * sensitivity;
	turn = turn * sensitivity;
	
	left = throttle-turn;
	right = throttle+turn;

	drive(left, right);
}


void Drivetrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(&default_command);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
