/*
 * AutonomousCommandYellowTote.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: Ligerbots
 */



#include "AutonomousCommandYellowTote.h"
#include "Delay.h"
#include "ToggleFlapsCommand.h"
#include "PositionElevator.h"
#include "ZeroElevator.h"


AutonomousCommand1Can1Tote::AutonomousCommand1Can1Tote() {
	printf("AutonomousCommand1Can1Tote constructed\n");
	// Need to go up twice to get a can
	//AddSequential(new ZeroElevator());
	AddSequential(new ToggleFlapsCommand(-1)); 	// make sure flaps are closed
	AddSequential(new PositionElevator(1, false)); // move tote up
	AddSequential(new Delay(1.5));
	AddSequential(new DrivePID(ninetyDegreeTurn, -ninetyDegreeTurn)); // turn left
	AddSequential(new DrivePID(100.0, 100.0)); // and drive off into the sunset..

}

