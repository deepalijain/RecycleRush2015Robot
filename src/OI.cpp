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
#include "Commands/ToggleFlapsCommand.h"
#include "Commands/DrivePID.h"
#include "Commands/PositionElevator.h"
#include "Commands/ToggleCompressor.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
	joystick1 = new Joystick(0);
	joystick2 = new Joystick(1);

	driveDistanceCommand = new DriveDistanceCommand(12*1);
	//applyBreakCommand = new ApplyBreakCommand();
	driveCommand = new DriveCommand();
	drivePID = new DrivePID();
	toggleArmFlap = new ToggleFlapsCommand();
	toggleCompressor = new ToggleCompressor();

	//if (!RobotMap::testBot) {
		toteUp = new PositionElevator(1);
		toteDown = new PositionElevator(-1);
		joystickButton5 = new JoystickButton(joystick1, 5);		// Right bumper
		joystickButton5->WhenPressed(toteUp);
		joystickButton5 = new JoystickButton(joystick1, 6);		// Left bumpter
		joystickButton5->WhenPressed(toteDown);
	//}
	joystickButton4 = new JoystickButton(joystick1, 4);			// Y button
	joystickButton4->WhenPressed(drivePID);

	toggleArmFlapButton = new JoystickButton(joystick1, 7);		// tiny back button (old XBox)
	toggleArmFlapButton->WhenPressed(toggleArmFlap);

	toggleCompressorButton = new JoystickButton(joystick1, 8);	// tiny start button
	toggleCompressorButton->WhenPressed(toggleCompressor);

	driveDistanceButton = new JoystickButton(joystick1, 10);	// right axis click
	driveDistanceButton->WhenPressed(driveDistanceCommand);

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
