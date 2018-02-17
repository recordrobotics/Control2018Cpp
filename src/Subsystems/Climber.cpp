/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Climber.h"
#include "../RobotMap.h"

#include "../RobotMap.h"

Climber::Climber() : Subsystem("Climber"), bottom_switch(bottomswitchPort),
					 top_switch(topswitchPort), motor(climbmotorPort), default_command()
{
}

void Climber::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(&default_command);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
