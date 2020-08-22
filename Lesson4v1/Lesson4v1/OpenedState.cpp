#include "pch.h"
#include "OpenedState.h"
#include <iostream>
OpenedState::OpenedState()
{
}
void OpenedState::Unlock() {
	std::cout << "Opened : The door is opened so you don't need to unlock" << std::endl;
}
void OpenedState::Open() {
	std::cout << "Opened : The door is already opened !" << std::endl;
}
void OpenedState::Close() {
	std::cout << "Opened->Closed : The door is closed!" << std::endl;
	m_Context->SetState(new ClosedState());
}
void OpenedState::Lock() {
	std::cout << "Opened->Locked : The door is locked!" << std::endl;
	m_Context->SetState(new LockedState());
}

OpenedState::~OpenedState()
{
}
