#pragma once
#include "IState.h"
#include "ClosedState.h"
#include "OpenedState.h"
#include "StateContext.h"
class LockedState :
	public IState
{
public:
	LockedState();
	
	virtual void Unlock(StateContext* context);
	virtual void Open(StateContext* context);
	virtual void Close(StateContext* context);
	virtual void Lock(StateContext* context);

	virtual ~LockedState();
};

