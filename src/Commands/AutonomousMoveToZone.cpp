// RobotBuilder Version: 1.5

#include "AutonomousMoveToZone.h"
#include "Delay.h"
#include "DrivePID.h"
#include "ToggleFlapsCommand.h"

AutonomousMoveToZone::AutonomousMoveToZone() {
	printf("AutonomousMoveToZone constructed\n");
	//AddSequential(new DrivePID(100.0, 100.0));
	AddSequential(new ToggleFlapsCommand(1));
}
