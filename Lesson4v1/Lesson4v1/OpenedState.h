#pragma once
#include "State.h"
#include "ClosedState.h"
#include "LockedState.h"
#include "StateContext.h"
class OpenedState :
	public State
{
public:
	OpenedState();
	
	virtual void Unlock();
	virtual void Open();
	virtual void Close();
	virtual void Lock();

	~OpenedState();
};

