/*
 * Parameters.h
 *
 *  Created on: Feb 21, 2015
 *      Author: cbf
 */

#ifndef SRC_SUBSYSTEMS_PARAMETERS_H_
#define SRC_SUBSYSTEMS_PARAMETERS_H_

class Parameters {
private:
	int getInt(FILE *pFile);
	double getDouble(FILE *pFile);
	void SaveParams();
	std::vector<std::string> comments;
public:
	static int version;
	static double driveP;
	static double driveI;
	static double driveD;
	static double driveF;
	static int driveIZone;
	static double driveRampRate;
	static double drivePIDDistance;

	static double elevatorP;
	static double elevatorI;
	static double elevatorD;
	static double elevatorF;
	Parameters();
	void GetParams();
	void ShowPIDParams();
	void UpdateDrivePIDParams();
	void UpdateElevatorPIDParams();
};

#endif /* SRC_SUBSYSTEMS_PARAMETERS_H_ */
