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
#include <exception>
#include "Commands/DriveCommand.h"
#include "Commands/DriveElevator.h"
#include "Commands/DriveDistanceCommand.h"
#include "Commands/PositionElevator.h"
#include "Commands/DrivePID.h"
#include "Commands/ZeroElevator.h"

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
IMAQdxSession Robot::session[2];
Image *Robot::frame[2];
IMAQdxError Robot::imaqError[2];
uInt32 Robot::cameraCount;
;

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
	if (cameraCount>0) CameraStop(1);
	if (cameraCount>1) CameraStop(2);
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
	UpdateDashboardPeriodic();
}

void Robot::AutonomousInit() {
	RobotMap::driveBackLeft->SetPosition(0.0);
	CameraCount();
	if (cameraCount>0) CameraStart(1);
	if (cameraCount>1) CameraStart(2);
	if (autonomousCommand != NULL)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	UpdateDashboardPeriodic();
	if (cameraCount>0) CameraFeed(1);
	if (cameraCount>1) CameraFeed(2);
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
	CameraCount();
	if (cameraCount>0) CameraStart(1);
	if (cameraCount>1) CameraStart(2);
}


void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	UpdateDashboardPeriodic();
	if (cameraCount>0) CameraFeed(1);
	if (cameraCount>1) CameraFeed(2);
}

void Robot::TestPeriodic() {
	lw->Run();
	if (cameraCount>0) CameraFeed(1);
	if (cameraCount>1) CameraFeed(2);
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

			SmartDashboard::PutNumber("DriveDistanceCmd distL",((DriveDistanceCommand *)Robot::oi->driveDistanceCommand)->distanceTravelledL);
			SmartDashboard::PutNumber("DriveDistanceCmd distR",((DriveDistanceCommand *)Robot::oi->driveDistanceCommand)->distanceTravelledR);
			// CANTalon 1, which is the Elevator lead Talon, isn't present on the kit bot
			if (!RobotMap::testBot) {
				SmartDashboard::PutNumber("Elevator Encoder Position", RobotMap::elevatorMotor1->GetClosedLoopError());
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


int Robot::CameraCount() {
	IMAQdxCameraInformation camInfo[4]; 	// we crash if there are more than 6 cameras!
	cameraCount = 4;
	// last parameter is "connectedOnly". Why would we want to enumerate non-connected cameras?
	IMAQdxEnumerateCameras(camInfo, &cameraCount, true);
	printf("Cameras (%u):\n", (unsigned int)cameraCount);
	for (uInt32 i=0; i!=cameraCount; i++) printf("  %s %s %s\n", camInfo[i].VendorName,
											     camInfo[i].ModelName, camInfo[i].InterfaceName);
	return cameraCount;
}

void Robot::CameraStart(int camNum) {
	std::string imaqErrorString;
    // create an image
	frame[camNum] = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	//the camera name (ex "cam0") can be found through the roborio web interface
	char cam[5] = "cam0";
	cam[3] = '0' + camNum;
	printf("Opening camera %s\n", cam);
	imaqError[camNum] = IMAQdxOpenCamera(cam, IMAQdxCameraControlModeController, &session[camNum]);
	if(imaqError[camNum] != IMAQdxErrorSuccess) {
		imaqErrorString = std::to_string((long)imaqError[camNum]);
		DriverStation::ReportError("IMAQdxOpenCamera error: " + imaqErrorString + "\n");
		printf("IMAQdxOpenCamera error (%s): %s\n", cam, imaqErrorString.c_str());
	}
	imaqError[camNum] = IMAQdxConfigureGrab(session[camNum]);
	if(imaqError[camNum] != IMAQdxErrorSuccess) {
		imaqErrorString = std::to_string((long)imaqError[camNum]);
		DriverStation::ReportError("IMAQdxConfigureGrab error: " + imaqErrorString + "\n");
		printf("IMAQdxConfigureGrab error(%s): %s\n", cam, imaqErrorString.c_str());
	}
    // start to acquire images
	printf("Camera Session #: %lu\n", session[camNum]);
	if (0!=session[camNum]) IMAQdxStartAcquisition(session[camNum]);

}

void Robot::CameraFeed(int camNum) {
	std::string imaqErrorString;
    // grab an image, draw the circle, and provide it for the camera server which will
    // in turn send it to the dashboard.
	// let's only do this every 1/10 second to avoid excess cpu & network traffic
	// Ticks+2 to avoid doing it on same cycle as SmartDashBoard updates
	if (session[camNum]!=0 && (Ticks+2)%5==0) {
		char cam[5] = "cam0";
		cam[3] = '0' + camNum;
		IMAQdxGrab(session[camNum], frame[camNum], false, NULL);
		if(imaqError[camNum] != IMAQdxErrorSuccess) {
			imaqErrorString = std::to_string((long)imaqError);
			DriverStation::ReportError("IMAQdxGrab error: " + imaqErrorString + "\n");
			printf("IMAQdxConfigureGrab error (%s): %s\n", cam, imaqErrorString.c_str());
		} else {
			// we don't need the silly circle but might use this for something latter
			// imaqDrawShapeOnImage(frame, frame, { 10, 10, 100, 100 }, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL, 0.0f);
			CameraServer::GetInstance()->SetImage(frame[camNum]);
		}				// wait for a motor update time
	}
}

void Robot::CameraStop(int camNum) {
    // stop image acquisition
	if (0!=session[camNum]) {
		char cam[5] = "cam0";
		cam[3] = '0' + camNum;
		// Had trouble with imaqDrawTextOnImage
		//const DrawTextOptions options = {"Arial", 12, 0, 0, 0, 0, IMAQ_CENTER, IMAQ_INVERT};
		//int fontUsed;
		//imaqDrawTextOnImage(frame, frame, {120, 80}, "X", &options, &fontUsed);
		if (NULL!=frame[camNum]) {
			// Would really like to make this semi-transparent, but not apparent how.
			imaqDrawShapeOnImage(frame[camNum], frame[camNum], { 100, 100, 160, 160 }, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL,3.0f);
			CameraServer::GetInstance()->SetImage(frame[camNum]);
		}
		IMAQdxStopAcquisition(session[camNum]);
		IMAQdxCloseCamera(session[camNum]);
		printf("Camera %s closed.", cam);
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
