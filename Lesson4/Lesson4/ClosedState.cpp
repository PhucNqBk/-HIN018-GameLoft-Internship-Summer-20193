#include "pch.h"
#include "ClosedState.h"
#include <iostream>

ClosedState::ClosedState()
{
}
void ClosedState::Unlock(StateContext* context) {
	std::cout << "Closed : The door is already unlocked " << std::endl;
}
void ClosedState::Open(StateContext* context) {
	context->SetState(new OpenedState());
	std::cout << "Closed->Opened : The door is opened !" << std::endl;
}
void ClosedState::Close(StateContext* context) {
	std::cout << "Closed : The door is already closed!" << std::endl;
}
void ClosedState::Lock(StateContext* context) {
	context->SetState(new LockedState());
	std::cout << "Closed->Locked : The door is locked!" << std::endl;
}

ClosedState::~ClosedState()
{
}
