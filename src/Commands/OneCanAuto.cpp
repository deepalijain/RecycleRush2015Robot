#include "OneCanAuto.h"

OneCanAuto::OneCanAuto() {
	AddSequential(new PositionElevator(1, true));
	AddSequential(new DriveDistanceCommand(105,1,1));
}
