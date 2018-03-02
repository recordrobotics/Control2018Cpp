/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Spark.h>
#include <Commands/Subsystem.h>
#include <Encoder.h>
#include <ADXRS450_Gyro.h>
#include <PIDOutput.h>
#include "../Commands/DrivewithJoystick.h"

class PIDEncoder : public frc::PIDSource {
public:
	PIDEncoder(frc::Encoder *encoder) : m_encoder(encoder) { }

	void SetPIDSourceType(frc::PIDSourceType pidSource) {
		m_pidSource = pidSource;
	}

	frc::PIDSourceType GetPIDSourceType() const { return m_pidSource; }

	double PIDGet() {
		double v = 0.0;
		if(m_pidSource == frc::PIDSourceType::kDisplacement)
			v = m_encoder->GetDistance();
		else
			v = m_encoder->GetRate();

		return v;
	}
protected:

	frc::Encoder *m_encoder;
};

class Drivetrain : public frc::Subsystem {
public:
	class DrivePIDOutput : public frc::PIDOutput {
	public:
		DrivePIDOutput(frc::Spark *motor1, frc::Spark *motor2, bool reverse) : m_reverse(reverse), m_motor1(motor1), m_motor2(motor2) { }

		void PIDWrite(double output) {
			double v = m_reverse ? -output : output;
			m_motor1->Set(v);
			m_motor2->Set(v);
		}
	protected:
		bool m_reverse;
		frc::Spark *m_motor1;
		frc::Spark *m_motor2;
	};

private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	frc::Spark left_motor1, left_motor2, right_motor1, right_motor2;

	double m_left, m_right;

	DrivewithJoystick default_command;

	frc::Encoder leftEncoder;
	frc::Encoder rightEncoder;

	PIDEncoder leftEncoderPID;
	PIDEncoder rightEncoderPID;

	DrivePIDOutput leftPIDOutput;
	DrivePIDOutput rightPIDOutput;

	frc::ADXRS450_Gyro gyro;

public:
	Drivetrain();
	~Drivetrain();
	void InitDefaultCommand() override;
	void drive(double left, double right);
	void stop();
	void driveCheesy(double throttle, double turn, double sensitivity);

	inline double getLeft() const { return m_left; }
	inline double getRight() const { return m_right; }

	inline double getLeftDistance() const { return leftEncoder.GetDistance(); }
	inline double getRightDistance() const { return rightEncoder.GetDistance(); }

	inline double getLeftRate() const { return leftEncoder.GetRate(); }
	inline double getRightRate() const { return rightEncoder.GetRate(); }

	inline double getAngle() const { return gyro.GetAngle(); }

	inline double getAngleRate() const { return gyro.GetRate(); }

	inline frc::PIDOutput *getLeftPIDOutput() const { return (frc::PIDOutput*)&leftPIDOutput; }
	inline frc::PIDOutput *getRightPIDOutput() const { return (frc::PIDOutput*)&rightPIDOutput; }

	inline frc::PIDSource *getLeftEncoderPID() const { return (frc::PIDSource*)&leftEncoderPID; }
	inline frc::PIDSource *getRightEncoderPID() const { return (frc::PIDSource*)&rightEncoderPID; }
};

