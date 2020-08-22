#pragma once
#include "State.h"
#include "OpenedState.h"
#include "ClosedState.h"
#include "LockedState.h"
class StateContext
{
public:
	StateContext(State* state = nullptr);
	inline static StateContext* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new StateContext(); }
	void SetState(State* state);
	void Unlock();
	void Open();
	void Close();
	void Lock();
	~StateContext();

	private:
		State* m_State;
		static StateContext* s_Instance;
};

