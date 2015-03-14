// RobotBuilder Version: 1.5
//

#include "AutonomousCommand1Can.h"
#include "ToggleFlapsCommand.h"
#include "PositionElevator.h"
#include "ZeroElevator.h"


AutonomousCommand1Can::AutonomousCommand1Can() {
	printf("AutonomousCommand1Can constructed\n");
	AddSequential(new ZeroElevator());
	AddSequential(new ToggleFlapsCommand(-1)); 	// make sure flaps are closed
	AddSequential(new PositionElevator(1, true));
}
