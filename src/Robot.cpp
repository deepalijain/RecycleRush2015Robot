// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "Robot.h"
#include <iostream>
#include "Commands/DriveCommand.h"
#include "Commands/DriveElevator.h"
#include "Commands/PositionElevator.h"
#include "Commands/DrivePID.h"

DriveSubsystem *Robot::driveSubsystem = 0;
Elevator *Robot::elevator = 0;
ArmFlaps *Robot::armFlaps = 0;
TotePusher *Robot::totePusher = 0;
OI *Robot::oi = 0;
Command *Robot::driveCommand = 0;
Command *Robot::driveElevatorCommand = 0;
Command *Robot::holdElevatorCommand = 0;
Parameters *Robot::parameters = 0;

int Ticks = 0;

void Robot::RobotInit() {
	// Get our save parameters before we do anything else
	parameters = new Parameters();
	parameters->GetParams();

	RobotMap::init();
	driveSubsystem = new DriveSubsystem();
	elevator = new Elevator();
	armFlaps = new ArmFlaps;
	totePusher = new TotePusher;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi = new OI();
	driveCommand = new DriveCommand();
	// PositionElevator(0) means maintain current position, which is why we
	// use the word "hold" here. Other instances of positionElevator have
	// parameters of 1 or -1
	holdElevatorCommand = new PositionElevator(0);
	driveElevatorCommand = new DriveElevator();

	lw = LiveWindow::GetInstance();

	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

  }

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
	UpdateDashboardPeriodic();
}

void Robot::AutonomousInit() {
	RobotMap::driveBackLeft->SetPosition(0.0);

	if (autonomousCommand != NULL)
		autonomousCommand->Start();

}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	UpdateDashboardPeriodic();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to 
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand != NULL)
		autonomousCommand->Cancel();

	RobotMap::armFlapSolenoid->Set(DoubleSolenoid::kOff);
	RobotMap::shifterSolenoid->Set(DoubleSolenoid::kOff);
	RobotMap::totePusherSolenoid->Set(DoubleSolenoid::kOff);
	// It seems that we need a Set to confirm the control mode or else it reverts
}


void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	UpdateDashboardPeriodic();
}

void Robot::TestPeriodic() {
	lw->Run();
}
void Robot::UpdateDashboardPeriodic() {

	// Do this every 1/10th of a second, not more often for efficiency
	if (Ticks++%5==0) {
//		Compressor* wC = RobotMap::workingCompressor;
//		if (NULL!=wC) {
//			SmartDashboard::PutBoolean("CompEnabled", wC->Enabled());
//			SmartDashboard::PutBoolean("CompSwitch", wC->GetPressureSwitchValue());
//			SmartDashboard::PutNumber("CompCurrent", wC->GetCompressorCurrent());
//		}

		parameters->ShowPIDParams();
		SmartDashboard::PutNumber("CAN Front Left Fault", RobotMap::driveFrontLeft->GetFaults());
		SmartDashboard::PutNumber("Left Encoder Position", Robot::driveSubsystem->GetLeftEncoderPosition());
		SmartDashboard::PutNumber("Right Encoder Position", Robot::driveSubsystem->GetRightEncoderPosition());
		SmartDashboard::PutNumber("DrivePID Left  Error",RobotMap::driveBackLeft->GetClosedLoopError());
		SmartDashboard::PutNumber("DrivePID Right Error",RobotMap::driveBackRight->GetClosedLoopError());

		SmartDashboard::PutNumber("Elevator Encoder Position", Robot::elevator->GetEncoderPosition());
		SmartDashboard::PutNumber("Elevator PID Error", RobotMap::elevatorMotor1->GetClosedLoopError());
		SmartDashboard::PutNumber("Elevator Position", Robot::elevator->GetPosition());

		RobotMap::Ct->UpdateDashboard();

#ifdef sensors
		if (NULL!=RobotMap::distanceSensor) {
			SmartDashboard::PutNumber("DistanceSensorVoltage", RobotMap::distanceSensor->GetVoltage());  // THIS IS THE LINE THAT IS FAILING!!
		} else {
			printf("distanceSensor pointer NULL\n");
		}
		if (NULL!=RobotMap::colorSensor) {
			SmartDashboard::PutNumber("ColorSensorVoltage", RobotMap::colorSensor->Get());  // THIS IS THE LINE THAT IS FAILING!!
		} else {
			printf("colorSensor pointer NULL\n");
		}
#endif
	}
}


START_ROBOT_CLASS(Robot);
