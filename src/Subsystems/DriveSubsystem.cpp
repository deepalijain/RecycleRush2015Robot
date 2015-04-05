// DriveSubsystem

#include "DriveSubsystem.h"
#include "../RobotMap.h"
#include "../Commands/DriveCommand.h"
#include "Parameters.h"

DriveSubsystem::DriveSubsystem() : Subsystem("DriveSubsystem") {
	lFront = RobotMap::driveFrontLeft;
	rFront = RobotMap::driveFrontRight;
	robotDrive = RobotMap::driveSubsystem;
	backLeftMotor = RobotMap::driveBackLeft;
	backRightMotor = RobotMap::driveBackRight;

	backLeftMotor->ClearError();
	backLeftMotor->SetPosition(0.0);
	backLeftMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	if (RobotMap::testBot) backLeftMotor->SetSensorDirection(true);

	backRightMotor->SetPosition(0.0);
	backRightMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	if (RobotMap::testBot) backRightMotor->SetSensorDirection(true);

	// Set the voltage ramp rate for both drive motors
	backLeftMotor->SetVoltageRampRate(Parameters::driveRampRate);
	backRightMotor->SetVoltageRampRate(Parameters::driveRampRate);
}
    
void DriveSubsystem::SetPIDDistance(double left, double right)
{
	double leftPosition = GetLeftEncoderPosition();
	double rightPosition = GetRightEncoderPosition();

	left = leftPosition - left;
	right += rightPosition;

	backLeftMotor->SetControlMode(CANSpeedController::kPosition);
	backLeftMotor->SetPID(Parameters::driveP,Parameters::driveI,
									Parameters::driveD,Parameters::driveF);
	backLeftMotor->SetIzone(Parameters::driveIZone);
	backLeftMotor->SetCloseLoopRampRate(Parameters::driveRampRate);
	backLeftMotor->ClearIaccum();

	printf("PID Left from=%1.0f, to=%1.2f, driveP=%1.3f, driveI=%1.3f, driveD=%1.3f, driveF=%1.3f.\n",
			leftPosition, left, Parameters::driveP, Parameters::driveI, Parameters::driveD, Parameters::driveF);

	backRightMotor->SetControlMode(CANSpeedController::kPosition);
	backRightMotor->SetPID(Parameters::driveP,Parameters::driveI,
									 Parameters::driveD,Parameters::driveF);
	backRightMotor->SetIzone(Parameters::driveIZone);
	backRightMotor->SetCloseLoopRampRate(Parameters::driveRampRate);
	backRightMotor->ClearIaccum();

	printf("PID Right from=%1.0f, to=%1.2f, driveP=%1.3f, driveI=%1.3f, driveD=%1.3f, driveF=%1.3f.\n",
			rightPosition, right, Parameters::driveP, Parameters::driveI, Parameters::driveD, Parameters::driveF);

	backLeftMotor->Set(left);
	backRightMotor->Set(right);

	previousClosedLoopError = 0.0;
	numberofsame = 0;

}

// if the last 8 closed loop errors (where each error is the sum of left + right)
// didn't change, then we can consider the PID loop to have completed its task
bool DriveSubsystem::IsFinished() {
	int left = abs(backLeftMotor->GetClosedLoopError());
	int right = abs(backRightMotor->GetClosedLoopError());

	int closedLoopError = left + right;
	if (previousClosedLoopError - closedLoopError < 3) {
		if (++numberofsame >= 8) return true;
	}
	else numberofsame = 0;
	previousClosedLoopError = closedLoopError;
	return false;
}

void DriveSubsystem::DriveJoysticks(double y, double x)
{
	robotDrive->ArcadeDrive(y,x);
}

void DriveSubsystem::InitDefaultCommand() {
	//SetDefaultCommand(Robot::driveCommand);
}

double DriveSubsystem::GetLeftEncoderPosition() {
	return backLeftMotor->GetPosition();
}

double DriveSubsystem::GetRightEncoderPosition() {
	return backRightMotor->GetPosition();
}

double DriveSubsystem::LeftTalonGet() {
	return backLeftMotor->Get();
}

double DriveSubsystem::RightTalonGet() {
	return backRightMotor->Get();
}

double DriveSubsystem::GetLeftSpeed() {
	// GetSpeed returns ticks per 100ms
	// ticks/100ms * 10 = ticks/sec
	// ticks/sec / ticks/inch = inches/sec
	return backLeftMotor->GetSpeed()*10.0*RobotMap::inchesPerTick;
}

double DriveSubsystem::GetRightSpeed() {
	// GetSpeed returns ticks per 100ms
	// ticks/100ms * 10 = ticks/sec
	// ticks/sec / ticks/inch = inches/sec
	return backRightMotor->GetSpeed()*10.0*RobotMap::inchesPerTick;
}


