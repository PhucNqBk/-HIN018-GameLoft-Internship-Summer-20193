#include "ESWalk.h"

ESWalk::ESWalk()
{

}
ESWalk::~ESWalk()
{

}

void ESWalk::Init()
{
	m_Duration = 0;
	m_WaitTimer = 0;
	m_Range = m_Entity->GetRange();
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
void ESWalk::Exit()
{

}

void ESWalk::HandleEvents()
{

}
void ESWalk::Update(float deltaTime)
{

}
void ESWalk::Draw()
{

}
void ESWalk::ProcessAI(float x, float y, float deltatime)
{
	Vector2 pos =  m_Entity->GetPosition();
	if ((pos.x - x)*(pos.x - x) + (pos.y - y)*(pos.y - y) <= m_Range * m_Range)
	{
		Direction move = ValueFunction(x, y, pos.x, pos.y);
		m_Entity->MoveToDirection(move, deltatime);
	}
	else
	{
		if (m_Duration == 0)
		{
			m_Duration = ((float)rand() / (RAND_MAX));
			int dir = rand() % 4;
			if (dir == 0)
			{
				m_Entity->MoveToDirection(Direction::DIR_DOWN, deltatime);
			}
			else if (dir == 1) 
			{
				m_Entity->MoveToDirection(Direction::DIR_RIGHT, deltatime);
			}
			else if (dir == 2)
			{
				m_Entity->MoveToDirection(Direction::DIR_UP, deltatime);
			}
			else
			{
				m_Entity->MoveToDirection(Direction::DIR_LEFT, deltatime);
			}
		}
		else if (m_WaitTimer >= m_Duration)
			{
				m_WaitTimer = 0;
				int idle = rand() % 2;
				if (idle == 1) {
					m_Entity->ChangeState(EntityStateType::IDLE);
				}
				else
				{
					m_Duration = ((float)rand() / (RAND_MAX));
					int dir = rand() % 4;
					if (dir == 0)
					{
						m_Entity->MoveToDirection(Direction::DIR_DOWN, deltatime);
					}
					else if (dir == 1)
					{
						m_Entity->MoveToDirection(Direction::DIR_RIGHT, deltatime);
					}
					else if (dir == 2)
					{
						m_Entity->MoveToDirection(Direction::DIR_UP, deltatime);
					}
					else
					{
						m_Entity->MoveToDirection(Direction::DIR_LEFT, deltatime);
					}
				}
			}
		
		
			
	}
	m_WaitTimer += deltatime;
}
Direction ESWalk::ValueFunction(float px, float py, float ex, float ey)
{
	// speed * deltatime is constant so we can choose any number != 0
	float minRange = (ex - px)*(ex - px) + (ey- py + 1)*(ey - py + 1);
	float rangeR = (ex - px + 1)*(ex - px + 1) + (ey - py)*(ey - py);
	float rangeU = (ex - px)*(ex - px) + (ey - py - 1)*(ey - py - 1);
	float rangeL = (ex - px - 1)*(ex - px - 1) + (ey - py)*(ey - py);
	Direction dir = Direction::DIR_DOWN;
	if (rangeU < minRange)
	{
		minRange = rangeU;
		dir = Direction::DIR_UP;
	}
	if (rangeR < minRange)
	{
		minRange = rangeU;
		dir = Direction::DIR_RIGHT;
	}
	if (rangeL < minRange)
	{
		minRange = rangeU;
		dir = Direction::DIR_LEFT;
	}
	return dir;
}