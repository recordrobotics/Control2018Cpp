#pragma once

#include <Commands/Auto/A_CTwoCube.h>
#include <Commands/Auto/BTwoCube.h>
#include <unordered_map>

#include "Subsystems/Drivetrain.h"
#include "OI.h"
#include <TimedRobot.h>
#include <Commands/Command.h>
//#include <Commands/MoveToTarget.h>
#include <Commands/CommandGroup.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "Subsystems/Climber.h"
#include "Subsystems/Grabber.h"
#include "Commands/Auto/A_COneCube.h"
#include "Commands/Auto/A_CTwoCube.h"
#include "Commands/Auto/BOneCube.h"
#include "Commands/Auto/BTwoCube.h"

#include "Commands/Auto/BSimple.h"

// List of autonomous modes to be selected by driver
enum E_AUTO_CHOOSE {
	EAC_FORWARD = 0,
	EAC_ONECUBE,
	EAC_TWOCUBE,
	EAC_GOAWAY,
	EAC_COUNT
};

// Start position of robot as selected by driver
enum E_START_POSITION {
	ESP_LEFT = 0,
	ESP_CENTER,
	ESP_RIGHT,
	ESP_COUNT
};

enum E_SWITCH {
	ES_LEFT = 0,
	ES_RIGHT,
	ES_COUNT
};

struct auto_key {
	E_AUTO_CHOOSE choose;
	E_START_POSITION position;
	E_SWITCH switch_pos;
};

struct auto_hash {
	std::size_t operator()(const auto_key& k) const {
		return std::hash<std::string>()(std::to_string(k.choose) + std::to_string(k.position) + std::to_string(k.switch_pos));
	}
};

struct auto_equal {
	bool operator()(const auto_key& key1, const auto_key& key2) const {
		return (key1.choose == key2.choose && key1.position == key2.position && key1.switch_pos == key2.switch_pos);
	}
};

class Robot : public frc::TimedRobot {
public:
	static Drivetrain drivetrain;
	static Climber climber;
	static Grabber grabber;
	static OI oi;

	Robot();

private:
	bool getAuto();

	double m_period;

	frc::Command *m_autonomousCommand;
	/*BL_BR m_BLCommand;
	BL_BR m_BRCommand;
	BSimple m_BSimpleLeftCommand;
	BSimple m_BSimpleRightCommand;
	CL_AR m_CLCommand;
	CL_AR m_ARCommand;
	MoveTime m_A_CSimpleCommand;
	MoveTime m_supersimpleCommand;
	SmoothMove smoothMove;*/
	MoveTime m_moveForwardCommand;
	A_COneCube m_AOneCubeCommand;
	A_COneCube m_COneCubeCommand;
	A_CTwoCube m_ATwoCubeCommand;
	A_CTwoCube m_CTwoCubeCommand;
	BOneCube m_BLOneCubeCommand;
	BOneCube m_BROneCubeCommand;
	BTwoCube m_BLTwoCubeCommand;
	BTwoCube m_BRTwoCubeCommand;
	BSimple m_BGoAwayLeftCommand;
	BSimple m_BGoAwayRightCommand;

	frc::SendableChooser<E_AUTO_CHOOSE> autoChooser;
	frc::SendableChooser<E_START_POSITION> positionChooser;

	std::unordered_map<auto_key, frc::Command*, auto_hash, auto_equal> autoMap;

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
