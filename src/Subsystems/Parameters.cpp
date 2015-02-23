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

static double driveP = 0;
static double driveI = 0;
static double driveD = 0;
static double driveF = 0;
static double drivePIDDistance = 0;

static double elevatorP = 0;
static double elevatorI = 0;
static double elevatorD = 0;
static double elevatorF = 0;
static double elevatorPIDDistance = 0;

Parameters::Parameters() {
	// TODO Auto-generated constructor stub

}

void Parameters::ShowPIDParams()
{
	try {
		SmartDashboard::PutNumber("driveP", driveP);
		SmartDashboard::PutNumber("driveI", driveI);
		SmartDashboard::PutNumber("driveD", driveD);
		SmartDashboard::PutNumber("driveF", driveF);
		SmartDashboard::PutNumber("drivePIDDistance", drivePIDDistance);

		SmartDashboard::PutNumber("elevatorP", elevatorP);
		SmartDashboard::PutNumber("elevatorI", elevatorI);
		SmartDashboard::PutNumber("elevatorD", elevatorD);
		SmartDashboard::PutNumber("elevatorF", elevatorF);
		SmartDashboard::PutNumber("elevatorPIDDistance", elevatorPIDDistance);
	}
	catch (int e) {
		printf("ShowPIDParams threw exception\n");
	}
}

void Parameters::UpdateDrivePIDParams()
{
	bool needsUpdate = false;
	double ldriveP, ldriveI, ldriveD, ldriveF;

	ldriveP = SmartDashboard::GetNumber("driveP");
	ldriveI = SmartDashboard::GetNumber("driveI");
	ldriveD = SmartDashboard::GetNumber("driveD");
	ldriveF = SmartDashboard::GetNumber("driveF");
	drivePIDDistance = SmartDashboard::GetNumber("driveF");

	needsUpdate |= (ldriveP != driveP);
	needsUpdate |= (ldriveP != driveP);
	needsUpdate |= (ldriveP != driveP);

	driveP = ldriveP;
	driveI = ldriveI;
	driveD = ldriveD;
	driveF = ldriveF;
	if (needsUpdate) SaveParams();
}

void Parameters::UpdateElevatorPIDParams()
{
	bool needsUpdate = false;
	double lelevatorP, lelevatorI, lelevatorD, lelevatorF;

	lelevatorP = SmartDashboard::GetNumber("elevatorP");
	lelevatorI = SmartDashboard::GetNumber("elevatorI");
	lelevatorD = SmartDashboard::GetNumber("elevatorD");
	lelevatorF = SmartDashboard::GetNumber("elevatorF");
	elevatorPIDDistance = SmartDashboard::GetNumber("elevatorF");

	needsUpdate |= (lelevatorP != elevatorP);
	needsUpdate |= (lelevatorP != elevatorP);
	needsUpdate |= (lelevatorP != elevatorP);

	elevatorP = lelevatorP;
	elevatorI = lelevatorI;
	elevatorD = lelevatorD;
	elevatorF = lelevatorF;
	if (needsUpdate) SaveParams();
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
	return val;
}

void Parameters::GetParams() {
	FILE *pFile = fopen("params2015.txt", "r");
	if (NULL != pFile){
		int version = getInt(pFile);

		if (1 == version) {
			// drive PID params
			driveP = getDouble(pFile);
			driveI = getDouble(pFile);
			driveD = getDouble(pFile);
			driveF = getDouble(pFile);

			// elevator PID params
			elevatorP = getDouble(pFile);
			elevatorI = getDouble(pFile);
			elevatorD = getDouble(pFile);
			elevatorF = getDouble(pFile);
		}
		fclose(pFile);
		printf("Loaded params\n  %f %f %f %f\n  %f %f %f %f\n",
			driveP, driveI, driveD, driveF,
			elevatorD, elevatorI, elevatorD, elevatorF);
	}
}

void Parameters::SaveParams() {
	// make a backup copy just in case we get interrupted
	system("cp params2015.txt params2015.txt~");
	FILE *pFile = fopen("params2015.txt", "w");
	if (NULL != pFile)
	{
		fprintf(pFile, "%d\t%s\n", 1, comments[0].c_str());
		fprintf(pFile, "%f\t%s\n", driveP, comments[1].c_str());
		fprintf(pFile, "%f\t%s\n", driveI, comments[2].c_str());
		fprintf(pFile, "%f\t%s\n", driveD, comments[3].c_str());
		fprintf(pFile, "%f\t%s\n", driveF, comments[5].c_str());

		fprintf(pFile, "%f\t%s\n", elevatorP, comments[5].c_str());
		fprintf(pFile, "%f\t%s\n", elevatorI, comments[6].c_str());
		fprintf(pFile, "%f\t%s\n", elevatorD, comments[7].c_str());
		fprintf(pFile, "%f\t%s\n", elevatorF, comments[8].c_str());

		fclose(pFile);
		printf("Saved params\n  %f %f %f %f\n  %f %f %f %f\n",
			driveP, driveI, driveD, driveF,
			elevatorD, elevatorI, elevatorD, elevatorF);
	}
	else printf("Couldn't open params2015.txt for write.\n");
}
