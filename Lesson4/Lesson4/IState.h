#pragma once
class StateContext;

class IState
{
public:

	virtual void Unlock(StateContext* context) {}
	virtual void Open(StateContext* context) {}
	virtual void Close(StateContext* context) {}
	virtual void Lock(StateContext* context){}
};

