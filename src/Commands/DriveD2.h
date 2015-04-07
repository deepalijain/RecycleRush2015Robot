#pragma once

#include "../Robot.h"
#include "DriveCommand.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class DriveD2: public Command {
private:
	double m_distL;
	double m_distR;
	double m_direction;		// 1.0 for forward, -1.0 for backward
	double m_ratio;			// the ratio of the left to the right
							// 1.0 is both sides the same
							// -1.0 would be a 90 degree turn
	double m_encoderInitialL;
	double m_encoderInitialR;
	bool m_isCommandDone;
	double m_remainingDistance;
	// maxDecelDisatnce is the distance travelled while decelerating at the
	// maximum rate based on rateStep
	double m_maxDecelDistance;
	double m_rateLeft;
	double m_rateRight;
	double m_maxRate = 0.6;
	// Make sure to disable the VoltageRampRate on the drive Talons
	// Use this to step up the voltage for acceleration and deceleration
	// Using the Talon VoltageRampRate interferes with this control loop
	double m_rateStep = .02;
	double m_initialRate = 0.15; 	// overcome intertia
	// If we're off by 1 inch, this is how much we increase the right side voltage
	double m_rateScale = 0.04;
	// timeToStop is how long it takes to get to 0 volts from current rate at rateStep per cycle
	double m_timeToStop = 0.0;

	int m_timeTicks = 0;
	DriveSubsystem *driveSubsystem;

public:
	DriveD2(double distL, double distR);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	double distanceTravelledL;
	double distanceTravelledR;
};

