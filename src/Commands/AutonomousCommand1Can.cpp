// RobotBuilder Version: 1.5
//

#include "AutonomousCommand1Can.h"
#include "ToggleFlapsCommand.h"
#include "PositionElevator.h"
#include "ZeroElevator.h"
#include "Delay.h"


AutonomousCommand1Can::AutonomousCommand1Can() {
	printf("AutonomousCommand1Can constructed\n");

	AddSequential(new ZeroElevator());				// make sure elevator is zero'd
	AddSequential(new ToggleFlapsCommand(-1)); 		// make sure flaps are closed
	AddSequential(new PositionElevator(1, true, 0.8));	// raise it to can height
	AddSequential(new Delay(0.7));
	AddSequential(new DrivePID(-ninetyDegreeTurn, ninetyDegreeTurn)); // turn left
	AddSequential(new Delay(0.5));
	AddSequential(new DrivePID(106.0, 106.0));

	AddSequential(new PositionElevator(-1, true));	//hit the floor, hard!

}
