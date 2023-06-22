#pragma once

#include "common.h"

// A two-joint Inverse Kinematics calculator
struct IKArm
{
	// Lengths of each arm
	double length[2];

	// Create an IK simulation with the given arm lengths
	IKArm(double length0, double length1);

	// Return the angles needed for the arm to reach the given point
    AnglePair GetAnglePair(Point);

private:
	double CompAng2(double, double);
	double CompAng1(double, double, double);
};
