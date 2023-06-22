#pragma once

#include "common.h"

// Helper class to calculate points on a line, given a distance thru that line
class Line
{
	Point start, end;

public:
	Line(Point start, Point end);

	// Ex: given a 7-unit line (0, 0) -> (7, 0):
	// -------
	// GetPoint(3) = (3, 0)
	// --o----
	// GetPoint(11) = (11, 0)
	// -------   o
	Point GetPoint(double distance);
	double GetLength();
	double GetAngle();
};

