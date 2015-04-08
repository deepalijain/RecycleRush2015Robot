#include "Turn.h"
#include "../Subsystems/Parameters.h"

Turn::Turn(double left, double right) : m_left(left), m_right(right) {
	Requires(Robot::driveSubsystem);
	m_driveSubsystem = Robot::driveSubsystem;
	printf("Turn constructed for left = %1.2f, right=%1.2f.\n", m_left, m_right);
}

// Called just before this Command runs the first time
void Turn::Initialize() {
	SetInterruptible(false);
	m_startPosition = RobotMap::driveBackLeft->GetPosition();
	printf("Turn initialized for left = %1.2f, right=%1.2f.\n", m_left, m_right);
	// Disable the voltage ramp rate
	RobotMap::driveBackLeft->SetVoltageRampRate(0.0);
	RobotMap::driveBackRight->SetVoltageRampRate(0.0);
}

// Called repeatedly when this Command is scheduled to run
void Turn::Execute() {
	// For left side, positive is backward.
	// The testBot needs a little more power to overcome higher drive train friction
	double leftVbus = (m_left >= 0.0 ? 0.4 : -0.4) * (RobotMap::testBot ? 1.25 : 1.0);
	double rightVbus = (m_right >= 0.0 ? 0.4 : -0.4) * (RobotMap::testBot ? 1.25 : 1.0);
	m_driveSubsystem->robotDrive->TankDrive(-leftVbus, -rightVbus, false);
	double ticksTraveled = RobotMap::driveBackLeft->GetPosition() - m_startPosition;
	if (Robot::Ticks%5) {
		printf("Turn: ticks=%1.2f, inches=%1.2f, leftVbus=%1.2f, rightVbus=%1.2f, remaining=%1.2f.\n",
				ticksTraveled, ticksTraveled*RobotMap::inchesPerTick, leftVbus, rightVbus,
				fabs(m_left) - fabs(ticksTraveled*RobotMap::inchesPerTick));
	}

}

// Make this return true when this Command no longer needs to run execute()
bool Turn::IsFinished() {
	double ticksTraveled = RobotMap::driveBackLeft->GetPosition() - m_startPosition;
	return fabs(ticksTraveled)*RobotMap::inchesPerTick > fabs(m_left);
}

// Called once after isFinished returns true
void Turn::End() {
	m_driveSubsystem->robotDrive->ArcadeDrive(0, 0, true);
	// Set the voltage ramp rate for both drive motors
	RobotMap::driveBackLeft->SetVoltageRampRate(Parameters::driveRampRate);
	RobotMap::driveBackRight->SetVoltageRampRate(Parameters::driveRampRate);

	// Can't do this and expect to be part of a command group
	//((DriveCommand *)Robot::driveCommand)->Start();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Turn::Interrupted() {
	End();
	printf("TurnLeft INTERRUPTED at %d\n", Robot::Ticks);
}
