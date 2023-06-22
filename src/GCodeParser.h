#pragma once

// for size_t
#include <cstddef>

enum class GCodeInstrType
{
	Move,   // G00
	Line,   // G01
	ArcCW,  // G02
	ArcCCW, // G03
	Eof,    // No more instructions!
};

struct GCodeInstr
{
	GCodeInstrType type;
	double x, y, i, j;
};

struct GCodeVar
{
	char c;
	double val;
};

template<typename T>
struct Option
{
	T value;
	bool hasValue;
};

struct Instr
{
	int gcode;
	Option<double> x, y, i, j;
};

class GCodeParser
{
	bool ownsSrc = false;
	const char* src = nullptr;
	double x = 0, y = 0, i = 0, j = 0;
	size_t index = 0;
	double lastX = 0, lastY = 0;
public:
	static GCodeParser FromFile(const char *path);
	static GCodeParser FromText(const char *src);

	GCodeInstr ParseLine();

private:
	void SkipWhitespace();
	int ExpectG();
	double ReadDouble();
	void ReadVars();
	void ExpectEndOfLine();
	Instr NextInstr();
};
