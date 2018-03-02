/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <TimedRobot.h>
#include <Utils/MsTimer.h>

#include "Robot.h"

#include "RobotMap.h"

#include "Commands/MoveToCube.h"

#include "Utils/Network.h"
#include "Utils/Logger.h"

Drivetrain Robot::drivetrain;
OI Robot::oi;
Climber Robot::climber;
Grabber Robot::grabber;

Robot::Robot() : m_period(0.01), m_moveToCubeCommand(), m_autonomousCommand(nullptr)
{
	SetPeriod(m_period);
}

void Robot::RobotInit() {
	MsTimer::init();
	Logger::init("/log/log.txt");
	Network::init();
	Logger::log("Begin!");

	m_autonomousCommand = &m_moveToCubeCommand;
}

void Robot::RobotPeriodic() {
	//rangeFinder.update();
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	if (m_autonomousCommand != nullptr) {
		m_autonomousCommand->Start();
	}
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	if (m_autonomousCommand != nullptr) {
		m_autonomousCommand->Cancel();
		m_autonomousCommand = nullptr;
	}
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {}

START_ROBOT_CLASS(Robot)
