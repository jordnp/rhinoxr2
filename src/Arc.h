#pragma once

#include "common.h"

enum class ArcDir
{
	// Clockwise
	CW,
	// Counter-Clockwise
	CCW,
};

// The name 'Arc' is taken by a windows function.
// Thank you microsoft, very cool!
// Helper class to calculate points on a circle/arc.
class ArcCalc
{
	bool isCircle;
	Point origin;
	double radius;
	double startAngle, endAngle;
public:
	ArcCalc(Point start, Point end, Point center);

	// delta: number 0 thru 1 inclusive.
	//   0 = Start, 1 = End
	// dir: Clockwise or CounterClockwise?
	Point GetPoint(double delta, ArcDir dir);
};
