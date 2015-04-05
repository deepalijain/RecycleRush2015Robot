/*
 * DriveDistanceCommand.h
 *
 *  Created on: Jan 29, 2015
 *      Author: Ligerbots
 */

#ifndef SRC_COMMANDS_DRIVEDISTANCECOMMAND_H_
#define SRC_COMMANDS_DRIVEDISTANCECOMMAND_H_





#endif /* SRC_COMMANDS_DRIVEDISTANCECOMMAND_H_ */
// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef DRIVEDISTANCECOMMAND_H
#define DRIVEDISTANCECOMMAND_H



#include "../Robot.h"
#include "DriveCommand.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class DriveDistance: public Command {
private:
	double _distL;
	double _distR;
	bool isCommandDone;
	double remainingDistance;
	double rateLeft = 0.0;
	double rateRight = 0.0;
	double maxRate = 0.6;
	// Just make rateStep 1.0 and let the voltage ramp rate handle it.
	//double voltageStep = maxVoltage/(secondsToMax/timeStep);
	double rateStep = .02;
	double initialRate = 0.15; 	// overcome intertia
	double wheelDiam;
	double distancePerRev;
	double inchesPerTick;
	// If we're off by 1 inch, increase the voltage by 0.05
	double rateScale = 0.04;
	int ticks = 0;
	DriveSubsystem *driveSubsystem;
public:
	DriveDistance(double distL, double distR);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	double distanceTravelledL;
	double distanceTravelledR;
};

#endif