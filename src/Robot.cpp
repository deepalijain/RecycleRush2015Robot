// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It was full of non-buildable code
// and stupd

#include "Robot.h"
#include <iostream>
#include <exception>
#include "Commands/DriveCommand.h"
#include "Commands/DriveElevator.h"
#include "Commands/DriveDistanceCommand.h"
#include "Commands/PositionElevator.h"
#include "Commands/DrivePID.h"
#include "Commands/ZeroElevator.h"
#include "Commands/AutonomousCommand1Can.h"
#include "Commands/AutonomousMoveToZone.h"
#include "Subsystems/Camera.h"

DriveSubsystem *Robot::driveSubsystem = 0;
Elevator *Robot::elevator = 0;
ArmFlaps *Robot::armFlaps = 0;
TotePusher *Robot::totePusher = 0;
CompressorSubsystem *Robot::compressorSubsystem = NULL;
OI *Robot::oi = 0;
Command *Robot::driveCommand = 0;
Command *Robot::driveElevatorCommand = 0;
Command *Robot::holdElevatorCommand = 0;
Command *Robot::zeroElevator = 0;
Parameters *Robot::parameters = 0;
PowerDistributionPanel *Robot::pdp = 0;

int Ticks = 0;

void Robot::RobotInit() {
	try {
		// Get our save parameters before we do anything else
		parameters = new Parameters();
		parameters->GetParams();

		RobotMap::init();
		pdp = new PowerDistributionPanel();
		printf("PDP Temperature: %f\n", pdp->GetTemperature());
		driveSubsystem = new DriveSubsystem();
		elevator = new Elevator();
		compressorSubsystem = new CompressorSubsystem(7);			// CAN channel 7
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
		holdElevatorCommand = new PositionElevator(0, false);
		driveElevatorCommand = new DriveElevator();
		zeroElevator = new ZeroElevator();

		autoCommandMoveToZone = new AutonomousMoveToZone();
		autoCommand1Can = new AutonomousCommand1Can();
		// Add a button to the SmartDashboard to allow the command to be tested
		SmartDashboard::PutData("AutoCommand1Can", autoCommandMoveToZone);
		SmartDashboard::PutData("AutoCommand1Can", autoCommand1Can);
		// Stuff to get autonomous selection on SmartDashboard
		chooser = new SendableChooser();
		chooser->AddDefault("Can to Auto Zone", autoCommand1Can);
		chooser->AddObject("Drive to Auto Zone", autoCommandMoveToZone);
		SmartDashboard::PutData("Autonomous Modes",chooser);

		Camera::EnumerateCameras();

		lw = LiveWindow::GetInstance();

		// instantiate the command used for the autonomous period
		// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

		// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

	}
	catch (std::exception& e) {
		printf("Exception: %s\n",  e.what());
	}
  }

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit() {
	Camera::StopCameras();
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
	UpdateDashboardPeriodic();
}

void Robot::AutonomousInit() {
	RobotMap::driveBackLeft->SetPosition(0.0);
	parameters->UpdateDrivePIDParams();
	zeroElevator->Start();
	parameters->UpdateElevatorPIDParams();
	if (!elevator->WasZeroed()) zeroElevator->Start();
	autonomousCommand = (Command *)chooser->GetSelected();
	if (autonomousCommand != NULL)
		autonomousCommand->Start();
	Camera::StartCameras();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	UpdateDashboardPeriodic();
	Camera::Feed();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to 
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand != NULL)
		autonomousCommand->Cancel();
	if (!elevator->WasZeroed()) zeroElevator->Start();
	RobotMap::armFlapSolenoid->Set(DoubleSolenoid::kOff);
	RobotMap::shifterSolenoid->Set(DoubleSolenoid::kOff);
	RobotMap::totePusherSolenoid->Set(DoubleSolenoid::kOff);
	// It seems that we need a Set to confirm the control mode or else it reverts
	parameters->UpdateDrivePIDParams();
	parameters->UpdateElevatorPIDParams();
	Camera::StartCameras();
}


void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	UpdateDashboardPeriodic();
	float up = Robot::oi->joystick1->GetRawAxis(3);
	float down = Robot::oi->joystick1->GetRawAxis(2);
	if (fabs(up) > 0.06 || fabs(down) > 0.06)
	{
		//printf("Drive Elevator initiated by joystick input up=%f, down=%f.\n", up, down);
		Robot::driveElevatorCommand->Start();
	}
	Camera::Feed();
}

void Robot::TestPeriodic() {
	lw->Run();
	Camera::Feed();
	UpdateDashboardPeriodic();
}

void Robot::UpdateDashboardPeriodic() {
	try {
		// Do this every 1/10th of a second, not more often for efficiency
		if (Ticks++%5==0) {

		Compressor* wC = compressorSubsystem->workingCompressor;
		if (NULL!=wC) {
			SmartDashboard::PutBoolean("CompEnabled", wC->Enabled());
			SmartDashboard::PutNumber("CompCurrent", wC->GetCompressorCurrent());
		}
		try {
			SmartDashboard::PutNumber("CAN Front Left Fault", RobotMap::driveFrontLeft->GetFaults());
			SmartDashboard::PutNumber("Left Encoder Position", Robot::driveSubsystem->GetLeftEncoderPosition());
			SmartDashboard::PutNumber("Right Encoder Position", Robot::driveSubsystem->GetRightEncoderPosition());
			SmartDashboard::PutNumber("DrivePID Left  Error",RobotMap::driveBackLeft->GetClosedLoopError());
			SmartDashboard::PutNumber("DrivePID Right Error",RobotMap::driveBackRight->GetClosedLoopError());

			if (Robot::oi->driveDistanceCommand != NULL) {
				SmartDashboard::PutNumber("DriveDistanceCmd distL",((DriveDistanceCommand *)Robot::oi->driveDistanceCommand)->distanceTravelledL);
				SmartDashboard::PutNumber("DriveDistanceCmd distR",((DriveDistanceCommand *)Robot::oi->driveDistanceCommand)->distanceTravelledR);
			}
			// CANTalon 1, which is the Elevator lead Talon, isn't present on the kit bot
			if (!RobotMap::testBot) {
				SmartDashboard::PutNumber("Elevator Encoder Raw", RobotMap::elevatorMotor1->GetEncPosition());
				SmartDashboard::PutNumber("Elevator PID Error", RobotMap::elevatorMotor1->GetClosedLoopError());
			}
			SmartDashboard::PutNumber("Elevator Position", Robot::elevator->GetPosition());
			SmartDashboard::PutNumber("Elevator Target Position", Robot::elevator->targetHeight);
		}
		catch(int e) {
			printf("SmartDashboard exception, post ShowPIDParams.\n");
		}

			SmartDashboard::PutNumber("PDP Temperature", pdp->GetTemperature());
			RobotMap::Ct->UpdateDashboard();
		}
	}
	catch (std::exception& e) {
		printf("SmartDashboard Exception: %s\n",  e.what());
	}
}

void Robot::DisplaySensorData() {
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


START_ROBOT_CLASS(Robot);
