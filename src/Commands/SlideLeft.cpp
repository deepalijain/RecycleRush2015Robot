// RobotBuilder Version: 1.5
//

#include "SlideLeft.h"
#include "RightOnly.h"
#include "LeftOnly.h"
#include "DriveDistance.h"
#include "../RobotMap.h"
#include "DelayCommand.h"
#include "RestoreDrive.h"

SlideLeft::SlideLeft(double inches) {
	printf("SlideLeft constructed\n");
	// compute parameters
	double w = RobotMap::robotWidth;
	double a = acos((w-inches) / w);
	double arc = a * w;
	double d = w * sin(a);
	AddSequential(new RightOnly(-arc));
	AddSequential(new DelayCommand(0.2));
	AddSequential(new LeftOnly(-arc));
	AddSequential(new DelayCommand(0.2));
	AddSequential(new DriveDistance(d, d));
	AddSequential(new RestoreDrive());

}
