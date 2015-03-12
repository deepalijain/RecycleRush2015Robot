// RobotBuilder Version: 1.5
//

#include "AutonomousCommand1Can.h"
AutonomousCommand1Can::AutonomousCommand1Can() {
	// Need to go up twice to get a can
	AddSequential(Robot::oi->canUp);
	//AddSequential(Robot::oi->toteUp);
	// TODO: DrivePID only goes straight right now. We need to be able to pass in values
	// but I want to coordinate with Charles
	AddSequential(Robot::oi->drive100);
	// And now drive into Auto Zone
	// TODO: Need to pass in distance. Both sides should be the same
	// AddSequential(Robot::oi->drivePID);
}
