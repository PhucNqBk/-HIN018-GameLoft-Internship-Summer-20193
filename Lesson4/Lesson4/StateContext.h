#pragma once
#include "IState.h"
#include "LockedState.h"
#include "ClosedState.h"
#include "OpenedState.h"

class StateContext
{
public:
	StateContext();

	void SetState(IState* state);
	void Unlock();
	void Open();
	void Close();
	void Lock();

	virtual ~StateContext();
	
private:
	IState* m_State;
};

