// RobotBuilder Version: 1.5
//

#include "AutonomousCommand1Can1Tote.h"
#include "Delay.h"
#include "ToggleFlapsCommand.h"
#include "PositionElevator.h"

AutonomousCommand1Can1Tote::AutonomousCommand1Can1Tote() {
	// Need to go up twice to get a can
	AddSequential(new ToggleFlapsCommand(-1)); 	// make sure flaps are closed
	AddSequential(Robot::oi->canUp);
	AddSequential(new Delay(1.5));
	AddSequential(new DrivePID(21.0, 21.0));

	AddSequential(Robot::oi->canDown);	// put the can on the tote
	AddSequential(Robot::oi->toteDown);	// move down to under the Tote
	AddSequential(new Delay(1.5));
	AddSequential(Robot::oi->toteUp);	// pick up the Tote
	AddSequential(Robot::oi->turnLeft); // turn left
	AddSequential(Robot::oi->drive100); // and drive off into the sunset..
}
