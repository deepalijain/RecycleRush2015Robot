// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "DriveSubsystem.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "../Commands/DriveCommand.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

static double driveP;
static double driveI;
static double driveD;
static double driveF;


DriveSubsystem::DriveSubsystem() : Subsystem("DriveSubsystem") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	lFront = RobotMap::driveFrontLeft;
	rFront = RobotMap::driveFrontRight;
	robotDrive = RobotMap::driveSubsystem;
	backLeftMotor = RobotMap::driveBackLeft;
	backRightMotor = RobotMap::driveBackRight;

	RobotMap::driveBackLeft->SetPosition(0.0);
	RobotMap::driveBackLeft->SetFeedbackDevice(CANTalon::QuadEncoder);
	RobotMap::driveBackLeft->SetSensorDirection(true);
	RobotMap::driveBackLeft->SetCloseLoopRampRate(.05);

	RobotMap::driveBackRight->SetPosition(0.0);
	RobotMap::driveBackRight->SetFeedbackDevice(CANTalon::QuadEncoder);
	RobotMap::driveBackRight->SetSensorDirection(true);
	RobotMap::driveBackRight->SetCloseLoopRampRate(.05);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}
    
void DriveSubsystem::SetPIDDistance( double left, double right)
{
	driveP = SmartDashboard::GetNumber("driveP");
	driveI = SmartDashboard::GetNumber("driveI");
	driveD = SmartDashboard::GetNumber("driveD");
	driveF = SmartDashboard::GetNumber("driveF");

	RobotMap::driveBackLeft->SetControlMode(CANSpeedController::kPosition);
	RobotMap::driveBackLeft->SetPID(driveP,driveI,driveD,driveF);
	RobotMap::driveBackLeft->ClearIaccum();

	printf("PID Left params distance=%1.2f, driveP=%1.3f, driveI=%1.3f, driveD=%1.3f, driveF=%1.3f.\n",
			-left, driveP, driveI, driveD, driveF);

	RobotMap::driveBackRight->SetControlMode(CANSpeedController::kPosition);
	RobotMap::driveBackRight->SetPID(driveP,driveI,driveD,driveF);
	RobotMap::driveBackRight->ClearIaccum();

	printf("PID Right params distance=%1.2f, driveP=%1.3f, driveI=%1.3f, driveD=%1.3f, driveF=%1.3f.\n",
			right, driveP, driveI, driveD, driveF);

	RobotMap::driveBackLeft->Set(-left);

	RobotMap::driveBackRight->Set(right);

}

void DriveSubsystem::DriveJoysticks(double y, double x)
{
	robotDrive->ArcadeDrive(y,x);
}

void DriveSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new DriveCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

double DriveSubsystem::GetLeftEncoderPosition() {
	// Set the default command for a subsystem here.
	return ((CANTalon*) backLeftMotor)->GetEncPosition();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

double DriveSubsystem::GetRightEncoderPosition() {
	// Set the default command for a subsystem here.
	return ((CANTalon*) backRightMotor)->GetEncPosition();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


