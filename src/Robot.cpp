/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Command.h>
#include <Commands/MoveToTarget.h>
#include <Commands/Scheduler.h>
#include <TimedRobot.h>
#include <Utils/MsTimer.h>
#include <DriverStation.h>

#include "Robot.h"

#include "RobotMap.h"

#include "Utils/Network.h"
#include "Utils/Logger.h"

Drivetrain Robot::drivetrain;
OI Robot::oi;
Climber Robot::climber;
Grabber Robot::grabber;

Robot::Robot() : m_period(0.01), m_moveToCubeCommand(), m_autonomousCommand()
{
	SetPeriod(m_period);
}

void Robot::getGameMessage()
{
	gameMes = frc::DriverStation::GetInstance().GetGameSpecificMessage();
}

void Robot::RobotInit() {
	MsTimer::init();
	Logger::init("/log/log.txt");
	Network::init();
	Logger::log("Begin!");

	m_autonomousCommand = &m_BSimpleCommand;
	chooser.AddDefault("BSimple", &m_BSimpleCommand);
	/*chooser.AddDefault("BSimple", m_BSimpleCommand);
	chooser.AddObject("BL_BR", m_BL_BRCommand);
	chooser.AddObject("CL_AR", m_CL_ARCommand);
	chooser.AddObject("ACSimple", m_A_CSimpleCommand);*/
}

void Robot::RobotPeriodic() {
	//rangeFinder.update();
	//Logger::log("Angle: %f", drivetrain.getAngle());
	Logger::log("Encoders: %f, %f", drivetrain.getLeftRate(), drivetrain.getRightRate());
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();

	getGameMessage();
}

void Robot::AutonomousInit() {
	getGameMessage();

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
