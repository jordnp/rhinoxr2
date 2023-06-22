#pragma once

#ifndef PI
#define PI 3.14159
#endif

// A pair of angles. Uses RADIANS unless otherwise specified.
struct AnglePair
{
	double ang1;
	double ang2;
};

struct Point
{
	double x;
	double y;
};

// The definition of one "tick" per the Rhino XR manual: 0.12 degrees
#define DEG_PER_TICK 0.12

// The C standard library (<math.h>) conflicts between platforms on whether the
// `abs` function takes and returns `int` or `double` types.
// Instead of dealing with that, here's a common implementation.
double Abs(double x);

// Common conversions

double RadToDeg(double rad);
int RadToTicks(double rad);

double DegToRad(double deg);
int DegToTicks(double deg);

double TicksToDeg(int ticks);
double TicksToRad(int ticks);
