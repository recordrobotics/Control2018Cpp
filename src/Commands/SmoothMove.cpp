/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <fstream>

#include "SmoothMove.h"

#include "../Robot.h"
#include "../Utils/MsTimer.h"

extern "C" {
#include <pathfinder/trajectory.h>
#include <pathfinder/mathutil.h>
#include <pathfinder/spline.h>
#include <pathfinder/fit.h>
#include <pathfinder/modifiers/tank.h>
#include <pathfinder/io.h>
}

SmoothMove::SmoothMove(const char *fname, const char *fconstants, double dt, double mvel, double macc, double mjerk) : constants_path(fconstants), curve_period(dt),
					   max_vel(mvel), max_acc(macc), max_jerk(mjerk), k_p(0.1), k_i(0.01), k_d(0.05), k_f(1.0 / mvel), pid_period(0.01),
					   left_controller(k_p, k_i, k_d, k_f, Robot::drivetrain.getLeftEncoderPID(), Robot::drivetrain.getLeftPIDOutput(), pid_period),
					   right_controller(k_p, k_i, k_d, k_f, Robot::drivetrain.getRightEncoderPID(), Robot::drivetrain.getRightPIDOutput(), pid_period)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::drivetrain);

	wheelbase_width = 0.6;
	k_tolerance = 0.01;
	finished = false;
	k_di = 0.7;
	k_ti = 0.3;
	start_time = 0;
	start_left_dist = 0.0;
	start_right_dist = 0.0;
	last_dist_idx = 0;

	Robot::drivetrain.getLeftEncoderPID()->SetPIDSourceType(frc::PIDSourceType::kRate);
	Robot::drivetrain.getRightEncoderPID()->SetPIDSourceType(frc::PIDSourceType::kRate);

	std::ifstream file(fname);

	if(file.is_open()) {
		double x, y, theta;

		while(file >> x >> y >> theta)
			waypoints.push_back({ x, y , d2r(theta) });

		file.close();
	}

	if(!waypoints.size())
		finished = true;
	else {
		TrajectoryCandidate candidate;

		pathfinder_prepare(&waypoints[0], waypoints.size(), FIT_HERMITE_QUINTIC, PATHFINDER_SAMPLES_FAST, curve_period, max_vel, max_acc, max_jerk, &candidate);

		int length = candidate.length;
		segments.resize(length);

		pathfinder_generate(&candidate, &segments[0]);

		leftsegments.resize(length);
		rightsegments.resize(length);

		pathfinder_modify_tank(&segments[0], length, &leftsegments[0], &rightsegments[0], wheelbase_width);
	}
}

double SmoothMove::findClosest(const std::vector<Segment>& arr, double dist, int guess)
{
	int arr_size = arr.size();

	if(!arr_size)
		return 1.0;

	double idx = 0.0;

	if(guess > (arr_size - 1))
		guess = arr_size - 1;
	else if(guess < 0)
		guess = 0;

	if(arr[guess].position > dist) {
		for(int i = (guess - 1); i >= 0; i--) {
			if(arr[i].position < dist) {
				double f = (dist - arr[i].position) / (arr[i + 1].position - arr[i].position);
				idx = f * (double)(i + 1) + (1.0 - f) * (double)i;
				break;
			}
		}
	}
	else if(arr[guess].position < dist) {
		idx = arr_size + 1.0;

		for(int i = (guess + 1); i < arr_size; i++) {
			if(arr[i].position > dist) {
				double f = (dist - arr[i - 1].position) / (arr[i].position - arr[i - 1].position);
				idx = f * (double)i + (1.0 - f) * (double)(i - 1);
				break;
			}
		}
	}

	return idx;
}

// Called just before this Command runs the first time
void SmoothMove::Initialize() {
	last_dist_idx = 0;

	start_time = MsTimer::getMs();

	Robot::drivetrain.stop();

	left_controller.Reset();
	right_controller.Reset();

	left_controller.SetAbsoluteTolerance(k_tolerance);
	right_controller.SetAbsoluteTolerance(k_tolerance);

	left_controller.SetSetpoint(leftsegments[0].velocity);
	right_controller.SetSetpoint(rightsegments[0].velocity);

	left_controller.Enable();
	right_controller.Enable();

	start_time = MsTimer::getMs();
	start_right_dist = Robot::drivetrain.getRightDistance();
	start_left_dist = Robot::drivetrain.getLeftDistance();

	if(Logger::getFp()) {
		pathfinder_serialize(Logger::getFp(), &leftsegments[0], leftsegments.size());
		pathfinder_serialize(Logger::getFp(), &rightsegments[0], rightsegments.size());
	}

	finished = false;
}

// Called repeatedly when this Command is scheduled to run
void SmoothMove::Execute() {
	if(finished)
		return;

	std::ifstream fconst(constants_path);
	if(fconst.is_open()) {
		fconst >> k_p >> k_i >> k_d >> k_di >> k_ti >> k_tolerance;
		Logger::log("%f %f %f %f %f %f", k_p, k_i, k_d, k_di, k_ti, k_tolerance);
		fconst.close();
	}

	ms_t time_passed = MsTimer::getMs() - start_time;
	double time_idx = (double)time_passed / (curve_period * 1000.0);

	double avg_dist =  0.5 * ((Robot::drivetrain.getLeftDistance() - start_left_dist) + (Robot::drivetrain.getRightDistance() - start_right_dist));
	double dist_idx = findClosest(segments, avg_dist, (int)last_dist_idx);

	int idx = (int)((k_di * dist_idx + k_ti * time_idx) / (k_di + k_ti));

	if(idx > (segments.size() - 1)) {
		finished = true;
		return;
	}

	left_controller.SetSetpoint(leftsegments[idx].velocity);
	right_controller.SetSetpoint(rightsegments[idx].velocity);

	last_dist_idx = dist_idx;

	Logger::log("idx: %d, desired angle: %f, actual angle: %f", idx, 180.0 * segments[idx].heading / 3.141592, Robot::drivetrain.getAngle());

	/*ms_t time_passed = MsTimer::getMs() - start_time;
	int segment_idx = time_passed / m_dt;

	Segment left_s = leftsegments[segment_idx];
	Segment right_s = rightsegments[segment_idx];

	double left_d_e = (Robot::drivetrain.getLeftDistance() - left_s.position);
	double right_d_e = (Robot::drivetrain.getRightDistance() - right_s.position);

	double left_v_e = (Robot::drivetrain.getLeftRate() - left_s.velocity);
	double right_v_e = (Robot::drivetrain.getRightRate() - right_s.velocity);

	double left_a_e = (Robot::drivetrain.getLeftAcc() - left_s.acceleration);
	double right_a_e = (Robot::drivetrain.getRightAcc() - right_s.acceleration);

	double left = k_a_p * -left_a_e + k_v_p * -left_v_e + k_d_p * -left_p_e +
				  k_a_d * -left_a_e + k_v_d * -left_v_e + k_d_;
	double right = k_a_p * -right_a_e + k_v_p * -right_v_e + k_d_p * -right_p_e;*/
}

// Make this return true when this Command no longer needs to run execute()
bool SmoothMove::IsFinished() {
	return finished;
}

// Called once after isFinished returns true
void SmoothMove::End() {
	left_controller.Disable();
	right_controller.Disable();
	Robot::drivetrain.stop();
	finished = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SmoothMove::Interrupted() {
	left_controller.Disable();
	right_controller.Disable();
	Robot::drivetrain.stop();
}
