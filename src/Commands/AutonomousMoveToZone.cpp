// RobotBuilder Version: 1.5

#include "AutonomousMoveToZone.h"

AutonomousMoveToZone::AutonomousMoveToZone() {
	AddSequential(Robot::oi->drive100);
}
