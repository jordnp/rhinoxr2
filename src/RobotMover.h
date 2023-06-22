#pragma once

#include "Rhino.h"
#include "IKArm.h"
#include "Arc.h"

// Abstraction class that handles moving the robot.
// Assumes the Rhino to be set at 90 deg angles.
// To save yourself some manual adjustment, move the Rhino to (9, 9) at
// the end of your program.
class RobotMover
{
    Rhino rhino;

    // The Rhino arm segments are about 9 inches each
    IKArm ikCalculator = { 9, 9 };

    // 750 ticks == DegToTicks(90), precisely.
    int ticks[2] = { 750, 750 };

public:
    // Current point, estimated based on current angles.
    Point GetCurrentPoint();

    AnglePair GetCurrentAngles();

    // Move directly to a point. Do not pass Go. Do not collect $200.
    // How exactly it gets there is up to fate.
    // Does not draw straight lines! Use `DrawLineTo()`
    void MoveToPoint(Point);

    // Draw a (mostly) straight line from the current position, to the given point.
    // Very slow operation.
    void DrawLineTo(Point);

    // Draw an arc from the current position to `end` point,
    // centered on the "center" point, going either Clockwise
    // or Counter-Clockwise based on `dir`. The arc will be split
    // into `steps` segments connected by straight lines.
    // If the end point cannot be reached given the center point,
    // the program will exit with code 1. //TODO: nicer way to fail
    void DrawArcTo(Point end, Point center, ArcDir dir, unsigned int steps);

    // Move the pen up from a surface (twist the waist away from the board)
    void LiftPen();

    // Put the pen back after calling LiftPen()
    void SetPen();
};

