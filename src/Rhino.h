#pragma once

#include "SerialPort.h"

// Class to connect and control a Rhino XR-2.
// Connects via serial port, disconnects thru destructor.
// Only handles control of individual motors.
// The Rhino XR, and this class, do not remember their position or angles.
// See RobotMover for an abstraction that handles moving the arm to desired positions.
class Rhino
{

public:
	SerialPort robo;
	// Connects to the serial port.
	Rhino();
	// Disconnects the serial port.
	~Rhino();

	// Move the given motor by the given amount of 'ticks'.
	// Ticks can be negative.
	// Due to software limitations, the Rhino can only move by a limited amount of ticks at a time.
	// This function will split the movement into multiple steps if necessary.
	//
	// Valid motors:
	// 	 C: Wrist flex
	//   D: Forearm
	//   E: Shoulder
	//   F: Waist (!!!: 1 tick for F motor = .14 deg, not .12 like the above)
	void MoveMotor(char c, int ticks);

	// Pause execution until the motor is done moving.
	void AwaitMotor(char c);
};
