#include "Player.h"


Player::Player()
	:Entity()
{
	SetCollider(0, 0, 48, 48);
	m_Health = 12;
	m_HitBoxEnable = false;
	m_HasKey = false;
	m_Score = 0;
	m_CanMove = true;
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
	//std::cout << m_HitBoxEnable << std::endl;
	//std::cout << m_HitBox.OffsetX << " " << m_HitBox.OffsetY << " " << m_HitBox.w << m_HitBox.h << std::endl;
	
	m_LastSafePos = GetPosition();
	if (m_IsInvulnerable)
	{
		m_InvunerableTimer += deltaTime;
		if (m_InvunerableTimer >= m_InvunerableDuration) 
		{
			m_IsInvulnerable = false;
			m_InvunerableTimer = 0;
		}
	}
		m_CurrentAnimation->Update(deltaTime);
		if(m_CanMove == true)
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
bool Player::HitBoxCollision(float posX, float posY, Collider2D other)
{
	bool overlap_x = ((m_Position.x + m_HitBox.OffsetX - m_HitBox.w / 2) < (posX + other.OffsetX + other.w / 2)) && ((m_Position.x + m_HitBox.OffsetX + m_HitBox.w / 2) > (posX + other.OffsetX - other.w / 2));
	bool overlap_y = ((m_Position.y + m_HitBox.OffsetY - m_HitBox.h / 2) < (posY + other.OffsetY + other.h / 2)) && ((m_Position.y + m_HitBox.OffsetY + m_HitBox.h / 2) > (posY + other.OffsetY - other.h / 2));

	return (overlap_x && overlap_y & GetHitBoxEnable());
}
bool Player::GetInvunerable()
{
	return m_IsInvulnerable;

}
void Player::Damage(int amount)
{
	if (amount >= m_Health)
	{
		m_Health = 0;
		m_IsDead = true;
	}
	else {
		m_Health -= amount;
	}
	m_IsInvulnerable = true;
}
bool Player::GetHasKey()
{
	return m_HasKey;
}
void Player::SetHasKey(bool key)
{
	m_HasKey = key;
}
void Player::AddHeart(int amount)
{
	m_Health = (m_Health + amount > 12) ? 12 : m_Health + amount;
}
void Player::AddScore(int amount)
{
	m_Score += amount;
}
int	Player::GetScore()
{
	return m_Score;
}
void Player::SetCanMove(bool move)
{
	m_CanMove = move;
}