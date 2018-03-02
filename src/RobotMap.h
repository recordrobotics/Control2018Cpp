/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <SerialPort.h>

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int kLeftMotor = 1;
// constexpr int kRightMotor = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int kRangeFinderPort = 1;
// constexpr int kRangeFinderModule = 1;

// Motors
constexpr int leftmotor1Port = 0;
constexpr int leftmotor2Port = 1;
constexpr int rightmotor1Port = 2;
constexpr int rightmotor2Port = 3;
constexpr int climbmotorPort = 4;
constexpr int leftgrabberPort = 5;
constexpr int rightgrabberPort = 6;

// Other actuators
constexpr int grabsolenoidmodulePort = 0;
constexpr int grabsolenoidforwardPort = 0;
constexpr int grabsolenoidbackwardPort = 1;
constexpr int pushsolenoidmodulePort = 0;
constexpr int pushsolenoidforwardPort = 2;
constexpr int pushsolenoidbackwardPort = 3;

// Joysticks and buttons
constexpr int leftjoystickPort = 0;
constexpr int rightjoystickPort = 1;
constexpr int climberbuttonPort = 1;
//constexpr int opengrabberbuttonPort = 5;
//constexpr int closegrabberbuttonPort = 6;
constexpr int togglegrabberbuttonPort = 2;
constexpr int forward_axis = 1;
constexpr int grabber_axis = 0;

// Sensors
constexpr int bottomswitchPort = 1;
constexpr int topswitchPort = 2;
constexpr int rangefinderPort = 0;
constexpr int leftEncoderPort1 = 3;
constexpr int leftEncoderPort2 = 4;
constexpr int rightEncoderPort1 = 5;
constexpr int rightEncoderPort2 = 6;
constexpr frc::SerialPort::Port rangeFinderPort = frc::SerialPort::Port::kOnboard;
