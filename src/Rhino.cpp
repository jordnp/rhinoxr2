#include "Rhino.h"

#include "common.h"

#include <iostream>
#include <cmath>
#include <string>
#include <windows.h>
#include <stdio.h>
using namespace std;

Rhino::Rhino()
{
	bool success = robo.Connect("COM1", 9600, SerialParity::Even);
	if (!success)
	{
		fprintf(stderr, "Failed to connect to serial port. Proceeding anyway!\n");
	}
}

Rhino::~Rhino()
{
	robo.Disconnect();
}

//TODO: implement (see '?' command in manual)
// Pause execution until the motor is done moving.
void Rhino::AwaitMotor(char motor)
{
	Sleep(100);
}

void Rhino::MoveMotor(char motor, int distance)
{
	const int step_size = 30;

	string cmd_root;
	cmd_root += motor;
	cmd_root += distance > 0 ? '+' : '-';

	string step_cmd = cmd_root + to_string(abs(step_size));

	int steps = abs(distance) / step_size;
	for (int i = 0; i < steps; i++)
	{
		Sleep(120);
		robo << step_cmd.c_str();
		Sleep(120);
	}

	int remainder = abs(distance) % step_size;
	if (remainder != 0)
	{
		Sleep(120);
		string remainder_cmd = cmd_root + to_string(remainder);
		robo << remainder_cmd.c_str();
		Sleep(120);
	}
}
