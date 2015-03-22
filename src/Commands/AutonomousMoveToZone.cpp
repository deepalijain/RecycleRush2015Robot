// RobotBuilder Version: 1.5

#include "AutonomousMoveToZone.h"
#include "Delay.h"
#include "DrivePID.h"
#include "ToggleFlapsCommand.h"
#include "ZeroElevator.h"

AutonomousMoveToZone::AutonomousMoveToZone() {
	printf("AutonomousMoveToZone constructed\n");
	AddParallel(new DrivePID(100.0, 100.0));
	AddParallel(new ZeroElevator());
}
