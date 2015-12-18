
#include "../Robot.h"
#include "RestoreDrive.h"

RestoreDrive::RestoreDrive() {
	Requires(Robot::driveSubsystem);

	printf("RestoreDrive constructed.\n");
}

// Called just before this Command runs the first time
void RestoreDrive::Initialize() {
	SetInterruptible(false);
}

// Called repeatedly when this Command is scheduled to run
void RestoreDrive::Execute() {
}

// Make this reRestoreDrive true when this Command no longer needs to run execute()
bool RestoreDrive::IsFinished() {
	return true;
}

// Called once after isFinished reRestoreDrives true
void RestoreDrive::End() {
	Robot::driveCommand->Start();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RestoreDrive::Interrupted() {
	End();
	printf("RestoreDriveLeft INTERRUPTED at %d\n", Robot::Ticks);
}
