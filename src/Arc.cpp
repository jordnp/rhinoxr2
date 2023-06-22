#include "Arc.h"

#include <cmath>
#include <cstdio>

static double AngleToPoint(Point from, Point to)
{
	Point diff = {
		to.x - from.x,
		to.y - from.y,
	};
	return atan2(diff.y, diff.x);
}

#define MAXIMUM_RADIUS_DIFF 0.1

ArcCalc::ArcCalc(Point start, Point end, Point center)
{
	origin = center;
	isCircle = start.x == end.x && start.y == end.y;
	startAngle = AngleToPoint(origin, start);
	endAngle = AngleToPoint(origin, end);

	// Verify this circle is logically possible
	Point diff0 = { abs(start.x - origin.x), abs(start.y - origin.y) };
	double rad0 = sqrt(diff0.x*diff0.x + diff0.y*diff0.y);
	Point diff1 = { end.x - origin.x, end.y - origin.y };
	double rad1 = sqrt(diff1.x * diff1.x + diff1.y * diff1.y);

	if (Abs(rad0 - rad1) > MAXIMUM_RADIUS_DIFF)
	{
		printf("[ArcCalc] Dubious circle from (%0.2f, %0.2f) to (%0.2f, %0.2f), center=(%0.2f, %0.2f) [radius %0.2f != %0.2f]\n", start.x, start.y, end.x, end.y, center.x, center.y, rad0, rad1);
		puts("Continuing anyway...");
		//exit(1);
	}

	radius = rad0;
}

// "linear interpolation"
static double lerp(double a, double b, double delta)
{
	return a + (b - a) * delta;
}

//todo: get this out of my sight
struct Vec2
{
	double x, y;

	void rotate(double rad)
	{
		const double _x = x;
		x = _x * cos(rad) - y * sin(rad);
		y = _x * sin(rad) + y * cos(rad);
	}
};

static double NormalizeAngle(double ang)
{
	if (ang > 0)
		return ang;
	else
		return ang + 2*PI;
}

Point ArcCalc::GetPoint(double delta, ArcDir dir)
{
	// This sucks.
	// However, it works in enough cases that it doesn't seem worthwhile to
	// figure out how to make a foolproof, and probably simpler, solution.
	double ang;
	if (isCircle)
	{
		if (dir == ArcDir::CW)
			ang = lerp(startAngle, endAngle - 2 * PI, delta);
		else
			ang = lerp(startAngle, endAngle + 2*PI, delta);
	}
	else
	{
		double realEnd;
		if (dir == ArcDir::CW)
			if (startAngle > endAngle)
				realEnd = endAngle;
			else
				if (startAngle < 0 && endAngle < 0)
					realEnd = endAngle - 2 * PI;
				else
					realEnd = -NormalizeAngle(-endAngle);
		else // dir == CCW
			if (startAngle < endAngle)
				realEnd = endAngle;
			else
				realEnd = NormalizeAngle(endAngle);

		ang = lerp(startAngle, realEnd, delta);
	}
	Vec2 v = { radius, 0 };
	v.rotate(ang);

	Point res = {
		origin.x + v.x,
		origin.y + v.y,
	};
	return res;
}
