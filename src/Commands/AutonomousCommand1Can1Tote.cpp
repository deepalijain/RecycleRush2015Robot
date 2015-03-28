// RobotBuilder Version: 1.5
//

#include "AutonomousCommand1Can1Tote.h"
#include "Delay.h"
#include "ToggleFlapsCommand.h"
#include "PositionElevator.h"
#include "ZeroElevator.h"


AutonomousCommand1Can1Tote::AutonomousCommand1Can1Tote() {
	printf("AutonomousCommand1Can1Tote constructed\n");
	AddSequential(new ZeroElevator());					// make sure elevator is zero'd
	//AddSequential(new ToggleFlapsCommand(1)); 			// make sure flaps are open for picking up can
	AddSequential(new PositionElevator(1, true, 1.0));	// pick up the can
	AddSequential(new Delay(0.5));
	AddSequential(new DrivePID(21.0, 21.0));
	AddSequential(new Delay(0.3));
	AddSequential(new PositionElevator(-1, true));		// put the can on the tote
	AddSequential(new PositionElevator(-1, false, 1.0));// move down to under the Tote
	AddSequential(new Delay(0.5));
	AddSequential(new ToggleFlapsCommand(1)); 			// make sure flaps are closed
	AddSequential(new PositionElevator(1, false, 0.9));	// pick up the Tote
	AddSequential(new Delay(0.8));
	AddSequential(new DrivePID(-ninetyDegreeTurn, ninetyDegreeTurn)); // turn left
	AddSequential(new Delay(0.3));
	AddSequential(new DrivePID(106.0, 106.0)); // and drive off into the sunset..
	AddSequential(new PositionElevator(-1, false));	// another for good measure..
	AddSequential(new ToggleFlapsCommand(-1));
}
