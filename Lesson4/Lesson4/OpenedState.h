#pragma once
#include "IState.h"
#include "LockedState.h"
#include "ClosedState.h"
#include "StateContext.h"
class OpenedState :
	public IState
{
public:
	OpenedState();

	virtual void Unlock(StateContext* context);
	virtual void Open(StateContext* context);
	virtual void Close(StateContext* context);
	virtual void Lock(StateContext* context);

	virtual ~OpenedState();
};

