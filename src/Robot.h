#pragma once

#include "Subsystems/Drivetrain.h"
#include "OI.h"
#include <TimedRobot.h>
#include <Commands/Command.h>
#include <Commands/MoveToTarget.h>
#include <Commands/CommandGroup.h>
#include <SmartDashboard/SendableChooser.h>
#include "Subsystems/Climber.h"
#include "Subsystems/Grabber.h"

#include "Commands/Auto/BL_BR.h"
#include "Commands/Auto/BSimple.h"
#include "Commands/Auto/CL_AR.h"
#include "Commands/MoveTime.h"

class Robot : public frc::TimedRobot {
public:
	static Drivetrain drivetrain;
	static Climber climber;
	static Grabber grabber;
	static OI oi;

	Robot();

private:
	void getGameMessage();
	std::string gameMes;

	double m_period;

	AutoGroup m_autonomousCommand;
	BL_BR m_BL_BRCommand;
	BSimple m_BSimpleCommand;
	CL_AR m_C_ARCommand;
	MoveTime m_A_CSimpleCommand;

	frc::SendableChooser<frc::CommandGroup*> chooser;

	void RobotInit() override;
	void RobotPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
};
