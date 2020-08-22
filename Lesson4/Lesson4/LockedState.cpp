#include "pch.h"
#include "LockedState.h"
#include <iostream>

LockedState::LockedState()
{
}
void LockedState::Unlock(StateContext* context) {
	context->SetState(new ClosedState());
	std::cout << "Locked->Closed : The door is unlocked. Now open it!" << std::endl;
}
void LockedState::Open(StateContext* context) {
	std::cout << "Locked : The door is not unlocked !" << std::endl;
}
void LockedState::Close(StateContext* context) {
	std::cout << "Locked : The door is already locked so you don't need to close!" << std::endl;
}
void LockedState::Lock(StateContext* context) {
	std::cout << "Locked : The door is already locked!" << std::endl;
}
LockedState::~LockedState()
{
}
