#pragma once

#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class RestoreDrive: public Command {
public:
	RestoreDrive();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};


