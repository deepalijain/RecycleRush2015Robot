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
	printf("Drive elevator constructed.\n");

	maxSpeed = .7;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

// Called just before this Command runs the first time
void DriveElevator::Initialize() {
	printf("Drive elevator initialized.\n");
	if (!RobotMap::testBot) RobotMap::elevatorMotor1->SetControlMode(CANSpeedController::kPercentVbus);
}

// Called repeatedly when this Command is scheduled to run
void DriveElevator::Execute() {
	joystickup = maxSpeed*(Robot::oi->joystick1->GetRawAxis(3));
	joystickdown = maxSpeed*(Robot::oi->joystick1->GetRawAxis(2));
	if (RobotMap::testBot) {
		Robot::elevator->Move((joystickdown - joystickup)*Robot::elevator->ticksPerCycle);
	}
	else {
		// elevatorMotor1 is upside down and not invertable, not being a drive,
		// so we simply take the negative of what would be expected here
		Robot::elevator->elevatorMotor1->Set(joystickdown - joystickup);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DriveElevator::IsFinished() {
	// when our joystick inputs are close enough to zero, this command is done
	if (fabs(joystickup) < 0.1 && fabs(joystickdown) < 0.1)
	{
		printf("Elevator drive joystick input ended y=%f, x=%f.\n", joystickup, joystickdown);
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void DriveElevator::End() {
	// If the driver isn't actively moving the elevator, then use
	// the holdElevatorCommand to keep it in place.
	printf("Drive elevator ending, reverting to PID control.\n");
	// Max says this is wrong, I think it'll work for now:
	double curPos =  Robot::elevator->GetEncPosition();
	Robot::elevator->UpdateElevatorIndex();
	Robot::elevator->SetHeight(curPos);
	Robot::holdElevatorCommand->Start();
 }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveElevator::Interrupted() {

}
