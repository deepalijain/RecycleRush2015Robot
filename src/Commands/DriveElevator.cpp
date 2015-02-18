// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "DriveElevator.h"

DriveElevator::DriveElevator() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::elevator);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

// Called just before this Command runs the first time
void DriveElevator::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void DriveElevator::Execute() {
	float up = Robot::oi->joystick1->GetRawAxis(3);
	float down = Robot::oi->joystick1->GetRawAxis(2);
	//pickupMotor1 is upside down and not invertable, not being in a drive,
	//so we simply take the negative of what would be expected here
	Robot::elevator->elevatorMotor1->Set(down - up);
	SmartDashboard::PutNumber("pickupMotor set to", down-up);
	
}

// Make this return true when this Command no longer needs to run execute()
bool DriveElevator::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveElevator::End() {

 }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveElevator::Interrupted() {

}
