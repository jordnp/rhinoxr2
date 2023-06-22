#pragma once

#include "IKArm.h"
#include "Arc.h"
#include <cstdio>


class PointPrinter
{
    IKArm ikCalculator = { 9, 9 };
    Point pos = { 0, 0 };
    FILE* xf, * yf;
public:
    PointPrinter();
    ~PointPrinter();
    Point GetCurrentPoint();
    void MoveToPoint(Point);
    void DrawLineTo(Point);
    void DrawArcTo(Point end, Point center, ArcDir dir, unsigned int steps);
    void LiftPen();
    void SetPen();
};

