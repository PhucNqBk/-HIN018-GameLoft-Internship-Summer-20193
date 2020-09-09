#include "ESAttack.h"

ESAttack::ESAttack()
{

}
ESAttack::~ESAttack()
{

}

void ESAttack::Init()
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
void ESAttack::Exit()
{

}

void ESAttack::HandleEvents()
{

}
void ESAttack::Update(float deltaTime)
{

}
void ESAttack::Draw()
{

}