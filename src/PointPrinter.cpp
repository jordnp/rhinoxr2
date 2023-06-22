#include "PointPrinter.h"

#include <cstdio>
#include <cmath>

#include "Line.h"

PointPrinter::PointPrinter()
{
	fopen_s(&xf, "x.txt", "w");
	fopen_s(&yf, "y.txt", "w");
}

PointPrinter::~PointPrinter()
{
	fclose(xf);
	fclose(yf);
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

Point PointPrinter::GetCurrentPoint()
{
	return pos;
}

void PointPrinter::MoveToPoint(Point target)
{
	//printf("MoveToPoint({ %0.2f, %0.2f })\n", target.x, target.y);
	fprintf(xf, "%0.2f\n", target.x);
	fprintf(yf, "%0.2f\n", target.y);
	pos = target;
}

void PointPrinter::DrawLineTo(Point target)
{
	Line line(GetCurrentPoint(), target);
	/*
	double stepSize = 1;
	int steps = int(line.GetLength() / stepSize);
	for (int i = 1; i <= steps; i++)
	{
		MoveToPoint(line.GetPoint(stepSize * i));
	}*/
	MoveToPoint(target);
}

void PointPrinter::DrawArcTo(Point end, Point center, ArcDir dir, unsigned int steps)
{
	printf("DrawArcTo({ %0.2f, %0.2f }, { %0.2f, %0.2f }, %d)\n", end.x, end.y, center.x, center.y, steps);
	ArcCalc arc(GetCurrentPoint(), end, center);

	for (unsigned int i = 1; i < steps; i++)
	{
		double delta = (double)i / steps;
		DrawLineTo(arc.GetPoint(delta, dir));
	}
	DrawLineTo(end);
}

void PointPrinter::LiftPen()
{
	
}

void PointPrinter::SetPen()
{
	
}
