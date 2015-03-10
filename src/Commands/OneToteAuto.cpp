#include "OneToteAuto.h"

OneToteAuto::OneToteAuto() {
	AddSequential(new PositionElevator(1, false));
	AddSequential(new DriveDistanceCommand(105,1,1));
}
