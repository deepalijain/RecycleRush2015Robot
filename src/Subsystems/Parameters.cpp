/*
 * Parameters.cpp
 *
 *  Created on: Feb 21, 2015
 *      Author: cbf
 */


#include <stdio.h>
#include <vector>
#include <string>
#include "Parameters.h"
#include "WPILib.h"

double Parameters::driveP;
double Parameters::driveI;
double Parameters::driveD;
double Parameters::driveF;
int Parameters::driveIZone;			// ticks
double Parameters::driveRampRate;	// volts per second
double Parameters::drivePIDDistance;

double Parameters::elevatorP;
double Parameters::elevatorI;
double Parameters::elevatorD;
double Parameters::elevatorF;

int Parameters::version;

Parameters::Parameters() {

}

void Parameters::ShowPIDParams()
{
	try {
		SmartDashboard::PutNumber("driveP", driveP);
		SmartDashboard::PutNumber("driveI", driveI);
		SmartDashboard::PutNumber("driveD", driveD);
		SmartDashboard::PutNumber("driveF", driveF);
		SmartDashboard::PutNumber("driveIZone", driveIZone);
		SmartDashboard::PutNumber("driveRampRate", driveRampRate);
		SmartDashboard::PutNumber("drivePIDDistance", drivePIDDistance);


		SmartDashboard::PutNumber("elevatorP", elevatorP);
		SmartDashboard::PutNumber("elevatorI", elevatorI);
		SmartDashboard::PutNumber("elevatorD", elevatorD);
		SmartDashboard::PutNumber("elevatorF", elevatorF);
	}
	catch (int e) {
		printf("ShowPIDParams threw exception\n");
	}
}

void Parameters::UpdateDrivePIDParams()
{
	bool needsUpdate = false;
	double ldriveP, ldriveI, ldriveD, ldriveF, ldriveIZone, ldriveRampRate,
		   ldrivePIDDistance;

	try {
		ldriveP = SmartDashboard::GetNumber("driveP");
		ldriveI = SmartDashboard::GetNumber("driveI");
		ldriveD = SmartDashboard::GetNumber("driveD");
		ldriveF = SmartDashboard::GetNumber("driveF");
		ldriveIZone = SmartDashboard::GetNumber("driveIZone");
		ldriveRampRate = SmartDashboard::GetNumber("driveRampRate");
		ldrivePIDDistance = SmartDashboard::GetNumber("drivePIDDistance");

		needsUpdate |= (ldriveP != driveP);
		needsUpdate |= (ldriveI != driveI);
		needsUpdate |= (ldriveD != driveD);
		needsUpdate |= (ldriveF != driveF);
		needsUpdate |= ((int)ldriveIZone != driveIZone);
		needsUpdate |= (ldriveRampRate != driveRampRate);
		needsUpdate |= (ldrivePIDDistance != drivePIDDistance);

		driveP = ldriveP;
		driveI = ldriveI;
		driveD = ldriveD;
		driveF = ldriveF;
		driveIZone = ldriveIZone;
		driveRampRate = ldriveRampRate;
		drivePIDDistance = ldrivePIDDistance;
		if (needsUpdate) {
			SaveParams();
			ShowPIDParams();
		}
	}
	catch (int e) {
		printf("UpdateDrivePIDParams threw an exception\n");
	}
}

void Parameters::UpdateElevatorPIDParams()
{
	bool needsUpdate = false;
	double lelevatorP, lelevatorI, lelevatorD, lelevatorF;

	lelevatorP = SmartDashboard::GetNumber("elevatorP");
	lelevatorI = SmartDashboard::GetNumber("elevatorI");
	lelevatorD = SmartDashboard::GetNumber("elevatorD");
	lelevatorF = SmartDashboard::GetNumber("elevatorF");

	needsUpdate |= (lelevatorP != elevatorP);
	needsUpdate |= (lelevatorI != elevatorI);
	needsUpdate |= (lelevatorD != elevatorD);
	needsUpdate |= (lelevatorF != elevatorF);

	elevatorP = lelevatorP;
	elevatorI = lelevatorI;
	elevatorD = lelevatorD;
	elevatorF = lelevatorF;
	if (needsUpdate) {
		SaveParams();
		ShowPIDParams();
	}
}


// We have our own parameter file format because the one provided only allows reads params
// from the SmartDashboard at robot init time. We want to change our params when the
// robot is running and immediately save them to disk in case we crash.

// Format is one value per line, not labelled (all pararms are positional).
// Once the value is read the rest of the line is ignored, so the rest of
// the line can be used for a comment. These comments are preserved when
// we save the updated file.

// The first line of the file is an integer version number, so we can extend this


int Parameters::getInt(FILE *pFile)
{
	char line[120];
	char comment[80] = "";
	std::string *Comment = new std::string;
	int val;
	fgets(line, sizeof(line), pFile);
	sscanf(line, "%i %s", &val, comment);
	comment[sizeof(comment)-1] = 0;
	*Comment = comment;
	comments.push_back(*Comment);
	return val;
}

// stored values are actually floats not doubles (because that's what
// sscanf can parse). I think six or seven digits precision is enough.
double Parameters::getDouble(FILE *pFile)
{
	char line[120];
	char comment[80] = "";
	std::string *Comment = new std::string;
	float val;
	fgets(line, sizeof(line), pFile);
	sscanf(line, "%f %s", &val, comment);
	comment[sizeof(comment)-1] = 0;
	*Comment = comment;
	comments.push_back(*Comment);
	return val;
}

void Parameters::GetParams() {
	FILE *pFile = fopen("/home/lvuser/params2015.txt", "r");
	if (NULL != pFile){
		version = getInt(pFile);

		if (version < 4) {
			// drive PID params
			driveP = getDouble(pFile);
			driveI = getDouble(pFile);
			driveD = getDouble(pFile);
			driveF = getDouble(pFile);
			driveIZone = getInt(pFile);
			driveRampRate = getDouble(pFile);
			drivePIDDistance = getDouble(pFile);

			// elevator PID params
			elevatorP = getDouble(pFile);
			elevatorI = getDouble(pFile);
			elevatorD = getDouble(pFile);
			elevatorF = getDouble(pFile);
		}
		fclose(pFile);
		ShowPIDParams();	// show on Dashboard when loaded
		printf("Loaded params\n    %f %f %f %f %d %f %f \n  %f %f %f %f\n",
			driveP, driveI, driveD, driveF, driveIZone, driveRampRate, drivePIDDistance,
			elevatorP, elevatorI, elevatorD, elevatorF);
	}
}

void Parameters::SaveParams() {
	// make a backup copy just in case we get interrupted
	system("cp /home/lvuser/params2015.txt /home/lvuser/params2015.txt~");
	FILE *pFile = fopen("/home/lvuser/params2015.txt", "w");
	if (NULL != pFile)
	{
		int i = 0;
		fprintf(pFile, "%d\t%s\n", 3, comments[i++].c_str());
		fprintf(pFile, "%f\t%s\n", driveP, comments[i++].c_str());
		fprintf(pFile, "%f\t%s\n", driveI, comments[i++].c_str());
		fprintf(pFile, "%f\t%s\n", driveD, comments[i++].c_str());
		fprintf(pFile, "%f\t%s\n", driveF, comments[i++].c_str());
		fprintf(pFile, "%d\t%s\n", driveIZone, (version > 2) ? "" : comments[i++].c_str());
		fprintf(pFile, "%f\t%s\n", driveRampRate, (version > 2) ? "" : comments[i++].c_str());
		fprintf(pFile, "%f\t%s\n", drivePIDDistance, comments[i++].c_str());

		fprintf(pFile, "%f\t%s\n", elevatorP, comments[i++].c_str());
		fprintf(pFile, "%f\t%s\n", elevatorI, comments[i++].c_str());
		fprintf(pFile, "%f\t%s\n", elevatorD, comments[i++].c_str());
		fprintf(pFile, "%f\t%s\n", elevatorF, comments[i++].c_str());

		fclose(pFile);
		printf("Saved params\n  %f %f %f %f %d %f %f \n  %f %f %f %f\n",
			driveP, driveI, driveD, driveF, driveIZone, driveRampRate, drivePIDDistance,
			elevatorP, elevatorI, elevatorD, elevatorF);
	}
	else printf("Couldn't open params2015.txt for write.\n");
}
