// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#pragma once

#include "WPILib.h"

class OI {
private:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	JoystickButton *joystickButton5;
	JoystickButton *joystickButton4;
	JoystickButton *toggleArmFlapButton;
	JoystickButton *toggleCompressorButton;
	JoystickButton *driveDistanceButton;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	Joystick *joystick2;
	Joystick *joystick1;

	Command *driveDistanceCommand;
	Command *driveCommand;
	Command *toggleArmFlap;
	Command *toteUp;
	Command *toteDown;
	Command *drivePID;
	Command *toggleCompressor;

	OI();
 
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

	Joystick *getJoystick1();
	Joystick *getJoystick2();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
};

