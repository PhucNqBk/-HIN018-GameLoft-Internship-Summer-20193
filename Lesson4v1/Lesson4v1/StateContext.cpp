#include "pch.h"
#include "StateContext.h"

StateContext* StateContext::s_Instance = nullptr;
StateContext::StateContext(State* state)
{
	if (state == nullptr) {
		SetState(new LockedState());
	}
	else 
	{
		SetState(state);
	}
	
}

void StateContext::SetState(State* state)
{
	if (m_State != nullptr) 
	{
		delete m_State;
	}
	m_State = state;
	m_State->SetContext(this);
}
void StateContext::Unlock()
{
	m_State->Unlock();
}
void StateContext::Open()
{
	m_State->Open();
}
void StateContext::Close()
{
	m_State->Close();
}
void StateContext::Lock()
{
	m_State->Lock();
}
StateContext::~StateContext()
{
	delete m_State;
}
