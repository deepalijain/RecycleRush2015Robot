#include "OneToteAndCanAuto.h"

OneToteAndCanAuto::OneToteAndCanAuto() {
	AddSequential(new PositionElevator(1, true));
	AddSequential(new DriveDistanceCommand(22,1,1));
	AddSequential(new PositionElevator(-1, true));
	AddSequential(new PositionElevator(1, false));
	AddSequential(new DriveDistanceCommand(10*rand(),-1,1));
	AddSequential(new DriveDistanceCommand(105,1,1));
}
