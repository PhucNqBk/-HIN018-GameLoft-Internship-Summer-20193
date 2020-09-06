#include "Door.h"

Door::Door(bool isOpen, DoorDirection dir) : m_IsOpen(isOpen), m_Direction(dir)
{

}
Door::~Door()
{

}
void Door::SetIsOpen(bool isOpen)
{
	m_IsOpen = isOpen;
}
bool Door::GetIsOpen()
{
	return m_IsOpen;
}
DoorDirection Door::GetDoorDirection()
{
	return m_Direction;
}