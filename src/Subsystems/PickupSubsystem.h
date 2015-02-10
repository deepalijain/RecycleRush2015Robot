// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef PICKUPSUBSYSTEM_H
#define PICKUPSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "ctre/CanTalonSRX.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class PickupSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	CANTalon* pickupMotor1;
	Encoder* pickupEncoder;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	// Need to use CanTalonSRX for pickupMotor2 so we can invert the following Talon
	// See Software Reference Manual 21.15
	CanTalonSRX* pickupMotor2;

	PickupSubsystem();
	void InitDefaultCommand();
};

#endif
