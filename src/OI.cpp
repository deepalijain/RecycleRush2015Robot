// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"

#include "Commands/ApplyBreakCommand.h"
#include "Commands/DriveCommand.h"
#include "Commands/DriveDistanceCommand.h"
#include "Commands/GoDownCommand.h"
#include "Commands/PickUpCanCommand.h"
#include "Commands/PickUpToteCommand.h"
#include "Commands/ToggleFlapsCommand.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
	// Process operator interface input here.
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

	joystick1 = new Joystick(0);
	joystick2 = new Joystick(1);

	driveDistanceCommand = new DriveDistanceCommand(1000);
	applyBreakCommand = new ApplyBreakCommand();
	goDownCommand = new GoDownCommand();
	pickupCanCommand = new PickUpCanCommand();
	pickupToteCommand = new PickUpToteCommand();
	driveCommand = new DriveCommand();
	toggleArmFlap = new ToggleFlapsCommand();

	
	joystickButton5 = new JoystickButton(joystick1, 5);
	joystickButton5->WhenPressed(driveDistanceCommand);
	joystickButton4 = new JoystickButton(joystick1, 4);
	joystickButton4->WhenPressed(applyBreakCommand);
	joystickButton3 = new JoystickButton(joystick1, 3);
	joystickButton3->WhenPressed(goDownCommand);
	joystickButton2 = new JoystickButton(joystick1, 2);
	joystickButton2->WhenPressed(pickupCanCommand);
	joystickButton1 = new JoystickButton(joystick1, 1);
	joystickButton1->WhenPressed(pickupToteCommand);

	toggleArmFlapButton = new JoystickButton(joystick1,7);
	toggleArmFlapButton->WhenPressed(toggleArmFlap);

        // SmartDashboard Buttons
	SmartDashboard::PutData("AutonomousCommand", autonomousCommand);

	SmartDashboard::PutData("DriveCommand", driveCommand);

	SmartDashboard::PutData("PickUpToteCommand", pickupToteCommand);

	SmartDashboard::PutData("PickUpCanCommand", pickupCanCommand);

	SmartDashboard::PutData("GoDownCommand", goDownCommand);

	SmartDashboard::PutData("BreakCommand", applyBreakCommand);

	SmartDashboard::PutData("DriveDistanceCommand", driveDistanceCommand);


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

Joystick* OI::getJoystick2() {
	return joystick2;
}

Joystick* OI::getJoystick1() {
	return joystick1;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
