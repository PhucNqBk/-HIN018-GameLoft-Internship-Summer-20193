#include "pch.h"
#include "LockedState.h"
#include <iostream>

LockedState::LockedState()
{
}

void LockedState::Unlock() {
	std::cout << "Locked->Closed : The door is unlocked. Now open it!" << std::endl;
	m_Context->SetState(new ClosedState());
}
void LockedState::Open() {
	std::cout << "Locked : The door is not unlocked !" << std::endl;
}
void LockedState::Close() {
	std::cout << "Locked : The door is already locked so you don't need to close!" << std::endl;
}
void LockedState::Lock() {
	std::cout << "Locked : The door is already locked!" << std::endl;
}
LockedState::~LockedState()
{
}
