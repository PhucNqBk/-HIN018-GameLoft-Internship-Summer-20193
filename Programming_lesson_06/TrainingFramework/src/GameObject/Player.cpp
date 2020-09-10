#include "Player.h"


Player::Player()
	:Entity()
{
	SetCollider(0, 0, 48, 48);
	m_Health = 12;
}
Player::~Player()
{

}
void Player::HandleKeyEvents(int key, bool bIsPressed)
{
	//std::cout << key << bIsPressed << std::endl;
	if (bIsPressed) {
			switch (key) {
				case VK_UP:
					m_CheckKeyPress |= MUPWARD;
					break;
				case VK_DOWN:
					m_CheckKeyPress |= MDOWNWARD;
					break;
				case VK_LEFT:
					m_CheckKeyPress |= MBACKWARD;
					break;
				case VK_RIGHT:
					m_CheckKeyPress |= MFORWARD;
					break;
				case 'Z':
					m_CheckKeyPress |= P_DASH;
					break;
				case 'C':
					m_CheckKeyPress |= P_SWORD;
				default:
					break;
			}
	}
	else {
		switch (key) {
			case VK_UP:
				m_CheckKeyPress &= ~MUPWARD;
				break;
			case VK_DOWN:
				m_CheckKeyPress &= ~MDOWNWARD;
				break;
			case VK_LEFT:
				m_CheckKeyPress &= ~MBACKWARD;
				break;
			case VK_RIGHT:
				m_CheckKeyPress &= ~MFORWARD;
				break;
			case 'Z':
				m_CheckKeyPress &= ~P_DASH;
				break;
			case 'C':
				m_CheckKeyPress &= ~P_SWORD;
			default:
				break;
		}
	}
}
void Player::Update(GLfloat deltaTime) {
	/*
	if (keyPressed & 1) 
	{
		Set2DPosition(m_Vec2DPos.x + deltaTime * 100, m_Vec2DPos.y);
	//	std::cout << "Move right" << std::endl;
	}
	if (keyPressed & 2) 
	{
		Set2DPosition(m_Vec2DPos.x - deltaTime * 100, m_Vec2DPos.y);
	//	std::cout << "Move left" << std::endl;
	}
	if (keyPressed & MUPWARD) 
	{
		Set2DPosition(m_Vec2DPos.x, m_Vec2DPos.y - deltaTime * 100);
	//	std::cout << "Move up" << std::endl;
	}
	if (keyPressed & MDOWNWARD) 
	{
		Set2DPosition(m_Vec2DPos.x, m_Vec2DPos.y + deltaTime * 100);
	//	std::cout << "Move down" << std::endl;
	}
	if (keyPressed & SHOOT)
	{
	//	std::cout << "Shoot :" << presss << std::endl;
	}
	*/
	m_LastSafePos = GetPosition();
	m_CurrentAnimation->Update(deltaTime);
	m_StateMachine->Update(deltaTime);
}
void Player::SetLastX()
{
	SetPosition(m_LastSafePos.x, m_Position.y);
}
void Player::SetLastY()
{
	SetPosition(m_Position.x, m_LastSafePos.y);
}
