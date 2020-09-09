#include "PSWalk.h"

PSWalk::PSWalk()
{

}
PSWalk::~PSWalk()
{

}

void PSWalk::Init()
{
	Direction dir = m_Entity->GetDirection();
	if (dir == Direction::DIR_DOWN)
		m_Entity->ChangeAnimation("player-walk-0");
	else if (dir == Direction::DIR_RIGHT)
		m_Entity->ChangeAnimation("player-walk-1");
	else if (dir == Direction::DIR_UP)
		m_Entity->ChangeAnimation("player-walk-2");
	else if (dir == Direction::DIR_LEFT)
		m_Entity->ChangeAnimation("player-walk-3");
}
void PSWalk::Exit()
{

}

void PSWalk::HandleEvents()
{

}

void PSWalk::Update(float deltaTime)
{
	int KeyPress = m_Entity->GetKeyPress();
	//std::cout << "WALK: " << KeyPress << std::endl;
	Vector2 Pos = m_Entity->GetPosition();
	if (KeyPress & MDOWNWARD) {
		m_Entity->SetDirection(Direction::DIR_DOWN);
		m_Entity->ChangeAnimation("player-walk-0");
		m_Entity->SetPosition(Pos.x, Pos.y + PLAYER_WALK_SPEED * deltaTime);
	}
	else if (KeyPress & MFORWARD)
	{
		m_Entity->SetDirection(Direction::DIR_RIGHT);
		m_Entity->ChangeAnimation("player-walk-1");
		m_Entity->SetPosition(Pos.x + PLAYER_WALK_SPEED * deltaTime, Pos.y);
	}
	else if (KeyPress & MUPWARD)
	{
		m_Entity->SetDirection(Direction::DIR_UP);
		m_Entity->ChangeAnimation("player-walk-2");
		m_Entity->SetPosition(Pos.x , Pos.y - PLAYER_WALK_SPEED * deltaTime);
	}
	else if (KeyPress & MBACKWARD)
	{
		m_Entity->SetDirection(Direction::DIR_LEFT);
		m_Entity->ChangeAnimation("player-walk-3");
		m_Entity->SetPosition(Pos.x - PLAYER_WALK_SPEED *deltaTime, Pos.y );
	}
	else {
		m_Entity->ChangeState(EntityStateType::IDLE);
	}
	if (KeyPress & P_SWORD)
	{
		m_Entity->ChangeState(EntityStateType::SWORD);
	}
	
}