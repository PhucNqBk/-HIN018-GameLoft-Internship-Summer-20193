#include "ESIdle.h"

ESIdle::ESIdle()
{
	m_Duration = 0.0f;
	m_WaitTimer = 0.0f;
}
ESIdle::~ESIdle()
{

}

void ESIdle::Init()
{
	m_Duration = 0.5f;
	m_WaitTimer = 0.0f;
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
void ESIdle::ProcessAI(float x, float y, float deltatime)
{
	if (m_Duration == 0)
	{
		m_Duration = ((float)rand() / (RAND_MAX));
	}
	else {
		m_WaitTimer += deltatime;
		if (m_WaitTimer >= m_Duration) 
		{
			m_Entity->ChangeState(EntityStateType::WALK);
		}
	}

}