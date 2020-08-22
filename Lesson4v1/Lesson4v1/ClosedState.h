#pragma once
#include "State.h"
#include "LockedState.h"
#include "OpenedState.h"
#include "StateContext.h"
class ClosedState :
	public State
{
public:
	ClosedState();

	virtual void Unlock();
	virtual void Open();
	virtual void Close();
	virtual void Lock();

	~ClosedState();
};

