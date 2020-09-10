#include "Door.h"
#include "Constant.h"
#include "ResourceManagers.h"
Door::Door(bool isEnable, bool isOpen, DoorDirection dir) :m_IsEnable(isEnable) ,m_IsOpen(isOpen), m_Direction(dir)
{
	
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2Dv1");
	auto texture = ResourceManagers::GetInstance()->GetTexture("DoorList", GL_NEAREST);
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_Sprite = std::make_shared<Tile>(model, shader, texture);
	m_Sprite->SetSize(96, 96);
	SetIsOpen(m_IsOpen);
	if (m_Direction == DoorDirection::DOWN) 
	{
		m_Collider.OffsetX = 0;
		m_Collider.OffsetY = 1;
		m_Collider.w = 84;
		m_Collider.h = 96;
	}
	else if (m_Direction == DoorDirection::RIGHT)
	{
		m_Collider.OffsetX = -1;
		m_Collider.OffsetY = 0;
		m_Collider.w = 96;
		m_Collider.h = 84;
	}
	else if (m_Direction == DoorDirection::UP)
	{
		m_Collider.OffsetX = 0;
		m_Collider.OffsetY = -1;
		m_Collider.w = 84;
		m_Collider.h = 96;
	}
	else
	{
		m_Collider.OffsetX = 1;
		m_Collider.OffsetY = 0;
		m_Collider.w = 96;
		m_Collider.h = 84;
	}
}
Door::~Door()
{

}
void Door::Init()
{

}
void Door::Draw()
{
	if (m_IsEnable)
	{
		m_Sprite->Draw(DOOR_TILE_ROW, DOOR_TILE_COL);
	}
	
}
void Door::Update(GLfloat deltaTime)
{

}
void Door::SetIsOpen(bool isOpen)
{
	m_IsOpen = isOpen;
	m_Sprite->SetTileID((isOpen == true) ? (m_Direction + 5) : (m_Direction + 1));
}
bool Door::GetIsOpen()
{
	return m_IsOpen;
}
void Door::SetIsEnable(bool isEnable)
{
	m_IsEnable = isEnable;
}
bool Door::GetIsEnable()
{
	return m_IsEnable;
}
DoorDirection Door::GetDoorDirection()
{
	return m_Direction;
}
void Door::SetPosition(float x, float y)
{
	m_Sprite->Set2DPosition(x, y);
}
Vector2	Door::GetPosition()
{
	return m_Sprite->Get2DPosition();
}
Collider2D Door::GetCollider()
{
	return m_Collider;
}