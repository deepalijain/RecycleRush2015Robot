// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Delay.h"

Delay::Delay(double time) : delayPeriod(time) {

}

// Called just before this Command runs the first time
void Delay::Initialize() {
	printf("Delay init'd for %1.f seconds\n", delayPeriod);
	ticks = 0;
}

// Called repeatedly when this Command is scheduled to run
void Delay::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool Delay::IsFinished() {
	return (ticks++*50.0 > delayPeriod);

}

// Called once after isFinished returns true
void Delay::End() {
	printf("Delay Done\n");
	ticks = 0;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Delay::Interrupted() {

}
