// RobotBuilder Version: 1.5

#include "AutonomousMoveToZone.h"

#include "DelayCommand.h"
#include "DrivePID.h"
#include "ToggleFlapsCommand.h"
#include "ZeroElevator.h"

AutonomousMoveToZone::AutonomousMoveToZone() {
	printf("AutonomousMoveToZone constructed\n");
	//AddParallel(new ZeroElevator());
	AddParallel(new DrivePID(106.0, 106.0));

}
