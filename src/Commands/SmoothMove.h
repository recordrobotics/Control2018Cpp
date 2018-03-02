/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>

#include <PIDController.h>

extern "C" {
#include <pathfinder/structs.h>
}

#include <Utils/MsTimer.h>

#include <vector>

class SmoothMove : public frc::Command {
public:
	SmoothMove(const char *fname, const char *fconstants, double dt, double mvel, double macc, double mjerk);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

	static double findClosest(const std::vector<Segment>& arr, double dist, int guess);

private:
	const char *constants_path;
	double curve_period;
	double max_vel, max_acc, max_jerk;
	double k_p, k_i, k_d, k_f;
	double pid_period;
	frc::PIDController left_controller, right_controller;
	std::vector<Segment> segments, leftsegments, rightsegments;
	ms_t start_time;
	double wheelbase_width;
	double k_tolerance;
	double k_di, k_ti;
	double start_left_dist, start_right_dist;
	int last_dist_idx;
	bool finished;
	std::vector<Waypoint> waypoints;
};

