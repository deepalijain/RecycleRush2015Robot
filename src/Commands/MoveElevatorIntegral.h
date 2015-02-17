
#pragma once

#include "Commands/Subsystem.h"
#include "../Robot.h"

class MoveElevatorIntegral: public Command {
public:
	MoveElevatorIntegral(int);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	static void MoveElevatorUpdateParams(double wheelDiam);
	static double wheelDiameter;

private:
	bool firstTime;
	int m_n;		// number of positions to move (can be negative)
	int ticks;
	static double m_startPos;
	static double m_curPos;		// our position in tote counts
	static double m_targetPos;
	static double encoderPos;
	static double ticksPerRotation;
	static double inchesPerTote;

	static double inchesPerRotation;
	static double ticksPerInch;
	static double ticksPerTote;
	static double elevatorSpeed;
};


