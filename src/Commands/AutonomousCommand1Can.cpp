// RobotBuilder Version: 1.5
//

#include "AutonomousCommand1Can.h"
#include "ToggleFlapsCommand.h"
#include "PositionElevator.h"
#include "ZeroElevator.h"
#include "Delay.h"


AutonomousCommand1Can::AutonomousCommand1Can() {
	printf("AutonomousCommand1Can constructed\n");

	AddSequential(new ToggleFlapsCommand(-1)); 	// make sure flaps are closed
	AddSequential(new PositionElevator(1, true));	// first call goes to "Driving position"
	AddSequential(new PositionElevator(1, true, 0.8));	// second call will raise it to can height
	AddSequential(new DrivePID(100.0, 100.0));
}
