// RobotBuilder Version: 1.5
//

#include "AutonomousCommand1Can.h"
#include "ToggleFlapsCommand.h"
#include "PositionElevator.h"
#include "ZeroElevator.h"


AutonomousCommand1Can::AutonomousCommand1Can() {
	// Need to go up twice to get a can

	// And now drive into Auto Zone
	// TODO: Need to pass in distance. Both sides should be the same
	// AddSequential(Robot::oi->drivePID);
}
