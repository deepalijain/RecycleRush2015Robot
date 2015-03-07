// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

double elevatorP;
double elevatorI;
double elevatorD;
double elevatorF;
double elevatorRampRateCloseLoop;

#include "Elevator.h"
#include "../RobotMap.h"
#include "../Robot.h"

Elevator::Elevator() : Subsystem("Elevator") {
	wheelDiameter = 2.0; // starting guess

	ticksPerRotation = 1024.0;
	inchesPerTote = 12.1;
	inchesPerRotation = wheelDiameter * 3.14159;
	ticksPerInch = ticksPerRotation / inchesPerRotation;
	ticksPerTote = ticksPerInch * inchesPerTote;

	// This is for testBot only:
	// Simulate movement so a full tote's height takes about 2 seconds
	ticksPerCycle = ((ticksPerInch * inchesPerTote) / 50) / 2;

	elevatorMotor1 = RobotMap::elevatorMotor1;
	elevatorMotor2 = RobotMap::elevatorMotor2;
	elevatorMotor1->SetPosition(0.0);
	encoderPos = 0;	// test bot only, not worth if statement
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}
    
void Elevator::SetHeight(double height)
{
	Robot::parameters->UpdateElevatorPIDParams();
	elevatorP = SmartDashboard::GetNumber("elevatorP");
	elevatorI = SmartDashboard::GetNumber("elevatorI");
	elevatorD = SmartDashboard::GetNumber("elevatorD");
	elevatorF = SmartDashboard::GetNumber("elevatorF");
	elevatorRampRateCloseLoop = SmartDashboard::GetNumber("ElClosedLoopRR");

	RobotMap::elevatorMotor1->SetVoltageRampRate(elevatorRampRateCloseLoop);
	RobotMap::elevatorMotor1->SetPID(elevatorP,elevatorI,elevatorD,elevatorF);
	RobotMap::elevatorMotor1->ClearIaccum();

	printf("PID Elevator params distance=%1.2f, elevatorP=%1.3f, elevatorI=%1.3f, elevatorD=%1.3f, elevatorF=%1.3f.\n",
			height, elevatorP, elevatorI, elevatorD, elevatorF);

	RobotMap::elevatorMotor1->Set(height);

}

// Only valid on the test bot. On the real elevator, we actually move
void Elevator::Move(double n) {
	// On the production bot, nothing's here. The Talon's PID loop is doing all the work!
	if (RobotMap::testBot) {
		if (encoderPos >= 0) {
			encoderPos += n;
			if (encoderPos < 0) encoderPos = 0;
		}
	}
}


void Elevator::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// presume Elevator starts at position zero. We need to actually
	// ensure this elsewhere
	if (!RobotMap::testBot) {
		SetDefaultCommand(Robot::holdElevatorCommand);
	}
}

double Elevator::GetPosition() {
	if (RobotMap::testBot) return encoderPos;
	return elevatorMotor1->Get();
}
