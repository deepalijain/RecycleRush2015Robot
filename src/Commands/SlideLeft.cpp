// RobotBuilder Version: 1.5
//

#include "SlideLeft.h"
#include "RightOnly.h"
#include "LeftOnly.h"
#include "DriveDistance.h"
#include "Delay.h"
#include "../RobotMap.h"

SlideLeft::SlideLeft(double inches) {
	printf("SlideLeft constructed\n");
	// compute parameters
	double w = RobotMap::robotWidth;
	double a = acos((w-inches) / w);
	double arc = a * w;
	double d = w * sin(a);
	AddSequential(new RightOnly(-arc));
	AddSequential(new Delay(0.2));
	AddSequential(new LeftOnly(-arc));
	AddSequential(new Delay(0.2));
	AddSequential(new DriveDistance(d, d));

}
