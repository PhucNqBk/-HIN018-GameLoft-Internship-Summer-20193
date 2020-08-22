#include "pch.h"
#include "OpenedState.h"
#include <iostream>

OpenedState::OpenedState()
{
}
void OpenedState::Unlock(StateContext* context) {
	std::cout << "Opened : The door is opened so you don't need to unlock" << std::endl;
}
void OpenedState::Open(StateContext* context) {
	std::cout << "Opened : The door is already opened !" << std::endl;
}
void OpenedState::Close(StateContext* context) {
	context->SetState(new ClosedState());
	std::cout << "Opened->Closed : The door is closed!" << std::endl;
}
void OpenedState::Lock(StateContext* context) {
	context->SetState(new LockedState());
	std::cout << "Opened->Locked : The door is locked!" << std::endl;
}

OpenedState::~OpenedState()
{
}
