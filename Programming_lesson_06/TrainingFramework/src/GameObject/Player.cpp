#include "Player.h"



Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	:Sprite2D(model, shader, texture)
{
	m_IsMoving = false;
	m_Direction = UP;
}
Player::~Player()
{
}
int keyPressed = 0;
#define MFORWARD 1;
#define MBACKWARD 2;
#define MUPWARD 4
#define MDOWNWARD 8
void Player::HandleKeyEvents(int key, bool bIsPressed)
{
	//std::cout << key << bIsPressed << std::endl;
	if (bIsPressed) {
			switch (key) {
				case VK_UP:
					m_IsMoving = true;
					//m_Direction = UP;
					keyPressed |= MUPWARD;
					break;
				case VK_DOWN:
					m_IsMoving = true;
					//m_Direction = DOWN;
					keyPressed |= MDOWNWARD;
					break;
				case VK_LEFT:
					m_IsMoving = true;
					//m_Direction = LEFT;
					keyPressed |= MBACKWARD;
					break;
				case VK_RIGHT:
					m_IsMoving = true;
					//m_Direction = RIGHT;
					keyPressed |= MFORWARD;
					break;
				default:
					break;
			}
	}
	else {
		m_IsMoving = false;
		switch (key) {
		case VK_UP:
			keyPressed &= !MUPWARD;
			break;
		case VK_DOWN:
			keyPressed &= !MDOWNWARD;
			break;
		case VK_LEFT:
			keyPressed &= !MBACKWARD;
			break;
		case VK_RIGHT:
			keyPressed &= !MFORWARD;
			break;
		default:
			break;
		}
	}
}
void Player::Update(GLfloat deltaTime) {
	/*
	if (m_IsMoving == true) {
		switch (m_Direction) {
			case UP:
				Set2DPosition(m_Vec2DPos.x, m_Vec2DPos.y - deltaTime *100);
				break;
			case DOWN:
				Set2DPosition(m_Vec2DPos.x, m_Vec2DPos.y + deltaTime* 100);
				break;
			case LEFT:
				Set2DPosition(m_Vec2DPos.x - deltaTime * 100, m_Vec2DPos.y );
				break;
			case RIGHT:
				Set2DPosition(m_Vec2DPos.x + deltaTime * 100, m_Vec2DPos.y);
				break;
			default:
				break;
		}
	}
	*/

	if (keyPressed & 1) 
	{
		Set2DPosition(m_Vec2DPos.x + deltaTime * 100, m_Vec2DPos.y);
	}
	if (keyPressed & 2) 
	{
		Set2DPosition(m_Vec2DPos.x - deltaTime * 100, m_Vec2DPos.y);
	}
	if (keyPressed & MUPWARD) 
	{
		Set2DPosition(m_Vec2DPos.x, m_Vec2DPos.y - deltaTime * 100);
	}
	if (keyPressed & MDOWNWARD) 
	{
		Set2DPosition(m_Vec2DPos.x, m_Vec2DPos.y + deltaTime * 100);
	}
}
