#include "Line.h"

#include <cmath>

Line::Line(Point p1, Point p2)
{
	start = p1;
	end = p2;
}

double Line::GetLength()
{
	double x = abs(start.x - end.x);
	double y = abs(start.y - end.y);

	return sqrt(x * x + y * y);
}

double Line::GetAngle()
{
	return atan((end.x - start.x) / (end.y - start.y));
}

Point Line::GetPoint(double dist)
{
	double sign = end.y < start.y ? -1 : 1;
	return Point {
		sign * dist * sin(GetAngle()) + start.x,
		sign * dist * cos(GetAngle()) + start.y,
	};
}
