#include "PSSword.h"

PSSword::PSSword()
{
	m_Time = 0.4f;
}
PSSword::~PSSword()
{

}

void PSSword::Init()
{
	m_CurrentTime = 0;
	m_Entity->SetHitBoxEnable(true);
	Direction dir = m_Entity->GetDirection();
	if (dir == Direction::DIR_DOWN)
	{
		m_Entity->ChangeAnimation("player-sword-0");
		m_Entity->SetHitBox(0, 24, 48, 40);
	}
		
	else if (dir == Direction::DIR_RIGHT)
	{
		m_Entity->ChangeAnimation("player-sword-1");
		m_Entity->SetHitBox(24, 0, 40, 48);
	}
		
	else if (dir == Direction::DIR_UP)
	{
		m_Entity->ChangeAnimation("player-sword-2");
		m_Entity->SetHitBox(0, -24, 48, 40);
	}
		
	else if (dir == Direction::DIR_LEFT)
	{
		m_Entity->ChangeAnimation("player-sword-3");
		m_Entity->SetHitBox(-24, 0, 40, 48);
	}
		
}
void PSSword::Exit()
{

}

void PSSword::HandleEvents()
{

}

void PSSword::Update(float deltaTime)
{
	int KeyPress = m_Entity->GetKeyPress();
	/*
	
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
	*/
	bool isEnd =(m_Entity->GetCurrentAnimation()->GetCurrentFrame() == m_Entity->GetCurrentAnimation()->GetFrameCount() - 1);
	m_CurrentTime += deltaTime;
	if (isEnd)
	{
		m_Entity->ChangeState(EntityStateType::IDLE);
		m_Entity->SetHitBoxEnable(false);
	}
	if (KeyPress & P_SWORD)
	{
		m_Entity->ChangeState(EntityStateType::SWORD);
	}

}