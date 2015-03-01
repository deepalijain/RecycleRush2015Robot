// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "DrivePID.h"
#include "../Robot.h"
#include "../Subsystems/Parameters.h"

DrivePID::DrivePID() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveSubsystem);
	isFinished = false;
	firstTime = true;
	printf("drivePID constructed.\n");
}

// Called just before this Command runs the first time
void DrivePID::Initialize() {
	SetTimeout(15000);  // set 15 second timeout. Good enough?
	Robot::parameters->UpdateDrivePIDParams();
	double distance = Parameters::drivePIDDistance;
	Robot::driveSubsystem->SetPIDDistance(double(distance), double(distance));
	printf("Drive PID Initialized, ticks=%1.0f.\n", distance);
}

// Called repeatedly when this Command is scheduled to run
void DrivePID::Execute(){
}

// Make this return true when this Command no longer needs to run execute()
bool DrivePID::IsFinished() {
	double y = Robot::oi->joystick1->GetY();
	double x = Robot::oi->joystick1->GetRawAxis(4);
	if(fabs(y) > 0.1 || fabs(x) > 0.1)
	{
		printf("Drive PID terminated y=%f, x=%f.\n", y, x);
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void DrivePID::End() {
	RobotMap::driveBackLeft->SetControlMode(CANSpeedController::kPercentVbus);
	RobotMap::driveBackRight->SetControlMode(CANSpeedController::kPercentVbus);

	Robot::driveCommand->Start();

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DrivePID::Interrupted() {
	End();
}
