#include "RobotMover.h"

#include <cstdio>
#include <cmath>

#include "Line.h"

AnglePair RobotMover::GetCurrentAngles()
{
	return AnglePair { TicksToRad(ticks[0]), TicksToRad(ticks[1]) };
}

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

Point RobotMover::GetCurrentPoint()
{
	AnglePair ang = GetCurrentAngles();
	
	Vec2 arm0 = { 9, 0 };
	arm0.rotate(ang.ang1);
	Vec2 arm1 = { 9, 0 };
	arm1.rotate(ang.ang1);
	arm1.rotate(-ang.ang2);

	return Point{arm0.x+arm1.x, arm0.y+arm1.y};
}

void RobotMover::MoveToPoint(Point target)
{
	float magnitude = sqrt(target.x * target.x + target.y * target.y);
	if (magnitude >= 18)
	{
		printf("Point { %0.2f, %0.2f } is out of range! (%0.2f inches)\n", target.x, target.y, magnitude);
		exit(1);
	}
	AnglePair targetAngles = ikCalculator.GetAnglePair(target);

	int movement0 = ticks[0] - RadToTicks(targetAngles.ang1);
	int movement1 = ticks[1] - RadToTicks(targetAngles.ang2);

	if (movement0 != 0)
		rhino.MoveMotor('E', movement0);

	// The Rhino does some automatic adjustments when moving a parent arm.
	// But that messes up my calculations, so it must be compensated.
	if (movement1-movement0 != 0)
		rhino.MoveMotor('D', movement1-movement0);

	ticks[0] -= movement0;
	ticks[1] -= movement1;
}

void RobotMover::DrawLineTo(Point target)
{
	AnglePair targetAngles = ikCalculator.GetAnglePair(target);
	int targetTicks[2] = { RadToTicks(targetAngles.ang1), RadToTicks(targetAngles.ang2) };
	
	Line line(GetCurrentPoint(), target);
	
	double stepSize = 0.1;
	int steps = int(line.GetLength() / stepSize);
	for (int i = 1; i <= steps; i++)
	{
		MoveToPoint(line.GetPoint(stepSize * i));
	}
	MoveToPoint(target);
}

void RobotMover::DrawArcTo(Point end, Point center, ArcDir dir, unsigned int steps)
{
	ArcCalc arc(GetCurrentPoint(), end, center);

	for (unsigned int i = 1; i < steps; i++)
	{
		double delta = (double)i / steps;
		DrawLineTo(arc.GetPoint(delta, dir));
	}
	DrawLineTo(end);
}

void RobotMover::LiftPen()
{
	rhino.MoveMotor('F', -8);
}

void RobotMover::SetPen()
{
	rhino.MoveMotor('F', 8);
}
