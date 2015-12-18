/*
 * AutonomousCommandYellowTote.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: Ligerbots
 */



#include "AutonomousCommand1Tote.h"

#include "DelayCommand.h"
#include "ToggleFlapsCommand.h"
#include "PositionElevator.h"
#include "ZeroElevator.h"
#include "../RobotMap.h"
#include "Turn.h"
#include "DriveDistance.h"


AutonomousCommand1Tote::AutonomousCommand1Tote() {
	printf("AutonomousCommand1Can1Tote constructed\n");

	AddSequential(new ZeroElevator());				// make sure elevator is zero'd
	AddSequential(new ToggleFlapsCommand(1)); 			// make sure flaps are closed
	AddSequential(new PositionElevator(1, false, 0.9)); // move tote up to driving position
	AddSequential(new Turn(RobotMap::ninetyDegreeTurn, -RobotMap::ninetyDegreeTurn)); // turn right
	AddSequential(new DelayCommand(0.5));
	AddSequential(new DriveDistance(106.0, 106.0)); 			// and drive off into the sunset..
	AddSequential(new PositionElevator(-1, false)); // move tote to floor
}

