// RobotBuilder Version: 1.5

#include "AutonomousEmpty.h"
#include "Delay.h"

AutonomousEmpty::AutonomousEmpty() {
	printf("AutonomousEmpty constructed\n");
	AddSequential(new Delay(0.5));
}
