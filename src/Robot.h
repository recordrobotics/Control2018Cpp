#pragma once

#include "Subsystems/Drivetrain.h"
#include "OI.h"
#include <TimedRobot.h>
#include <Commands/Command.h>
#include "Commands/MoveToCube.h"

class Robot : public frc::TimedRobot {
public:
	static Drivetrain drivetrain;
	static OI oi;

	Robot();

	inline double getPeriod() const { return m_period; }

private:
	MoveToCube m_moveToCubeCommand;
	Command *m_autonomousCommand;

	double m_period;

	void RobotInit() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
};
