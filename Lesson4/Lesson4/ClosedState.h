#pragma once
#include "IState.h"
#include "LockedState.h"
#include "OpenedState.h"
#include "StateContext.h"
class ClosedState :
	public IState
{
public:
	ClosedState();

	virtual void Unlock(StateContext* context);
	virtual void Open(StateContext* context);
	virtual void Close(StateContext* context);
	virtual void Lock(StateContext* context);

	virtual ~ClosedState();
};

