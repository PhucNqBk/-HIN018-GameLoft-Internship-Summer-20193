#pragma once
#include "State.h"
#include "ClosedState.h"
#include "OpenedState.h"
#include "StateContext.h"
class LockedState :
	public State
{
public:
	LockedState();

	virtual void Unlock();
	virtual void Open();
	virtual void Close();
	virtual void Lock();

	virtual ~LockedState();
};

