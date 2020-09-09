#include "ESIdle.h"

ESIdle::ESIdle()
{

}
ESIdle::~ESIdle()
{

}

void ESIdle::Init()
{
	Direction dir = m_Entity->GetDirection();
	if (dir == Direction::DIR_DOWN)
		m_Entity->ChangeAnimation("idle-0");
	else if (dir == Direction::DIR_RIGHT)
		m_Entity->ChangeAnimation("idle-1");
	else if (dir == Direction::DIR_UP)
		m_Entity->ChangeAnimation("idle-2");
	else if (dir == Direction::DIR_LEFT)
		m_Entity->ChangeAnimation("idle-3");
}
void ESIdle::Exit()
{

}

void ESIdle::HandleEvents()
{

}
void ESIdle::Update(float deltaTime)
{

}
void ESIdle::Draw()
{

}