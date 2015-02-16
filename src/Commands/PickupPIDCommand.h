
#pragma once


#include "Commands/Subsystem.h"
#include "../Robot.h"

class PickupPIDCommand: public Command {
public:
	PickupPIDCommand(int _ticks);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	int ticks;
	bool isFinished, firstTime;
};

