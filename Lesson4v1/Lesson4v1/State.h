#pragma once
class StateContext;
class State
{
public:
	
	void SetContext(StateContext* context);
	virtual void Unlock() = 0;
	virtual void Open() = 0;
	virtual void Close() = 0;
	virtual void Lock() = 0;

	virtual ~State();
protected:
	StateContext* m_Context;
};

