#pragma once

#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Turn: public Command {
public:
	Turn(double left, double right);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	double m_left, m_right;
	DriveSubsystem *m_driveSubsystem;
	double m_startPosition;
};


