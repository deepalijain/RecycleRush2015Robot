
#pragma once

#include "Commands/Subsystem.h"
#include "../Robot.h"

class PositionElevator: public Command {
public:
	PositionElevator(int n);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	static void MoveElevatorUpdateParams();

	static double ticksPerRotation;
	static double m_curPos; //our position in tote counts

private:
	bool firstTime;

	// m_n tells us which variant of PositionElevator we are:
	//  0 - hold position (using PID control)
	//  1 - elevator up command (one floor per press)
	// -1 - elevator down command (one floor per press)
	int m_n;

	// tergetFloor is how we keep track of multiple presses
	// for each press targetFloor += m_n
	static int targetFloor;

	static double m_startPos;
	static double m_targetPos;
	static double encoderPos;
	static double inchesPerTote;

	static double wheelDiameter;
	static double inchesPerRotation;
	static double ticksPerInch;
	static double ticksPerTote;
	static double elevatorSpeed;
};


