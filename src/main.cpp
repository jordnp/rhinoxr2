// Jordan Potter, 2023, COMSC-11

#include "RobotMover.h"
#include "GCodeParser.h"
#include "PointPrinter.h"

#include <cmath>

#define OFFSX 5
#define OFFSY 12
#define SCALE 0.05
#define ARC_SEGMENTS 3
#define GCODE_FILE "samples/turt_gcode.txt"

// Good offset and scale values for some provided G-Code files:
// turt_gcode.txt: X5 Y12 S0.05

// Verify that, with these settings, the GCode will not exceed the Rhino's range.
void VerifyGCodeInRange(const char *path, double offsx, double offsy, double scale)
{
	GCodeParser parser = GCodeParser::FromFile(path);
	for (;;)
	{
		GCodeInstr i = parser.ParseLine();
		if (i.type == GCodeInstrType::Eof)
			break;

		i.x *= scale;
		i.y *= scale;
		i.i *= scale;
		i.j *= scale;

		i.x += offsx;
		i.y += offsy;
		i.i += offsx;
		i.j += offsy;
		if (sqrt(i.x*i.x + i.y*i.y) >= 18)
		{
			printf("Input exceeds maximum range. Adjust the OFFSX/Y and SCALE settings.\n");
			exit(1);
		}
	}
}

int main()
{
	VerifyGCodeInRange(GCODE_FILE, OFFSX, OFFSY, SCALE);
	RobotMover robo;
	GCodeParser parser = GCodeParser::FromFile(GCODE_FILE);
	for (;;)
	{
		GCodeInstr i = parser.ParseLine();
		if (i.type == GCodeInstrType::Eof)
			break;
		i.x *= SCALE;
		i.y *= SCALE;
		i.i *= SCALE;
		i.j *= SCALE;

		i.x += OFFSX;
		i.y += OFFSY;
		i.i += OFFSX;
		i.j += OFFSY;

		printf("G0%d X%0.2f  Y%0.2f", i.type, i.x, i.y);
		if (i.type == GCodeInstrType::ArcCW || i.type == GCodeInstrType::ArcCCW)
			printf("  I%0.2f  J%0.2f", i.i, i.j);
		putchar('\n');

		switch (i.type)
		{
		case GCodeInstrType::Move:
			robo.LiftPen();
			robo.MoveToPoint({ i.x, i.y });
			robo.SetPen();
			break;
		case GCodeInstrType::Line:
			robo.DrawLineTo({ i.x, i.y });
			break;
		case GCodeInstrType::ArcCW:
			robo.DrawArcTo({ i.x, i.y }, { i.i, i.j }, ArcDir::CW, ARC_SEGMENTS);
			break;
		case GCodeInstrType::ArcCCW:
			robo.DrawArcTo({ i.x, i.y }, { i.i, i.j }, ArcDir::CCW, ARC_SEGMENTS);
			break;
		case GCodeInstrType::Eof:
			break; // Handled at the start of this loop
		}
	}

	// Reset to origin.
	robo.LiftPen();
	robo.MoveToPoint({ 9, 9 });
	robo.SetPen();
	return 0;
}
