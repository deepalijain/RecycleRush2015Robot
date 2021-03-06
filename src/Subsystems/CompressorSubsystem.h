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

/**
 *
 *
 * @author ExampleAuthor
 */
class CompressorSubsystem: public Subsystem {
private:

public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	Compressor *workingCompressor;
	CompressorSubsystem(int channel);
	void InitDefaultCommand();
	void Toggle();
	void TurnOn();
	void TurnOff();
	bool GetState();
	DoubleSolenoid* testSolenoid;
};

