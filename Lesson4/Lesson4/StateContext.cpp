#include "pch.h"
#include "StateContext.h"


StateContext::StateContext()
{
	m_State = new LockedState();
}
void StateContext::SetState(IState* state) {
	if (m_State != nullptr) {
		delete m_State;
	}
	m_State = state;
}
void StateContext::Unlock() 
{
	m_State->Unlock(this);
}

void StateContext::Open()
{
	m_State->Open(this);
}

void StateContext::Close() 
{
	m_State->Close(this);
}

void StateContext::Lock()
{
	m_State->Lock(this);
}

StateContext::~StateContext()
{
	delete m_State;
}
