#pragma once

#include "Subsystems/Drivetrain.h"
#include "OI.h"
#include <TimedRobot.h>
#include <Commands/Command.h>
#include "Commands/MoveToCube.h"
#include "Subsystems/Climber.h"
#include "Subsystems/Grabber.h"

class Robot : public frc::TimedRobot {
public:
	static Drivetrain drivetrain;
	static Climber climber;
	static Grabber grabber;
	static OI oi;

	Robot();

private:
	double m_period;

	MoveToCube m_moveToCubeCommand;
	Command *m_autonomousCommand;

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
