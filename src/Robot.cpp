/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Command.h>
//#include <Commands/MoveToTarget.h>
#include <Commands/Scheduler.h>
#include <TimedRobot.h>
#include <Utils/MsTimer.h>
#include <DriverStation.h>

#include "Robot.h"

#include "RobotMap.h"

//#include "Utils/Network.h"
#include "Utils/Logger.h"

Drivetrain Robot::drivetrain;
OI Robot::oi;
Climber Robot::climber;
Grabber Robot::grabber;

Robot::Robot() : m_period(0.01), m_autonomousCommand(nullptr), m_moveForwardCommand(0.5, 0.5, 3000), m_ATwoCubeCommand(false),
								 m_CTwoCubeCommand(true), m_BLOneCubeCommand(true), m_BROneCubeCommand(false), m_BLTwoCubeCommand(true),
								 m_BRTwoCubeCommand(false), m_BGoAwayLeftCommand(true), m_BGoAwayRightCommand(false)
				/*m_BLCommand(true), m_BRCommand(false),
				 m_BSimpleLeftCommand(true), m_BSimpleRightCommand(false), m_CLCommand(true),
				 m_ARCommand(false), m_A_CSimpleCommand(0.5, 0.5, 3500), m_supersimpleCommand(0.5, 0.5, 3500),
				 smoothMove("/path/path1", "/path/constants", 0.01, 10.0, 20.0, 40.0)*/
{
	SetPeriod(m_period);
}

bool Robot::getAuto()
{
	if(autoChooser.GetSelected() == EAC_FORWARD) {
		m_autonomousCommand = &m_moveForwardCommand;
		//Logger::log("Simple");
		return true;
	}

	std::string s = frc::DriverStation::GetInstance().GetGameSpecificMessage();

	//Logger::log("Message: %s", s.c_str());

	if(s.length() > 0) {
		E_AUTO_CHOOSE choose = autoChooser.GetSelected();
		E_START_POSITION position = positionChooser.GetSelected();
		E_SWITCH switch_pos = ES_COUNT;

		if(s[0] == 'L')
			switch_pos = ES_LEFT;
		else if(s[0] == 'R')
			switch_pos = ES_RIGHT;

		if(switch_pos != ES_COUNT) {
			auto it = autoMap.find({ choose, position, switch_pos });

			if(it != autoMap.end()) {
				m_autonomousCommand = it->second;
				//Logger::log("%d %d %d found", choose, position, switch_pos);
				return true;
			}
			//else
			//	Logger::log("%d %d %d not found", choose, position, switch_pos);
		}
	}

	return false;
}


void Robot::RobotInit() {
	MsTimer::init();
	Logger::init("/log/log.txt");
	//Network::init();
	Logger::log("Begin!");

	autoMap.insert({ { EAC_ONECUBE, ESP_LEFT, ES_LEFT }, &m_COneCubeCommand });
	autoMap.insert({ { EAC_ONECUBE, ESP_LEFT, ES_RIGHT }, &m_moveForwardCommand });
	autoMap.insert({ { EAC_ONECUBE, ESP_RIGHT, ES_LEFT }, &m_moveForwardCommand });
	autoMap.insert({ { EAC_ONECUBE, ESP_RIGHT, ES_RIGHT }, &m_AOneCubeCommand });
	autoMap.insert({ { EAC_ONECUBE, ESP_CENTER, ES_LEFT }, &m_BLOneCubeCommand });
	autoMap.insert({ { EAC_ONECUBE, ESP_CENTER, ES_RIGHT }, &m_BROneCubeCommand });
	autoMap.insert({ { EAC_TWOCUBE, ESP_LEFT, ES_LEFT }, &m_CTwoCubeCommand });
	autoMap.insert({ { EAC_TWOCUBE, ESP_LEFT, ES_RIGHT }, &m_moveForwardCommand });
	autoMap.insert({ { EAC_TWOCUBE, ESP_RIGHT, ES_LEFT }, &m_moveForwardCommand });
	autoMap.insert({ { EAC_TWOCUBE, ESP_RIGHT, ES_RIGHT }, &m_ATwoCubeCommand });
	autoMap.insert({ { EAC_TWOCUBE, ESP_CENTER, ES_LEFT }, &m_BLTwoCubeCommand });
	autoMap.insert({ { EAC_TWOCUBE, ESP_CENTER, ES_RIGHT }, &m_BRTwoCubeCommand });
	autoMap.insert({ { EAC_TWOCUBE, ESP_LEFT, ES_RIGHT }, &m_moveForwardCommand });
	autoMap.insert({ { EAC_GOAWAY, ESP_LEFT, ES_LEFT }, &m_moveForwardCommand });
	autoMap.insert({ { EAC_GOAWAY, ESP_LEFT, ES_RIGHT }, &m_moveForwardCommand });
	autoMap.insert({ { EAC_GOAWAY, ESP_RIGHT, ES_LEFT }, &m_moveForwardCommand });
	autoMap.insert({ { EAC_GOAWAY, ESP_RIGHT, ES_RIGHT }, &m_moveForwardCommand });
	autoMap.insert({ { EAC_GOAWAY, ESP_CENTER, ES_LEFT }, &m_BGoAwayRightCommand });
	autoMap.insert({ { EAC_GOAWAY, ESP_CENTER, ES_RIGHT }, &m_BGoAwayLeftCommand });
	/*autoMap.insert({ { EAC_SIMPLE_RIGHT, ESP_LEFT, ES_LEFT }, &m_A_CSimpleCommand });
	autoMap.insert({ { EAC_SIMPLE_RIGHT, ESP_LEFT, ES_RIGHT }, &m_A_CSimpleCommand });
	autoMap.insert({ { EAC_SIMPLE_AWAY, ESP_LEFT, ES_LEFT }, &m_A_CSimpleCommand });
	autoMap.insert({ { EAC_SIMPLE_AWAY, ESP_LEFT, ES_RIGHT }, &m_A_CSimpleCommand });
	autoMap.insert({ { EAC_SIMPLE_LEFT, ESP_RIGHT, ES_LEFT }, &m_A_CSimpleCommand });
	autoMap.insert({ { EAC_SIMPLE_LEFT, ESP_RIGHT, ES_RIGHT }, &m_A_CSimpleCommand });
	autoMap.insert({ { EAC_SIMPLE_RIGHT, ESP_RIGHT, ES_LEFT}, &m_A_CSimpleCommand });
	autoMap.insert({ { EAC_SIMPLE_RIGHT, ESP_RIGHT, ES_RIGHT}, &m_A_CSimpleCommand });
	autoMap.insert({ { EAC_SIMPLE_AWAY, ESP_RIGHT, ES_LEFT }, &m_A_CSimpleCommand });
	autoMap.insert({ { EAC_SIMPLE_AWAY, ESP_RIGHT, ES_RIGHT }, &m_A_CSimpleCommand });
	autoMap.insert({ { EAC_SIMPLE_LEFT, ESP_CENTER, ES_LEFT }, &m_BSimpleLeftCommand });
	autoMap.insert({ { EAC_SIMPLE_LEFT, ESP_CENTER, ES_RIGHT }, &m_BSimpleLeftCommand });
	autoMap.insert({ { EAC_SIMPLE_RIGHT, ESP_CENTER, ES_LEFT }, &m_BSimpleRightCommand });
	autoMap.insert({ { EAC_SIMPLE_RIGHT, ESP_CENTER, ES_RIGHT }, &m_BSimpleRightCommand });
	autoMap.insert({ { EAC_SIMPLE_AWAY, ESP_CENTER, ES_LEFT }, &m_BSimpleRightCommand });
	autoMap.insert({ { EAC_SIMPLE_AWAY, ESP_CENTER, ES_RIGHT }, &m_BSimpleLeftCommand });
	autoMap.insert({ { EAC_NEARSWITCH, ESP_LEFT, ES_LEFT }, &m_CLCommand });
	autoMap.insert({ { EAC_NEARSWITCH, ESP_LEFT, ES_RIGHT }, &m_A_CSimpleCommand });
	autoMap.insert({ { EAC_NEARSWITCH, ESP_RIGHT, ES_LEFT }, &m_A_CSimpleCommand });
	autoMap.insert({ { EAC_NEARSWITCH, ESP_RIGHT, ES_RIGHT }, &m_ARCommand });
	autoMap.insert({ { EAC_NEARSWITCH, ESP_CENTER, ES_LEFT }, &m_BLCommand });
	autoMap.insert({ { EAC_NEARSWITCH, ESP_CENTER, ES_RIGHT }, &m_BRCommand });*/

	autoChooser.AddDefault("Forward", EAC_FORWARD);
	autoChooser.AddObject("OneCube", EAC_ONECUBE);
	autoChooser.AddObject("TwoCube", EAC_TWOCUBE);
	autoChooser.AddObject("GoAway", EAC_GOAWAY);

	positionChooser.AddDefault("Left", ESP_LEFT);
	positionChooser.AddObject("Center", ESP_CENTER);
	positionChooser.AddObject("Right", ESP_RIGHT);

	frc::SmartDashboard::PutData("Auto Chooser", &autoChooser);
	frc::SmartDashboard::PutData("Position Chooser", &positionChooser);

	drivetrain.setLights(false);
	grabber.setExtendSolenoid(frc::DoubleSolenoid::Value::kReverse);
}

void Robot::RobotPeriodic() {
	//rangeFinder.update();
	//Logger::log("Angle: %f", drivetrain.getAngle());
	//Logger::log("Encoders: %f, %f", drivetrain.getLeftRate(), drivetrain.getRightRate());

	//std::string s = frc::DriverStation::GetInstance().GetGameSpecificMessage();

	//Logger::log("Message: %s", s.c_str());
}

void Robot::DisabledInit() {
}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();

	getAuto();
}

void Robot::AutonomousInit() {
	/*getGameMessage();

	E_START_POSITION pos = positionChooser.getSelected();
	E_AUTO_CHOOSE choose = autochooser.getSelected();

	if(gameMes.length) {
		if(gameMes[0] == 'L') {
			switch(pos) {
			case ESP_LEFT:
				if(choose == EAC_SIMPLE_LEFT || choose == EAC_SIMPLE_RIGHT)
					m_autonomousCommand = &m_A_CSimpleCommand;
				else if(choose == EAC_NEARSWITCH)
					m_autonomousCommand = &m_CL_ARCommand;
				break;
			case ESP_RIGHT:
				if(choose == EAC_SIMPLE_LEFT || choose == EAC_SIMPLE_RIGHT || choose == EAC_NEARSWITCH)
					m_autonomousCommand = &m_A_CSimpleCommand;
				break;
			case ESP_CENTER:
				switch(choose) {
				case EAC_SIMPLE_LEFT:
					m_autonomousCommand = &m_BSimpleLeftCommand;
					break;
				case EAC_SIMPLE_RIGHT:
					m_autonomousCommand = &m_BSimpleRightCommand;
					break;
				case EAC_NEARSWITCH:
					m_autonomousCommand = &m_BLCommand;
					break;
				};
				break;
			default:
				break;
			};
		}
		else if(gameMes[0] == 'R') {
			switch(pos) {
			case ESP_RIGHT:
				if(choose == EAC_SIMPLE_LEFT || choose == EAC_SIMPLE_RIGHT)
					m_autonomousCommand = &m_A_CSimpleCommand;
				else if(choose == EAC_NEARSWITCH)
					m_autonomousCommand = &m_CL_ARCommand;
				break;
			case ESP_LEFT:
				if(choose == EAC_SIMPLE_LEFT || choose == EAC_SIMPLE_RIGHT || choose == EAC_NEARSWITCH)
					m_autonomousCommand = &m_A_CSimpleCommand;
				break;
			case ESP_CENTER:
				switch(choose) {
				case EAC_SIMPLE_LEFT:
					m_autonomousCommand = &m_BSimpleLeftCommand;
					break;
				case EAC_SIMPLE_RIGHT:
					m_autonomousCommand = &m_BSimpleRightCommand;
					break;
				case EAC_NEARSWITCH:
					m_autonomousCommand = &m_BRCommand;
					break;
				};
				break;
			default:
				break;
			};
		}
	}*/

	getAuto();

	grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kForward);
	grabber.setExtendSolenoid(frc::DoubleSolenoid::Value::kForward);

	if (m_autonomousCommand != nullptr) {
		m_autonomousCommand->Start();
	}
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	grabber.setGrabSolenoid(frc::DoubleSolenoid::Value::kForward);
	grabber.setExtendSolenoid(frc::DoubleSolenoid::Value::kForward);

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
