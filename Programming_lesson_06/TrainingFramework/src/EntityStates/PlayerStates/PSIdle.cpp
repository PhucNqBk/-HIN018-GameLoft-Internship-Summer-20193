#include "PSIdle.h"

PSIdle::PSIdle()
{
	
}
PSIdle::~PSIdle()
{

}

void PSIdle::Init()
{	
	
	Direction dir = m_Entity->GetDirection();
	if (dir == Direction::DIR_DOWN)
		m_Entity->ChangeAnimation("player-idle-0");
	else if (dir == Direction::DIR_RIGHT)
		m_Entity->ChangeAnimation("player-idle-1");
	else if (dir == Direction::DIR_UP)
		m_Entity->ChangeAnimation("player-idle-2");
	else if (dir == Direction::DIR_LEFT)
		m_Entity->ChangeAnimation("player-idle-3");
}
void PSIdle::Exit()
{

}

void PSIdle::HandleEvents()
{

}

void PSIdle::Update(float deltaTime)
{

	int KeyPress = m_Entity->GetKeyPress();
	//std::cout << "IDLE: " << KeyPress << std::endl;
	if (KeyPress & MFORWARD) {
		m_Entity->SetDirection(Direction::DIR_RIGHT);
		m_Entity->ChangeState(EntityStateType::WALK);
	}
	else if (KeyPress & MBACKWARD)
	{
		m_Entity->SetDirection(Direction::DIR_LEFT);
		m_Entity->ChangeState(EntityStateType::WALK);
	}
	else if (KeyPress & MDOWNWARD)
	{
		m_Entity->SetDirection(Direction::DIR_DOWN);
		m_Entity->ChangeState(EntityStateType::WALK);
	}
	else if (KeyPress & MUPWARD)
	{
		m_Entity->SetDirection(Direction::DIR_UP);
		m_Entity->ChangeState(EntityStateType::WALK);
	}
	if ((KeyPress & P_SWORD))
	{
		m_Entity->ChangeState(EntityStateType::SWORD);
	}
	
}
