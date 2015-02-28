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


#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "DriveCommand.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class DriveDistanceCommand: public Command {
private:
	float distance; // requested distance in inches
	bool isCommandDone;
	float distanceError;
	float voltageLeft = 0.0;
	float voltageRight = 0.0;
	float maxVoltage = 0.9;
	float timeStep = 0.02;
	float secondsToMax = 1.5;
	float voltageStep = maxVoltage/(secondsToMax/timeStep);
	// To do: change wheelDiam to 6.0 for production robot
	float wheelDiam = 4.0;
	float distancePerRev = 3.1416*wheelDiam;
	float inchesPerTick = distancePerRev/1024;
	// If we're off by 1 inch, increase the voltage by 0.05
	float voltageScale = 0.05;
public:
	DriveDistanceCommand(int dist);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	static float distanceTravelledL = 0.0;
	static float distanceTravelledR = 0.0;
};

#endif
