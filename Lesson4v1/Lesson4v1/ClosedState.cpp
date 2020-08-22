#include "pch.h"
#include "ClosedState.h"
#include <iostream>

ClosedState::ClosedState()
{
}

void ClosedState::Unlock() {
	std::cout << "Closed : The door is already unlocked " << std::endl;
}
void ClosedState::Open() {
	std::cout << "Closed->Opened : The door is opened !" << std::endl;
	m_Context->SetState(new OpenedState());
}
void ClosedState::Close() {
	std::cout << "Closed : The door is already closed!" << std::endl;
}
void ClosedState::Lock() {
	std::cout << "Closed->Locked : The door is locked!" << std::endl;
	m_Context->SetState(new LockedState());
}

ClosedState::~ClosedState()
{
}
