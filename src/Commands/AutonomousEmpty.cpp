// RobotBuilder Version: 1.5

#include "AutonomousEmpty.h"

#include "DelayCommand.h"

AutonomousEmpty::AutonomousEmpty() {
	printf("AutonomousEmpty constructed\n");
	AddSequential(new DelayCommand(0.5));
}
