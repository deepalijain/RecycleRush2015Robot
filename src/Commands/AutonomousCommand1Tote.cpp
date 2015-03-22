/*
 * AutonomousCommandYellowTote.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: Ligerbots
 */



#include "AutonomousCommand1Tote.h"

#include "Delay.h"
#include "ToggleFlapsCommand.h"
#include "PositionElevator.h"
#include "ZeroElevator.h"


AutonomousCommand1Tote::AutonomousCommand1Tote() {
	printf("AutonomousCommand1Can1Tote constructed\n");

	AddSequential(new ZeroElevator());				// make sure elevator is zero'd
	AddSequential(new ToggleFlapsCommand(1)); 			// make sure flaps are closed
	AddSequential(new PositionElevator(1, false, 0.9)); // move tote up to driving position
	AddSequential(new DrivePID(ninetyDegreeTurn, -ninetyDegreeTurn)); // turn right
	AddSequential(new Delay(1.0));
	AddSequential(new DrivePID(100.0, 100.0)); 			// and drive off into the sunset..

}

